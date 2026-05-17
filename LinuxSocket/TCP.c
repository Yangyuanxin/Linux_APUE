/****************************************************************************
  Copyright(C)    2022, morixinguan@vip.qq.com
  File name :     TCP.c
  Author :        Yangyuanxin
  Version:        1.0
  Description:    TCP相关接口及测试程序实现
  Other:
  Mode History:
          <author>        <time>      <version>   <desc>
          Yangyuanxin    2022-8-21     V1.0.0.0
          Yangyuanxin    2024-01-01    V1.0.0.1   补全TCP测试
****************************************************************************/
#include "TCP.h"

S32 TcpClose(S32 Fd)
{
    return close(Fd);
}

S32 TcpOpen(S32 Domain, S32 Type, S32 Protocol)
{
    return socket(Domain, Type, Protocol);
}

S32 TcpBind(S32 Fd, Addr_t *Addr, SocketLen_t Len)
{
    return bind(Fd, Addr, Len);
}

S32 TcpListen(S32 Fd, S32 BackLog)
{
    return listen(Fd, BackLog);
}

S32 TcpAccept(S32 Fd, AddrIn_t *Addr, SocketLen_t *Len)
{
    return accept(Fd, (struct sockaddr *)Addr, (socklen_t *)Len);
}

S32 TcpConnect(S32 Fd, Addr_t *Addr, SocketLen_t Len)
{
    return connect(Fd, (struct sockaddr *)Addr, Len);
}

S32 TcpSend(S32 Fd, S8 *Buff, S32 Len)
{
    return send(Fd, Buff, Len, 0);
}

S32 TcpRecv(S32 Fd, S8 *Buff, S32 Len)
{
    return recv(Fd, Buff, Len, 0);
}

#ifdef TEST_OPEN
#include "Thread.h"

#define TCP_TEST_PORT   9999
#define TCP_TEST_ADDR   "127.0.0.1"
#define TCP_TEST_MSG    "Hello TCP!"
#define TCP_BACKLOG     5

static Void *TcpServerThread(Void *Arg)
{
    (Void)Arg;
    S32 ListenFd, ConnFd;
    AddrIn_t ServerAddr, ClientAddr;
    SocketLen_t ClientLen = sizeof(ClientAddr);
    S8 Buff[128] = {0};
    S32 Ret;

    ListenFd = TcpOpen(AF_INET, SOCK_STREAM, 0);
    if(ListenFd < 0)
    {
        perror("Server TcpOpen");
        return Null;
    }

    S32 Opt = 1;
    setsockopt(ListenFd, SOL_SOCKET, SO_REUSEADDR, &Opt, sizeof(Opt));

    memset(&ServerAddr, 0, sizeof(ServerAddr));
    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_port = htons(TCP_TEST_PORT);
    ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    Ret = TcpBind(ListenFd, (Addr_t *)&ServerAddr, sizeof(ServerAddr));
    if(Ret < 0)
    {
        perror("Server TcpBind");
        TcpClose(ListenFd);
        return Null;
    }

    Ret = TcpListen(ListenFd, TCP_BACKLOG);
    if(Ret < 0)
    {
        perror("Server TcpListen");
        TcpClose(ListenFd);
        return Null;
    }

    printf("Server listening on port %d...\n", TCP_TEST_PORT);

    ConnFd = TcpAccept(ListenFd, &ClientAddr, &ClientLen);
    if(ConnFd < 0)
    {
        perror("Server TcpAccept");
        TcpClose(ListenFd);
        return Null;
    }

    Ret = TcpRecv(ConnFd, Buff, sizeof(Buff));
    if(Ret < 0)
    {
        perror("Server TcpRecv");
        TcpClose(ConnFd);
        TcpClose(ListenFd);
        return Null;
    }
    printf("Server received: %s\n", Buff);

    Ret = TcpSend(ConnFd, "ACK", strlen("ACK") + 1);
    if(Ret < 0)
    {
        perror("Server TcpSend");
    }

    TcpClose(ConnFd);
    TcpClose(ListenFd);
    return Null;
}

static Void *TcpClientThread(Void *Arg)
{
    (Void)Arg;
    S32 Fd;
    AddrIn_t ServerAddr;
    S8 Buff[128] = {0};
    S32 Ret;

    usleep(1000 * 200);

    Fd = TcpOpen(AF_INET, SOCK_STREAM, 0);
    if(Fd < 0)
    {
        perror("Client TcpOpen");
        return Null;
    }

    memset(&ServerAddr, 0, sizeof(ServerAddr));
    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_port = htons(TCP_TEST_PORT);
    inet_pton(AF_INET, TCP_TEST_ADDR, &ServerAddr.sin_addr);

    Ret = TcpConnect(Fd, (Addr_t *)&ServerAddr, sizeof(ServerAddr));
    if(Ret < 0)
    {
        perror("Client TcpConnect");
        TcpClose(Fd);
        return Null;
    }

    Ret = TcpSend(Fd, TCP_TEST_MSG, strlen(TCP_TEST_MSG) + 1);
    if(Ret < 0)
    {
        perror("Client TcpSend");
        TcpClose(Fd);
        return Null;
    }
    printf("Client sent: %s\n", TCP_TEST_MSG);

    Ret = TcpRecv(Fd, Buff, sizeof(Buff));
    if(Ret < 0)
    {
        perror("Client TcpRecv");
        TcpClose(Fd);
        return Null;
    }
    printf("Client received: %s\n", Buff);

    TcpClose(Fd);
    return Null;
}

S32 TCPTest(Void)
{
    S32 Ret;
    Thread_t ServerTid, ClientTid;

    Ret = ThreadCreate(&ServerTid, Null, TcpServerThread, Null);
    if(0 != Ret)
    {
        printf("ThreadCreate Server fail:%d!\n", Ret);
        return -1;
    }

    Ret = ThreadCreate(&ClientTid, Null, TcpClientThread, Null);
    if(0 != Ret)
    {
        printf("ThreadCreate Client fail:%d!\n", Ret);
        ThreadJohin(ServerTid, Null);
        return -1;
    }

    ThreadJohin(ServerTid, Null);
    ThreadJohin(ClientTid, Null);

    printf("TCPTest Success!\n");
    return 0;
}
#endif
