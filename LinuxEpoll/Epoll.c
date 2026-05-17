/****************************************************************************
  Copyright(C)    2022, morixinguan@vip.qq.com
  File name :     Epoll.c
  Author :        Yangyuanxin
  Version:        1.0
  Description:    Epoll相关接口及测试程序实现
  Other:
  Mode History:
          <author>        <time>      <version>   <desc>
          Yangyuanxin    2024-01-01    V1.0.0.0
****************************************************************************/
#include "Epoll.h"

EpollFd_t EpollCreate(S32 Size)
{
    return epoll_create(Size);
}

S32 EpollCtl(EpollFd_t Epfd, S32 Op, S32 Fd, struct epoll_event *Event)
{
    return epoll_ctl(Epfd, Op, Fd, Event);
}

S32 EpollWait(EpollFd_t Epfd, struct epoll_event *Events, S32 MaxEvents, S32 Timeout)
{
    return epoll_wait(Epfd, Events, MaxEvents, Timeout);
}

S32 EpollAdd(EpollFd_t Epfd, S32 Fd, U32 Events)
{
    struct epoll_event Event;
    Event.events = Events;
    Event.data.fd = Fd;
    return epoll_ctl(Epfd, EPOLL_CTL_ADD, Fd, &Event);
}

S32 EpollDel(EpollFd_t Epfd, S32 Fd)
{
    return epoll_ctl(Epfd, EPOLL_CTL_DEL, Fd, Null);
}

#ifdef TEST_OPEN
#include "Pipe.h"
#include "Thread.h"
#include "FileOperate.h"

#define FIFO_FILE "./epoll_test.fifo"

static Void *WriteThread(Void *Arg)
{
    (Void)Arg;
    S32 Fd = -1;
    S32 Ret = -1;

    Ret = MkFifo(FIFO_FILE, 0777);
    if(Ret < 0)
    {
        printf("MkFifo fail\n");
        return Null;
    }

    Fd = FileOpen(FIFO_FILE, O_WRONLY | O_CREAT);
    if(Fd < 0)
    {
        printf("FileOpen FIFO_FILE fail:%d!\n", Fd);
        return Null;
    }

    Ret = FileWrite(Fd, "EPOLL_TEST", strlen("EPOLL_TEST") + 1);
    if(Ret < 0)
    {
        printf("FileWrite FIFO_FILE fail:%d!\n", Ret);
        FileClose(Fd);
        return Null;
    }

    FileClose(Fd);
    return Null;
}

S32 EpollTest(Void)
{
    S32 Ret;
    S32 Epfd;
    S32 Fd = -1;
    S8 Buff[128] = {0};
    struct epoll_event Events[1];
    Thread_t Tid;

    Epfd = EpollCreate(1);
    if(Epfd < 0)
    {
        printf("EpollCreate fail!\n");
        return -1;
    }

    Ret = ThreadCreate(&Tid, Null, WriteThread, Null);
    if(0 != Ret)
    {
        printf("ThreadCreate fail:%d\n", Ret);
        close(Epfd);
        return -1;
    }

    usleep(1000 * 300);

    Fd = FileOpen(FIFO_FILE, O_RDONLY);
    if(Fd < 0)
    {
        printf("FileOpen FIFO_FILE fail\n");
        close(Epfd);
        return -1;
    }

    Ret = EpollAdd(Epfd, Fd, EPOLLIN);
    if(Ret < 0)
    {
        printf("EpollAdd fail!\n");
        goto ErrorHandler;
    }

    Ret = EpollWait(Epfd, Events, 1, 5000);
    if(Ret <= 0)
    {
        printf("EpollWait fail or timeout!\n");
        goto ErrorHandler;
    }

    if(Events[0].events & EPOLLIN)
    {
        Ret = FileRead(Fd, Buff, sizeof(Buff));
        if(Ret < 0)
        {
            printf("FileRead fail!\n");
            goto ErrorHandler;
        }
        printf("Epoll received data: %s\n", Buff);
    }

    EpollDel(Epfd, Fd);
    FileClose(Fd);
    close(Epfd);
    FileUnlink(FIFO_FILE);

    ThreadJohin(Tid, Null);
    printf("EpollTest Success!\n");
    return 0;

ErrorHandler:
    if(Fd >= 0) FileClose(Fd);
    close(Epfd);
    FileUnlink(FIFO_FILE);
    ThreadJohin(Tid, Null);
    return -1;
}
#endif
