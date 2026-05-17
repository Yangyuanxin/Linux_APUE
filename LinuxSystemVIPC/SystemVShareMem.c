/****************************************************************************
  Copyright(C)    2022, morixinguan@vip.qq.com
  File name :     SystemVShareMem.c
  Author :        Yangyuanxin
  Version:        1.0
  Description:    System-V共享内存相关接口及测试程序实现
  Other:
  Mode History:
          <author>        <time>      <version>   <desc>
          Yangyuanxin    2022-9-2      V1.0.0.0
          Yangyuanxin    2024-01-01    V1.0.0.1   补全共享内存测试
****************************************************************************/
#include "SystemVShareMem.h"

S32 SystemVShareMemOpen(SystemVShareMemKey_t Key, S32 MemSize)
{
    S32 Fd = -1;
    
    Fd = shmget(Key, MemSize, IPC_CREAT | 0666);
    if(Fd < 0)
    {
        printf("shmget fail!\n");
        return -1;
    }
    
    return Fd;
}

S32 SystemVShareMemClose(S32 Fd)
{
    return shmctl(Fd, IPC_RMID, 0);
}

Void *SystemVShareMemAttach(S32 Fd)
{
    return shmat(Fd, Null, 0);
}

S32 SystemVShareMemDetach(const Void *Addr)
{
    return shmdt(Addr);
}

#ifdef TEST_OPEN
#include "Thread.h"

#define SHM_KEY  1234
#define SHM_SIZE 4096

static Void *WriteThread(Void *Arg)
{
    (Void)Arg;
    S32 Fd;
    S8 *Addr;

    Fd = SystemVShareMemOpen(SHM_KEY, SHM_SIZE);
    if(Fd < 0)
    {
        printf("SystemVShareMemOpen fail!\n");
        return Null;
    }

    Addr = (S8 *)SystemVShareMemAttach(Fd);
    if(Addr == (Void *)-1)
    {
        printf("shmat fail!\n");
        return Null;
    }

    strcpy(Addr, "Hello SystemV Shared Memory!");
    printf("WriteThread wrote: %s\n", Addr);

    SystemVShareMemDetach(Addr);
    return Null;
}

static Void *ReadThread(Void *Arg)
{
    (Void)Arg;
    S32 Fd;
    S8 *Addr;

    Fd = SystemVShareMemOpen(SHM_KEY, SHM_SIZE);
    if(Fd < 0)
    {
        printf("SystemVShareMemOpen fail!\n");
        return Null;
    }

    Addr = (S8 *)SystemVShareMemAttach(Fd);
    if(Addr == (Void *)-1)
    {
        printf("shmat fail!\n");
        return Null;
    }

    printf("ReadThread read: %s\n", Addr);

    SystemVShareMemDetach(Addr);
    SystemVShareMemClose(Fd);
    return Null;
}

S32 SystemVShareMemTest(Void)
{
    S32 Ret;
    Thread_t Id1, Id2;

    Ret = ThreadCreate(&Id1, Null, WriteThread, Null);
    if(0 != Ret)
    {
        printf("ThreadCreate Id1 fail:%d!\n", Ret);
        return -1;
    }

    usleep(1000 * 300);

    Ret = ThreadCreate(&Id2, Null, ReadThread, Null);
    if(0 != Ret)
    {
        printf("ThreadCreate Id2 fail:%d!\n", Ret);
        ThreadJohin(Id1, Null);
        return -1;
    }

    ThreadJohin(Id1, Null);
    ThreadJohin(Id2, Null);

    printf("SystemVShareMemTest Success!\n");
    return 0;
}
#endif
