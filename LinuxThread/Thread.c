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
****************************************************************************/
#include "Thread.h"

S32  ThreadCreate(Thread_t *Thread, const ThreadAttr_t *Attr, Void *(*ThreadFunc) (Void *), Void *Arg)
{
    return pthread_create(Thread, Attr, ThreadFunc, Arg);
}

S32  ThreadCancel(Thread_t Thread)
{
    return pthread_cancel(Thread);
}

Void ThreadExit(Void *Ret)
{
    pthread_exit(Ret);
}

S32  ThreadJohin(Thread_t Thread, Void **Ret)
{
    return pthread_join(Thread, Ret);
}

#ifdef TEST_OPEN
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


S32 ThreadTest(Void)
{
    S32 Ret ;
    Thread_t Id;
    
    Ret = ThreadCreate(&Id, Null, ThreadCallBack, Null);
    if(0 != Ret)
    {
        printf("ThreadCreate fail:%d!", Ret);
        goto ErrorHandler;
    }
    
    Ret = ThreadJohin(Id, Null);
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