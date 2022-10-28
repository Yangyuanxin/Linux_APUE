/****************************************************************************
  Copyright(C)    2022, morixinguan@vip.qq.com
  File name :     RunExec.h
  Author :        Yangyuanxin
  Version:        1.0
  Description:    执行器相关接口及测试程序实现
  Other:
  Mode History:
          <author>        <time>      <version>   <desc>
          Yangyuanxin    2022-8-15     V1.0.0.0
****************************************************************************/
#ifndef _RUNEXEC_H_
#define _RUNEXEC_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "SystemConfig.h"

S32 RunExec(S8 *Cmd);
S32 SystemFork(const S8* Cmd);
S32 RunCommond(const S8 *Cmd, S8 *Result);

#ifdef TEST_OPEN
S32 RunExecTest(Void);
#endif

#ifdef __cplusplus
}
#endif
#endif  //ifndef _RUNEXEC_H_
/****************************************************************************/