/****************************************************************************
  Copyright(C)    2022, morixinguan@vip.qq.com
  File name :     SystemVMsg.c
  Author :        Yangyuanxin
  Version:        1.0
  Description:    System-V消息队列相关接口及测试程序实现
  Other:
  Mode History:
          <author>        <time>      <version>   <desc>
          Yangyuanxin    2022-9-1      V1.0.0.0
****************************************************************************/
#include "SystemVMsg.h"

S32 SystemVMsgOpen(SystemVMsgKey_t Key)
{
    return msgget(Key, IPC_CREAT | 0666);
}

S32 SystemVMsgSend(S32 Fd, S8 *Buf, S32 Len)
{
    return msgsnd(Fd, Buf, Len, 0);
}

S32 SystemVMsgRecv(S32 Fd, S8 *Buf, S32 Len)
{
    return msgrcv(Fd, Buf, Len, 0, 0);
}

S32 SystemVMsgClose(S32 Fd)
{
    return msgctl(Fd, IPC_RMID, Null);
}


#ifdef TEST_OPEN

#include "Thread.h"

#define KEY 110

struct MsgQ_t
{
    S64 Type;
    S8 Buff[100];
};

Void SystemVMsgTest1(Void)
{
    S32  Ret;
    S32  MsgId;
    struct MsgQ_t Buf;
    struct MsgQ_t Buf1;
    
    MsgId = SystemVMsgOpen(KEY);
    if(MsgId < 0)
    {
        printf("SystemVMsgOpen fail:%d\n", MsgId);
        goto ErrorHandler;
    }
    
    Ret = system("ipcs -q") ;
    if(Ret < 0)
    {
        printf("system fail:%d\n", Ret);
        goto ErrorHandler;
    }
    
    Buf.Type = 1;
    memset(Buf.Buff, 0, 100);
    strcpy(Buf.Buff, "Hello World");
    Ret = SystemVMsgSend(MsgId, (Void *)&Buf, 100);
    if(Ret < 0)
    {
        printf("SystemVMsgSend fail:%d\n", Ret);
        goto ErrorHandler;
    }
    
    Ret = system("ipcs -q");
    if(Ret < 0)
    {
        printf("system fail:%d\n", Ret);
        goto ErrorHandler;
    }
    
    memset(Buf1.Buff,0,100);
    Ret = SystemVMsgRecv(MsgId, (Void *)&Buf1, 100);
    if(Ret < 0)
    {
        printf("SystemVMsgRecv fail:%d\n", Ret);
        goto ErrorHandler;
    }
    
    Ret = SystemVMsgClose(MsgId);
    if(Ret < 0)
    {
        printf("SystemVMsgClose fail:%d\n", Ret);
        goto ErrorHandler;
    }
    
    Ret = system("ipcs -q");
    if(Ret < 0)
    {
        printf("system fail:%d\n", Ret);
        goto ErrorHandler;
    }
    
    return ;
    
ErrorHandler:
    return ;
}

static Void *RecvMsqThreadFun(Void)
{
    S32  Ret;
    S32  MsgId;
    struct MsgQ_t Buf;
    
    MsgId = SystemVMsgOpen(KEY);
    if(MsgId < 0)
    {
        printf("SystemVMsgOpen fail:%d\n", MsgId);
        goto ErrorHandler;
    }
    
    Ret = system("ipcs -q") ;
    for(;;)
    {
        memset(Buf.Buff, 0, 100);
        Ret = SystemVMsgRecv(MsgId, (Void *)&Buf, 100);
        if(Ret < 0)
        {
            printf("SystemVMsgRecv fail:%d\n", Ret);
            goto ErrorHandler;
        }
        
        printf("Type:%lld Buff:%s\n", Buf.Type, Buf.Buff);
        break ;
    }

    Ret = SystemVMsgClose(MsgId);
    if(Ret < 0)
    {
        printf("SystemVMsgClose fail:%d\n", Ret);
        goto ErrorHandler;
    }
    
    Ret = system("ipcs -q");
    if(Ret < 0)
    {
        printf("system fail:%d\n", Ret);
        goto ErrorHandler;
    }
    
    return Null;
    
ErrorHandler:
    return Null;
}

static Void *SendMsqThreadFun(Void)
{
    S32  Ret;
    S32  MsgId;
    struct MsgQ_t Buf;
    
    MsgId = SystemVMsgOpen(KEY);
    if(MsgId < 0)
    {
        printf("SystemVMsgOpen fail:%d\n", MsgId);
        return Null;
    }
    
    Ret = system("ipcs -q") ;
    if(Ret < 0)
    {
        printf("system fail:%d\n", Ret);
        return Null;
    }
    
    for(;;)
    {
        Buf.Type = 1;
        memset(Buf.Buff, 0, 100);
        strcpy(Buf.Buff,"Hello World");
        
        Ret = SystemVMsgSend(MsgId, (Void *)&Buf, 100);
        if(Ret < 0)
        {
            printf("SystemVMsgSend fail:%d\n", Ret);
            return Null;
        }
        
        printf("Type:%lld Buff:%s\n", Buf.Type, Buf.Buff);
        break ;
    }
    
    return Null;
}

Void SystemVMsgTest2(Void)
{
    S32 Ret = -1 ;
    pthread_t Id1, Id2;
    
    Ret = ThreadCreate(&Id1, Null, (Void *)RecvMsqThreadFun, Null);
    if(Ret != 0)
    {
        printf("ThreadCreate fail:%d\n", Ret);
        return ;
    }
    
    Ret = ThreadCreate(&Id2, Null, (Void *)SendMsqThreadFun, Null);
    if(Ret != 0)
    {
        printf("ThreadCreate fail:%d\n", Ret);
        return ;
    }
    
    Ret = ThreadJohin(Id1, Null);
    if(Ret != 0)
    {
        printf("ThreadJohin fail:%d\n", Ret);
        return ;
    }
    
    Ret = ThreadJohin(Id2, Null);
    if(Ret != 0)
    {
        printf("ThreadJohin fail:%d\n", Ret);
        return ;
    }
}

S32 SystemVMsgTest(Void)
{
    SystemVMsgTest1();
    SystemVMsgTest2();
    
    return 0;
}
#endif

