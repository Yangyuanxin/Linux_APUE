/****************************************************************************
  Copyright(C)    2022, morixinguan@vip.qq.com
  File name :     PosixSemaphore.c
  Author :        Yangyuanxin
  Version:        1.0
  Description:    Posix信号量相关接口及测试程序实现
  Other:
  Mode History:
          <author>        <time>      <version>   <desc>
          Yangyuanxin    2022-8-24     V1.0.0.0
****************************************************************************/
#include "PosixSemaphore.h"

Void *PosixSemaphoreCreate(Void)
{
    PosixSemaphore_t *Sem = (PosixSemaphore_t *)malloc(sizeof(PosixSemaphore_t));
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

S32 PosixSemaphoreDestroy(Void *Sem)
{
    if(0 != sem_destroy((PosixSemaphore_t *)Sem))
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

S32 PosixSemaphorePost(Void *Sem)
{
    return sem_post((PosixSemaphore_t *)Sem);
}

S32 PosixSemaphoreWait(Void *Sem, U32 TimeoutMs)
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
static uint8_t SemCnt = 0;
PosixSemaphore_t *Sem = Null;

static Void *FunCall1(Void *Arg)
{
    (Void)Arg;
    for(;;)
    {
        if(0 != PosixSemaphorePost(Sem))
        {
            printf("SemaphorePost failed!\n");
            return Null;
        }
        SemCnt++;
        if(SemCnt >= 10)
        {
            printf("FunCall1 Finish!\n");
            break;
        }
        printf("SemaphorePost success!\n");
        sleep(1);
    }
    return Null;
}

static Void *FunCall2(Void *Arg)
{
    (Void)Arg;
    S32 Status = 0;
    
    for(;;)
    {
        printf("FunCall2 block wait sem!\n");
        Status = PosixSemaphoreWait(Sem, 0);
        if(0 == Status)
        {
            printf("Reciver Sem ok!!!\n");
            if(SemCnt >= 10)
            {
                printf("FunCall2 Finish!\n");
                break;
            }
        }
    }
    return Null;
}

S32 PosixSemaphoreTest(Void)
{
    S32 Ret = 0;
    pthread_t Id1, Id2;
    
    Sem = PosixSemaphoreCreate();
    if(Null == Sem)
    {
        printf("SemaphoreCreate failed!\n");
        return -1;
    }
    
    pthread_create(&Id2, Null, FunCall2, Null);
    pthread_create(&Id1, Null, FunCall1, Null);
    pthread_join(Id1, Null);
    pthread_join(Id2, Null);
    Ret = PosixSemaphoreDestroy(Sem);
    if(Ret != 0)
    {
        printf("SemaphoreDestroy failed!\n");
        return -1;
    }
    printf("PosixSemaphore Test Success!\n");
    return 0;
}
#endif
