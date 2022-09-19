/****************************************************************************
  Copyright(C)    2022, morixinguan@vip.qq.com
  File name :     Terminal.c
  Author :        Yangyuanxin
  Version:        1.0
  Description:    终端输出相关接口及测试程序实现
  Other:
  Mode History:
          <author>        <time>      <version>   <desc>
          Yangyuanxin    2022-8-24     V1.0.0.0
		  Yangyuanxin    2022-9-20     V1.0.0.1   增加设置属性、串口终端操作API
****************************************************************************/
#include "Terminal.h"

static S32 TerminalSetAttr(S32 Fd, TerminalAttr_t *Attr)
{
    S32 Status = 0;
    struct termios Opt;
    
    if(Fd < 0 || !Attr)
        return -1;
    
    tcgetattr(Fd, &Opt);
    
    /* raw mode */
    Opt.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
                | INLCR | IGNCR | ICRNL | IXON);
    Opt.c_oflag &= ~OPOST;
    Opt.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    Opt.c_cflag &= ~(CSIZE | PARENB);
    Opt.c_cflag |= CS8;
    /* raw mode end */
    
    cfsetispeed(&Opt, Attr->Attr_t.BaudRate);
    cfsetospeed(&Opt, Attr->Attr_t.BaudRate);
    
    Opt.c_cflag &= ~CSIZE;
    
    switch(Attr->Attr_t.Len)
    {
        case UART_5BIT:
            Opt.c_cflag |= CS5;
        break ;
        
        case UART_6BIT:
            Opt.c_cflag |= CS6;
        break ;
        
        case UART_7BIT:
            Opt.c_cflag |= CS7;
        break ;
        
        case UART_8BIT:
            Opt.c_cflag |= CS8;
        break ;
        
        default:
            Opt.c_cflag |= CS8;
        break ;
    }
    
    switch(Attr->Attr_t.Parity)
    {
        case NO_Parity:
        case MARK_PARITY:
        case SPACE_PARITY:
            Opt.c_cflag &= ~PARENB;
        break ;
        
        case ODD_PARITY:
            Opt.c_cflag |= PARENB;
            Opt.c_cflag |= PARODD;
        break ;
        
        case EVEN_PARITY:
            Opt.c_cflag |= PARENB;
            Opt.c_cflag &= ~PARODD;
        break ;
        
        default:
            Opt.c_cflag &= ~PARENB;
        break ;
    }
    
    switch(Attr->Attr_t.StopBits)
    {
        case STOP_BITS_1:
        case STOP_BITS_1_5:
            Opt.c_cflag &= ~CSTOPB;
        break ;
        
        case STOP_BITS_2:
            Opt.c_cflag |= CSTOPB;
        break  ;
        
        default:
            Opt.c_cflag &= ~CSTOPB;
        break ;
    }
    
    if(Attr->Attr_t.DtrDsrOn)
    {
        /*Dtr*/
        ioctl(Fd, TIOCMGET, &Status);
        Status |= TIOCM_DTR;
        ioctl(Fd, TIOCMSET, &Status);
        /*Dsr*/
        ioctl(Fd, TIOCMGET, &Status);
        Status |= TIOCM_LE;
        ioctl(Fd, TIOCMSET, &Status);
    }
    else
    {
        /*Dtr*/
        ioctl(Fd, TIOCMGET, &Status);
        Status &= ~TIOCM_DTR;
        ioctl(Fd, TIOCMSET, &Status);
        /*Dsr*/
        ioctl(Fd, TIOCMGET, &Status);
        Status &= ~TIOCM_LE;
        ioctl(Fd, TIOCMSET, &Status);
    }
    
    /* hardware flow control using RTS/CTS pins */
    if(Attr->Attr_t.RtsCtsOn)
        Opt.c_cflag |= CRTSCTS;
    else
        Opt.c_cflag &= ~CRTSCTS;
    
    /* software flow control*/
    if(Attr->Attr_t.XonXoffOn)
        Opt.c_iflag |= (IXON | IXOFF | IXANY);
    else 
        Opt.c_iflag &= ~(IXON | IXOFF | IXANY);
    
    Opt.c_cc[VTIME] = 0;
    Opt.c_cc[VMIN]  = 0;
    
    if(tcflush(Fd, TCIFLUSH) < 0)
    {
        fprintf(stderr, "tcflush error:%s\n", strerror(errno));
        return -1;
    }
    
    if(tcsetattr(Fd, TCSANOW, &Opt) < 0)
    {
        fprintf(stderr, "tcsetattr error:%s\n", strerror(errno));
        return -2;
    }

    return 0;
}

S32 TerminalOpen(TerminalAttr_t *Attr)
{
    S32 Fd = -1;
    S32 Ret = -1;
    
    if(Null == Attr)
    {
        printf("Attr is Null!\n");
        return -1;
    }
    
    Fd = open(Attr->Dev, Attr->DevFunctionAttr);
    if(Fd < 0)
    {
        printf("open dev failed!\n");
        return -1;
    }
    
    Ret = TerminalSetAttr(Fd, Attr);
    if(Ret < 0)
    {
        printf("TerminalSetAttr failed!\n");
        return -1;
    }
    
    return Fd;
}

S32 TerminalClose(S32 Fd)
{
    return close(Fd);
}

S32 TerminalWrite(S32 Fd, S8 *Buff, S32 Len)
{
    return write(Fd, Buff, Len);
}

S32 TerminalRead(S32 Fd, S8 *Buff, S32 Len)
{
    return read(Fd, Buff, Len);
}

#ifdef TEST_OPEN

S32 TerminalTest(Void)
{
    S32 Fd = -1;
    S32 Len = -1;
    TerminalAttr_t Attr;
    
    Attr.Attr_t.BaudRate = 115200;
    Attr.Attr_t.Len = UART_8BIT;
    Attr.Attr_t.Parity = NO_Parity;
    Attr.Attr_t.StopBits = STOP_BITS_1;
    Attr.Attr_t.DtrDsrOn = 0;
    Attr.Attr_t.RtsCtsOn = 0;
    Attr.Attr_t.XonXoffOn = 0;
    
    memset(Attr.Dev, 0, sizeof(Attr.Dev));
    snprintf(Attr.Dev, sizeof(Attr.Dev), "%s", "/dev/tty");
    Attr.Dev[strlen(Attr.Dev)] = '\0';
    Attr.DevFunctionAttr = O_RDWR | O_NOCTTY;
    
    Fd = TerminalOpen(&Attr);
    if(Fd < 0)
    {
        printf("TerminalOpen failed!\n");
        return -1;
    }
    
    Len = TerminalWrite(Fd, "Hello World\n", strlen("Hello World\n") + 1);
    if(Len <= 0)
    {
        printf("TerminalWrite failed!\n");
        return -1;
    }
    
    TerminalClose(Fd);
    
    printf("Terminal Test Success!");
    return 0;
}

#endif
