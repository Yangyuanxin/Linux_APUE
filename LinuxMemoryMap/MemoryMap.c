/****************************************************************************
  Copyright(C)    2023, 15078940894@163.com
  File name :     MemoryMap.c
  Author :        Tangping
  Version:        1.0
  Description:    内存映射相关接口及测试程序实现
  Other:
  Mode History:
          <author>        <time>      <version>   <desc>
          Tangping       2023-7-26    V1.0.0.0
****************************************************************************/
#include "MemoryMap.h"

#ifdef TEST_OPEN
#include "Thread.h"
static Void *ThreadCallBack1(Void *Arg)
{
    char str[] = "Hello world!";
    char *addr;
    int fd;

    fd = open("mmap_temp_file", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (-1 == fd)
    {
        perror("Create and open file failed\n");
        goto ErrorHandler;
    }

    if(-1 == ftruncate(fd, sizeof(str)))
    {
        perror("Operate file failed!\n");
    }

    addr = (char *)mmap(NULL, sizeof(str), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (addr == MAP_FAILED)
    {
        perror("mmap failed!\n");
        goto ErrorHandler;
    }

    close(fd);
    memcpy(addr, &str, sizeof(str));
    printf("Successfully written data to mmap\n");
    munmap(addr, sizeof(str));

    return Null;

ErrorHandler:

    printf("Written data form mmap Fail!\n");

    return Null;
}

static Void *ThreadCallBack2(Void *Arg)
{
    char *addr;
    int fd;

    fd = open("mmap_temp_file", O_RDONLY);
    if (-1 == fd)
    {
        perror("open failed\n");
        goto ErrorHandler;
    }

    addr = (char *)mmap(NULL, sizeof(char), PROT_READ, MAP_SHARED, fd, 0);
    if (addr == MAP_FAILED)
    {
        perror("mmap failed!\n");
        goto ErrorHandler;
    }
    close(fd);

    printf("Successfully read data form mmap: data = %s\n", addr);
    munmap(addr, sizeof(addr));

    return Null;

ErrorHandler:

    printf("Read data form mmap Fail!\n");

    return Null;
}

S32 MemoryMapTest(void)
{
    S32 Ret;
    Thread_t Id1, Id2;

    Ret = ThreadCreate(&Id1, Null, ThreadCallBack1, Null);
    if (0 != Ret)
    {
        printf("ThreadCreate Id1 fail:%d!", Ret);
        goto ErrorHandler;
    }

    usleep(1000 * 300);

    Ret = ThreadCreate(&Id2, Null, ThreadCallBack2, Null);
    if (0 != Ret)
    {
        printf("ThreadCreate Id2 fail:%d!", Ret);
        goto ErrorHandler;
    }

    Ret = ThreadJohin(Id1, Null);
    if (0 != Ret)
    {
        printf("ThreadJohin fail:%d!", Ret);
        goto ErrorHandler;
    }

    Ret = ThreadJohin(Id2, Null);
    if (0 != Ret)
    {
        printf("ThreadJohin fail:%d!", Ret);
        goto ErrorHandler;
    }

    printf("MemoryMapTest Success!\n");
    return 0;

ErrorHandler:
    return -1;
}
#endif