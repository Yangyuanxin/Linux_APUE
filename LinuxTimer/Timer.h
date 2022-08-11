/****************************************************************************
  Copyright(C)    2022, morixinguan@vip.qq.com
  File name :     Timer.h
  Author :        Yangyuanxin
  Version:        1.0
  Description:    定时器相关接口及测试程序实现
  Other:
  Mode History:
          <author>        <time>      <version>   <desc>
          Yangyuanxin    2022-8-11     V1.0.0.0
****************************************************************************/
#ifndef _TIMER_H_
#define _TIMER_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "SystemConfig.h"

Void TimerSet(S32 Sec, Void (*Cb)(S32 Sig));

#ifdef TEST_OPEN
S32 TimerTest(Void);
#endif

#ifdef __cplusplus
}
#endif
#endif  //ifndef _TIMER_H_
/****************************************************************************/