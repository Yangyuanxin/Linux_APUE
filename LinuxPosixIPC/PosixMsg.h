/****************************************************************************
  Copyright(C)    2022, morixinguan@vip.qq.com
  File name :     PosixMsg.h
  Author :        Yangyuanxin
  Version:        1.0
  Description:    Posix消息队列相关接口及测试程序实现
  Other:
  Mode History:
          <author>        <time>      <version>   <desc>
          Yangyuanxin    2022-10-17     V1.0.0.0
****************************************************************************/
#ifndef _POSIX_MSG_H_
#define _POSIX_MSG_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "SystemConfig.h"

#define MAX_MSQ_NUMBER 10
#define MSQ_NAME_SIZE  128

typedef mqd_t PosixMqd_t;
typedef struct mq_attr PosixMqAttr_t ;

S32 PosixMsgClose(PosixMqd_t Fd);
S32 PosixMsqUnlink(const S8 *Name);
S32 PosixMsgRcv(PosixMqd_t Fd, S8 *Buff, S32 Size);
PosixMqd_t PosixMsgOpen(const S8 *Name, S32 Flag);
S32 PosixMsgSnd(PosixMqd_t Fd, const S8 *Buff, S32 Size);
PosixMqd_t PosixMsgSetAttr(PosixMqd_t Fd, PosixMqAttr_t *Attr);
PosixMqd_t PosixMsgGetAttr(PosixMqd_t Fd, PosixMqAttr_t *Attr);

#ifdef TEST_OPEN
S32 PosixMsgTest(Void);
#endif

#ifdef __cplusplus
}
#endif
#endif //_POSIX_MSG_H_