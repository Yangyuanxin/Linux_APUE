/****************************************************************************
  Copyright(C)    2022, morixinguan@vip.qq.com
  File name :     Siganl.h
  Author :        Yangyuanxin
  Version:        1.0
  Description:    信号相关接口及测试程序实现
  Other:
  Mode History:
          <author>        <time>      <version>   <desc>
          Yangyuanxin    2022-8-12     V1.0.0.0
****************************************************************************/
#ifndef _SIGNAL_H_
#define _SIGNAL_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "SystemConfig.h"

S32 Signal(S32 SigNum, Void(*Fun)(S32));

#ifdef TEST_OPEN
S32 SignalTest(Void);
#endif

#ifdef __cplusplus
}
#endif
#endif  //ifndef _SIGNAL_H_
/****************************************************************************/