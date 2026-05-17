/****************************************************************************
  Copyright(C)    2022, morixinguan@vip.qq.com
  File name :     PosixShm.c
  Author :        Yangyuanxin
  Version:        1.0
  Description:    Posix共享内存相关接口及测试程序实现
  Other:
  Mode History:
          <author>        <time>      <version>   <desc>
          Yangyuanxin    2022-8-24     V1.0.0.0
          Yangyuanxin    2024-01-01    V1.0.0.1   补全共享内存测试
****************************************************************************/
#include "PosixShm.h"

S32 PosixShmOpen(const S8 *Name, S32 Flags, S32 Mode)
{
    S8 ShmName[128];
    if(Null == Name)
    {
        printf("Name is Null\n");
        return -1;
    }
    snprintf(ShmName, sizeof(ShmName), "/%s", Name);
    return shm_open(ShmName, Flags, Mode);
}

S32 PosixShmClose(S32 Fd)
{
    return close(Fd);
}

S32 PosixShmUnlink(const S8 *Name)
{
    S8 ShmName[128];
    if(Null == Name)
    {
        printf("Name is Null\n");
        return -1;
    }
    snprintf(ShmName, sizeof(ShmName), "/%s", Name);
    return shm_unlink(ShmName);
}

S32 PosixShmTruncate(S32 Fd, S64 Length)
{
    return ftruncate(Fd, Length);
}

Void *PosixShmMmap(Void *Addr, S64 Length, S32 Prot, S32 Flags, S32 Fd, S64 Offset)
{
    return mmap(Addr, Length, Prot, Flags, Fd, Offset);
}

S32 PosixShmUnmap(Void *Addr, S64 Length)
{
    return munmap(Addr, Length);
}

#ifdef TEST_OPEN
#include "Thread.h"

#define SHM_NAME "test_shm"
#define SHM_SIZE 4096

static Void *WriteThread(Void *Arg)
{
    (Void)Arg;
    S32 Fd;
    S32 Ret;
    S8 *Addr;

    Fd = PosixShmOpen(SHM_NAME, O_RDWR | O_CREAT, 0666);
    if(Fd < 0)
    {
        perror("PosixShmOpen write");
        return Null;
    }

    Ret = PosixShmTruncate(Fd, SHM_SIZE);
    if(Ret < 0)
    {
        perror("PosixShmTruncate");
        PosixShmClose(Fd);
        return Null;
    }

    Addr = (S8 *)PosixShmMmap(Null, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, Fd, 0);
    if(Addr == MAP_FAILED)
    {
        perror("mmap write");
        PosixShmClose(Fd);
        return Null;
    }

    PosixShmClose(Fd);

    strcpy(Addr, "Hello Posix Shared Memory!");
    printf("WriteThread wrote: %s\n", Addr);

    PosixShmUnmap(Addr, SHM_SIZE);
    return Null;
}

static Void *ReadThread(Void *Arg)
{
    (Void)Arg;
    S32 Fd;
    S8 *Addr;

    Fd = PosixShmOpen(SHM_NAME, O_RDONLY, 0666);
    if(Fd < 0)
    {
        perror("PosixShmOpen read");
        return Null;
    }

    Addr = (S8 *)PosixShmMmap(Null, SHM_SIZE, PROT_READ, MAP_SHARED, Fd, 0);
    if(Addr == MAP_FAILED)
    {
        perror("mmap read");
        PosixShmClose(Fd);
        return Null;
    }

    PosixShmClose(Fd);

    printf("ReadThread read: %s\n", Addr);

    PosixShmUnmap(Addr, SHM_SIZE);
    PosixShmUnlink(SHM_NAME);
    return Null;
}

S32 PosixShmTest(Void)
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

    printf("PosixShm Test Success!\n");
    return 0;
}
#endif
