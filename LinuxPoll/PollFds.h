/****************************************************************************
  Copyright(C)    2022, morixinguan@vip.qq.com
  File name :     PollFds.h
  Author :        Yangyuanxin
  Version:        1.0
  Description:    Poll相关接口及测试程序实现
  Other:
  Mode History:
          <author>        <time>      <version>   <desc>
          Yangyuanxin    2022-8-9      V1.0.0.0
****************************************************************************/
#ifndef _POLL_FDS_H_
#define _POLL_FDS_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "SystemConfig.h"

typedef struct PollFds_t
{
    S32 Fd;         /* file descriptor */
    S16 Events;     /* requested events */
    S16 REVENTS;    /* returned events */
}PollFds_t;

S32 PollFds(PollFds_t *Fds, U64 NumOfFds, S32 TimeOut);

#ifdef TEST_OPEN
S32 PollFdsTest(Void);
#endif

#ifdef __cplusplus
}
#endif
#endif  //ifndef _POLL_FDS_H_
/****************************************************************************/