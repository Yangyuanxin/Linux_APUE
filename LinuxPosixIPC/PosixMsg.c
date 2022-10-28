/****************************************************************************
  Copyright(C)    2022, morixinguan@vip.qq.com
  File name :     PosixMsg.c
  Author :        Yangyuanxin
  Version:        1.0
  Description:    Posix消息队列相关接口及测试程序实现
  Other:
  Mode History:
          <author>        <time>      <version>   <desc>
          Yangyuanxin    2022-10-17    V1.0.0.0
****************************************************************************/
#include "PosixMsg.h"

S32 PosixMsgClose(PosixMqd_t Fd)
{
    return mq_close(Fd);
}

S32 PosixMsqUnlink(const S8 *Name)
{
    S8 MsqName[MSQ_NAME_SIZE + 1];
    
    if(Null == Name)
    {
        printf("Name is Null\n");
        return -1;
    }
    
    snprintf(MsqName, sizeof(MsqName), "/%s", Name);
    
    return mq_unlink(MsqName);
}

S32 PosixMsgRcv(PosixMqd_t Fd, S8 *Buff, S32 Size)
{
    return mq_receive(Fd, Buff, Size, Null);
}

PosixMqd_t PosixMsgOpen(const S8 *Name, S32 Flag)
{
    S8 MsqName[MSQ_NAME_SIZE + 1];
    
    if(Null == Name)
    {
        printf("Name is Null\n");
        return -1;
    }
    
    snprintf(MsqName, sizeof(MsqName), "/%s", Name);
    
    return mq_open(MsqName, Flag, 0666, Null);
}

S32 PosixMsgSnd(PosixMqd_t Fd, const S8 *Buff, S32 Size)
{
    return mq_send(Fd, Buff, Size, 0);
}

PosixMqd_t PosixMsgSetAttr(PosixMqd_t Fd, PosixMqAttr_t *Attr)
{
    return mq_setattr(Fd, Attr, Null);
}

PosixMqd_t PosixMsgGetAttr(PosixMqd_t Fd, PosixMqAttr_t *Attr)
{
    return mq_getattr(Fd, Attr);
}

#ifdef TEST_OPEN
S8 *MsgName = "PRINT_I";

static Void *PollMqueueFun(Void *Arg)
{
    S32 Ret = -1;
    PosixMqd_t Fd;
    S8 Buff[20] = {0};
    struct pollfd Fds[1];
    
    Fd = PosixMsgOpen(MsgName, O_RDONLY);
    if(Fd < 0)
    {
        printf("PosixMsgOpen %s fail:%d\n", MsgName, Fd);
        return Null;
    }
    
    Fds[0].fd = Fd;
    Fds[0].events = POLLIN;
    Fds[0].revents = 0;
    
    while(1)
    {
        Ret = poll(Fds, 1, -1);
        if(Ret < 0)
        {
            printf("poll fail!\n");
            PosixMsgClose(Fds[0].fd);
            PosixMsqUnlink(MsgName);
            printf("PosixMsg Test Fail!\n");
            return Null;
        }
        
        if(Fds[0].revents & POLLIN)
        {
            memset(Buff, 0, sizeof(Buff));
            Ret = PosixMsgRcv(Fds[0].fd, (S8 *)Buff, 20);
            if(Ret < 0)
            {
                printf("PosixMsgRcv fail: %d!\n", Ret);
                PosixMsgClose(Fds[0].fd);
                PosixMsqUnlink(MsgName);
                printf("PosixMsg Test Fail!\n");
                return Null;
            }
            
            printf("Read Buff: %s\n", Buff);
            break;
        }
        
        usleep(10000);
    }
    
    PosixMsgClose(Fds[0].fd);
    PosixMsqUnlink(MsgName);
    return Null;
}

S32 PosixMsgTest(Void)
{
    PosixMqd_t Fd;
    pthread_t Id; 
    
    Fd = PosixMsgOpen(MsgName, O_WRONLY | O_CREAT);
    if(Fd < 0)
    {
        printf("PosixMsgOpen %s fail!\n", MsgName);
        printf("PosixMsg Test Fail!\n");
        return -1;
    }
    
    PosixMsgSnd(Fd, "Hello World", strlen("Hello World"));
    PosixMsgClose(Fd);
    
    pthread_create(&Id, Null, PollMqueueFun, Null);
    pthread_join(Id, Null);
    
    return 0;
}
#endif
