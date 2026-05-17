/****************************************************************************
  Copyright(C)    2022, morixinguan@vip.qq.com
  File name :     Epoll.h
  Author :        Yangyuanxin
  Version:        1.0
  Description:    Epoll相关接口及测试程序实现
  Other:
  Mode History:
          <author>        <time>      <version>   <desc>
          Yangyuanxin    2024-01-01    V1.0.0.0
****************************************************************************/
#ifndef _EPOLL_H_
#define _EPOLL_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "SystemConfig.h"

typedef S32 EpollFd_t;

EpollFd_t EpollCreate(S32 Size);
S32 EpollCtl(EpollFd_t Epfd, S32 Op, S32 Fd, struct epoll_event *Event);
S32 EpollWait(EpollFd_t Epfd, struct epoll_event *Events, S32 MaxEvents, S32 Timeout);
S32 EpollAdd(EpollFd_t Epfd, S32 Fd, U32 Events);
S32 EpollDel(EpollFd_t Epfd, S32 Fd);

#ifdef TEST_OPEN
S32 EpollTest(Void);
#endif

#ifdef __cplusplus
}
#endif
#endif  //ifndef _EPOLL_H_
