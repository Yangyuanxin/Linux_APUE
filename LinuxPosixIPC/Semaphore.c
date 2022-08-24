/****************************************************************************
  Copyright(C)    2022, morixinguan@vip.qq.com
  File name :     Terminal.c
  Author :        Yangyuanxin
  Version:        1.0
  Description:    信号量相关接口及测试程序实现
  Other:
  Mode History:
          <author>        <time>      <version>   <desc>
          Yangyuanxin    2022-8-24     V1.0.0.0
****************************************************************************/
#include "Semaphore.h"

Void *SemaphoreCreate(Void)
{
    Semaphore_t *Sem = (Semaphore_t *)malloc(sizeof(Semaphore_t));
    if(Null == Sem)
        return Null;
    
    if(0 != sem_init(Sem, 0, 0))
    {
        free(Sem);
        Sem = Null;
        return Null;
    }
    
    return Sem;
}

S32 SemaphoreDestroy(Void *Sem)
{
    if(0 != sem_destroy((Semaphore_t *)Sem))
    {
        printf("sem_destroy failed!\n");
        free(Sem);
        Sem = Null;
        return -1;
    }
    
    free(Sem);
    Sem = Null;
    return 0;
}

S32 SemaphorePost(Void *Sem)
{
    return sem_post((Semaphore_t *)Sem);
}

S32 SemaphoreWait(Void *Sem, U32 TimeoutMs)
{
    S32 S;
    struct timespec Ts;
    if(0 == TimeoutMs) 
    {
        sem_wait(Sem);
        return 0;
    } 
    else 
    {
        do 
        {
            if(clock_gettime(CLOCK_REALTIME, &Ts) == -1) 
                return -1;

            S = 0;
            Ts.tv_nsec += (TimeoutMs % 1000) * 1000000;
            if(Ts.tv_nsec >= 1000000000) 
            {
                Ts.tv_nsec -= 1000000000;
                S = 1;
            }

            Ts.tv_sec += TimeoutMs / 1000 + S;

        } while (((S = sem_timedwait(Sem, &Ts)) != 0) && errno == EINTR);

        return S ? -1 : 0;
    }
}

#ifdef TEST_OPEN
Semaphore_t *Sem = Null;

static Void *FunCall1(Void *Arg)
{
    (Void)Arg;
    if(0 != SemaphorePost(Sem))
    {
        printf("SemaphorePost failed!\n");
        return Null;
    }
    printf("SemaphorePost success!\n");
    return Null;
}

static Void *FunCall2(Void *Arg)
{
    (Void)Arg;
    S32 Status = 0;
    
    for(;;)
    {
        printf("FunCall2 block wait sem!\n");
        Status = SemaphoreWait(Sem, 0);
        if(0 == Status)
        {
            printf("Reciver Sem ok!!!\n");
            break;
        }
    }
    return Null;
}

S32 SemaphoreTest(Void)
{
    S32 Ret = 0;
    pthread_t Id1, Id2;
    
    Sem = SemaphoreCreate();
    if(Null == Sem)
    {
        printf("SemaphoreCreate failed!\n");
        return -1;
    }
    pthread_create(&Id2, Null, FunCall2, Null);
    sleep(2);
    pthread_create(&Id1, Null, FunCall1, Null);
    pthread_join(Id1, Null);
    pthread_join(Id2, Null);
    
    Ret = SemaphoreDestroy(Sem);
    if(Ret != 0)
    {
        printf("SemaphoreDestroy failed!\n");
        return -1;
    }
    printf("Semaphore Test Success!");
    return 0;
}
#endif