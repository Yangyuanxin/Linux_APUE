/****************************************************************************
  Copyright(C)    2022, morixinguan@vip.qq.com
  File name :     PollFds.c
  Author :        Yangyuanxin
  Version:        1.0
  Description:    Poll相关接口及测试程序实现
  Other:
  Mode History:
          <author>        <time>      <version>   <desc>
          Yangyuanxin    2022-8-9      V1.0.0.0
****************************************************************************/
#include "PollFds.h"

S32 PollFds(PollFds_t *Fds, U64 NumOfFds, S32 TimeOut)
{
    return poll((struct pollfd *)Fds, NumOfFds, TimeOut);
}

#ifdef TEST_OPEN
#include "Thread.h"
#include "FileOperate.h"
#define STR  "POLLTEST"
#define FIFO_FILE "./fifofile"

static Void *ThreadCallBack1(Void *Arg)
{
    (Void)Arg;
    S32 Fd = -1;
    S32 Ret = -1;
    Ret = mkfifo(FIFO_FILE, 0777);
    if(Ret < 0)
    {
        printf("mkfifo FIFO_FILE fail\n");
        goto ErrorHandler;
    }
    
    Fd = FileOpen(FIFO_FILE, O_WRONLY | O_CREAT);
    if(Fd < 0)
    {
        printf("FileOpen FIFO_FILE fail:%d!\n", Fd);
        goto ErrorHandler;
    }
    
    Ret = FileWrite(Fd, STR, strlen(STR) + 1);
    if(Ret < 0)
    {
        printf("FileWrite FIFO_FILE fail:%d!\n", Ret);
        goto ErrorHandler;
    }
    
    Ret = FileClose(Fd);
    if(0 != Ret)
    {
        printf("FileClose FIFO_FILE fail!\n");
        goto ErrorHandler;
    }
    return Null;
    
ErrorHandler:

    Ret = FileClose(Fd);
    if(0 != Ret)
    {
        printf("FileClose FIFO_FILE fail!\n");
        goto ErrorHandler;
    }
    
    printf("SendData Test Fail!\n");
    
    return Null;
}

static Void *ThreadCallBack2(Void *Arg)
{
    (Void)Arg;
    S32 Ret = -1;
    S8 Buff[128] = {0};
    PollFds_t Fds[1] = {0};
    
    Fds[0].Fd = FileOpen(FIFO_FILE, O_RDONLY);
    Fds[0].Events = POLLIN;
    if(Fds[0].Fd < 0)
    {
        printf("FileOpen FIFO_FILE fail\n");
        goto ErrorHandler;
    }
    
    while(1)
    {
        Ret = PollFds(Fds, 1, -1);
        if(Ret < 0)
        {
            printf("PollFds error:%d!\n", Ret);
            goto ErrorHandler;
        }
        else
        {
            printf("Poll have data!!!\n");
            break ;
        }
    }
    
    Ret = FileRead(Fds[0].Fd, Buff, sizeof(Buff));
    if(Ret < 0)
    {
        printf("FileRead data fail:%d!\n", Ret);
        goto ErrorHandler;
    }
    
    printf("Poll data:%s Len:%ld\n", Buff, strlen(Buff) + 1);
    
    Ret = FileClose(Fds[0].Fd);
    if(0 != Ret)
    {
        printf("FileClose FIFO_FILE fail!\n");
        goto ErrorHandler;
    }
    
    Ret = FileUnlink(FIFO_FILE);
    if(0 != Ret)
    {
        printf("FileUnlink FIFO_FILE fail!\n");
        goto ErrorHandler;
    }
    
    printf("PollFds SendData Test Success!\n");
    return Null;
    
ErrorHandler:

    printf("PollFds Test Fail!\n");
    
    Ret = FileClose(Fds[0].Fd);
    if(0 != Ret)
    {
        printf("FileClose FIFO_FILE fail!\n");
        goto ErrorHandler;
    }
    
    Ret = FileUnlink(FIFO_FILE);
    if(0 != Ret)
    {
        printf("FileUnlink FIFO_FILE fail!\n");
        goto ErrorHandler;
    }
    return Null;
}

S32 PollFdsTest(Void)
{
    S32 Ret ;
    Thread_t Id1, Id2;
    
    Ret = ThreadCreate(&Id1, Null, ThreadCallBack1, Null);
    if(0 != Ret)
    {
        printf("ThreadCreate Id1 fail:%d!", Ret);
        goto ErrorHandler;
    }
    
    usleep(1000*300);
    
    Ret = ThreadCreate(&Id2, Null, ThreadCallBack2, Null);
    if(0 != Ret)
    {
        printf("ThreadCreate Id2 fail:%d!", Ret);
        goto ErrorHandler;
    }
    
    Ret = ThreadJohin(Id1, Null);
    if(0 != Ret)
    {
        printf("ThreadJohin fail:%d!", Ret);
        goto ErrorHandler;
    }
    
    Ret = ThreadJohin(Id2, Null);
    if(0 != Ret)
    {
        printf("ThreadJohin fail:%d!", Ret);
        goto ErrorHandler;
    }
    
    printf("Thread Test Success!\n");
    return 0;
    
ErrorHandler:
    return -1;
}
#endif
