/****************************************************************************
  Copyright(C)    2022, morixinguan@vip.qq.com
  File name :     SystemVMsg.h
  Author :        Yangyuanxin
  Version:        1.0
  Description:    System-V消息队列相关接口及测试程序实现
  Other:
  Mode History:
          <author>        <time>      <version>   <desc>
          Yangyuanxin    2022-9-1      V1.0.0.0
****************************************************************************/
#ifndef _SYSTEM_V_MSG_H_
#define _SYSTEM_V_MSG_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "SystemConfig.h"

typedef key_t SystemVMsgKey_t;

S32 SystemVMsgOpen(SystemVMsgKey_t Key);
S32 SystemVMsgSend(S32 Fd, S8 *Buf, S32 Len);
S32 SystemVMsgRecv(S32 Fd, S8 *Buf, S32 Len);
S32 SystemVMsgClose(S32 Fd);

#ifdef TEST_OPEN
S32 SystemVMsgTest(Void);
#endif

#ifdef __cplusplus
}
#endif
#endif  //ifndef _SYSTEM_V_MSG_H_
/****************************************************************************/