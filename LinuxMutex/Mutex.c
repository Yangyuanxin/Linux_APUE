/****************************************************************************
  Copyright(C)    2022, morixinguan@vip.qq.com
  File name :     Mutex.c
  Author :        Yangyuanxin
  Version:        1.0
  Description:    互斥锁相关接口及测试程序实现
  Other:
  Mode History:
          <author>        <time>      <version>   <desc>
          Yangyuanxin    2022-8-24     V1.0.0.0
****************************************************************************/
#include "Mutex.h"

Void *MutexCreate(Void)
{
    Mutex_t *Mutex = (Mutex_t *)malloc(sizeof(Mutex_t));
    if(Null == Mutex)
        return Null;
    
    if(0 != pthread_mutex_init(Mutex, Null))
    {
        free(Mutex);
        Mutex = Null;
        return Null;
    }
    
    return Mutex;
}

S32 MutexDestroy(Void *Mutex)
{
    if(0 != pthread_mutex_destroy((Mutex_t *)Mutex))
    {
        free(Mutex);
        return -1;
    }
    
    free(Mutex);
    Mutex = Null;
    return 0;
}

S32 MutexLock(Void *Mutex)
{
    return pthread_mutex_lock((Mutex_t *)Mutex);
}

S32 MutexTryLock(Void *Mutex)
{
    return pthread_mutex_trylock((Mutex_t *)Mutex);
}

S32 MutexUnlock(Void *Mutex)
{
    return pthread_mutex_unlock((Mutex_t *)Mutex);
}

#ifdef TEST_OPEN
S32 Number0 = 0;
S32 Number1 = 0 ;
Mutex_t *Mutex1;

static Void *FunCall1(Void *Arg)
{
    (Void)Arg;
    S32 Counter = 0;
    for (Counter = 0; Counter < 3; Counter++)
    {   
        MutexLock(Mutex1);
        sleep(1);
        Number0++;
        printf("FunCall1 add  one to num %d\n", Number0);
        MutexUnlock(Mutex1);
    }
    return Null;
}

static Void *FunCall2(Void *Arg)
{
    (Void)Arg;
    S32 Counter = 0;
    for (Counter = 0; Counter < 3; Counter++)
    {   
        MutexLock(Mutex1);
        sleep(1);
        Number0++;
        printf("FunCall2 add  one to num %d\n", Number0);
        MutexUnlock(Mutex1);
    }
    return Null;
}

S32 MutexTest(Void)
{
    pthread_t Id1, Id2;
    
    Mutex1 = MutexCreate();
    if(Null == Mutex1)
    {
        printf("MutexCreate failed!\n");
        return -1;
    }
    
    pthread_create(&Id1, Null, FunCall1, Null);
    pthread_create(&Id2, Null, FunCall2, Null);
    pthread_join(Id1, Null);
    pthread_join(Id2, Null);
    MutexDestroy(Mutex1);
    printf("Mutex Test Success!");
    
    return 0;
}
#endif
