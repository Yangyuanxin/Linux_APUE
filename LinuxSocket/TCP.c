/****************************************************************************
  Copyright(C)    2022, morixinguan@vip.qq.com
  File name :     TCP.h
  Author :        Yangyuanxin
  Version:        1.0
  Description:    TCP相关接口及测试程序实现
  Other:
  Mode History:
          <author>        <time>      <version>   <desc>
          Yangyuanxin    2022-8-21     V1.0.0.0
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
S32 TCPTest(Void)
{
  return 0;
}
#endif