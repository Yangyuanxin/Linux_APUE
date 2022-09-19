/****************************************************************************
  Copyright(C)    2022, morixinguan@vip.qq.com
  File name :     Thread.c
  Author :        Yangyuanxin
  Version:        1.0
  Description:    线程相关接口及测试程序实现
  Other:
  Mode History:
          <author>        <time>      <version>   <desc>
          Yangyuanxin    2022-8-9      V1.0.0.0
          Yangyuanxin    2022-8-20     V1.0.0.1   增加线程分离接口
****************************************************************************/
#include "Thread.h"

S32 ThreadCreate(Thread_t *Thread, const ThreadAttr_t *Attr, Void *(*ThreadFunc) (Void *), Void *Arg)
{
    return pthread_create(Thread, Attr, ThreadFunc, Arg);
}

S32 ThreadCancel(Thread_t Thread)
{
    return pthread_cancel(Thread);
}

Void ThreadExit(Void *Ret)
{
    pthread_exit(Ret);
}

S32 ThreadJohin(Thread_t Thread, Void **Ret)
{
    return pthread_join(Thread, Ret);
}

S32 ThreadDetach(Thread_t Thread)
{
    return pthread_detach(Thread);
}

#ifdef TEST_OPEN
Thread_t Id2;
static Void *ThreadCallBack(Void *Arg)
{
    (Void)Arg;
    S32 Counter = 0;
    while(1)
    {
        if(Counter > 10)
            ThreadExit(Null);
        printf("Hello World!\n");
        usleep(1000 * 100);
        Counter++;
    }
    return Null;
}

static Void *ThreadCallBack1(Void *Arg)
{
    (Void)Arg;
    S32 Counter = 0;
    while(1)
    {
        printf("Hello Thread!\n");
        usleep(1000 * 100);
        Counter++;
    }
    return Null;
}


S32 ThreadTest(Void)
{
    S32 Ret ;
    Thread_t Id1;
    
    Ret = ThreadCreate(&Id1, Null, ThreadCallBack, Null);
    if(0 != Ret)
    {
        printf("ThreadCreate fail:%d!", Ret);
        goto ErrorHandler;
    }
    
    Ret = ThreadCreate(&Id2, Null, ThreadCallBack1, Null);
    if(0 != Ret)
    {
        printf("ThreadCreate fail:%d!", Ret);
        goto ErrorHandler;
    }
    
    Ret = ThreadJohin(Id1, Null);
    if(0 != Ret)
    {
        printf("ThreadJohin fail:%d!", Ret);
        goto ErrorHandler;
    }
    
    printf("Cancel ThreadCallBack1\n");
    ThreadCancel(Id2);
    printf("Cancel ThreadCallBack1 End\n");
    
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