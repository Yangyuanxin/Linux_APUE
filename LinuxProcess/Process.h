/****************************************************************************
  Copyright(C)    2022, morixinguan@vip.qq.com
  File name :     Process.h
  Author :        Yangyuanxin
  Version:        1.0
  Description:    进程相关接口及测试程序实现
  Other:
  Mode History:
          <author>        <time>      <version>   <desc>
          Yangyuanxin    2024-01-01    V1.0.0.0
****************************************************************************/
#ifndef _PROCESS_H_
#define _PROCESS_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "SystemConfig.h"

S32 ProcessFork(Void);
S32 ProcessWait(S32 *Status);
S32 ProcessWaitPid(pid_t Pid, S32 *Status, S32 Options);
pid_t ProcessGetPid(Void);
pid_t ProcessGetPpid(Void);

#ifdef TEST_OPEN
S32 ProcessTest(Void);
#endif

#ifdef __cplusplus
}
#endif
#endif  //ifndef _PROCESS_H_
