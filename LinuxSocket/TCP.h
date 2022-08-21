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
#ifndef _TCP_H_
#define _TCP_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "SystemConfig.h"

typedef struct sockaddr_in AddrIn_t;
typedef struct sockaddr Addr_t;
typedef socklen_t SocketLen_t;

S32 TcpClose(S32 Fd);
S32 TcpOpen(S32 Domain, S32 Type, S32 Protocol);
S32 TcpBind(S32 Fd, Addr_t *Addr, SocketLen_t Len);
S32 TcpListen(S32 Fd, S32 BackLog);
S32 TcpAccept(S32 Fd, AddrIn_t *Addr, SocketLen_t *Len);
S32 TcpConnect(S32 Fd, Addr_t *Addr, SocketLen_t Len);
S32 TcpSend(S32 Fd, S8 *Buff, S32 Len);
S32 TcpRecv(S32 Fd, S8 *Buff, S32 Len);

#ifdef TEST_OPEN
S32 TCPTest(Void);
#endif

#ifdef __cplusplus
}
#endif
#endif  //ifndef _TCP_H_
/****************************************************************************/