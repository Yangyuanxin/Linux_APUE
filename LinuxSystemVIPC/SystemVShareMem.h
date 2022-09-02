/****************************************************************************
  Copyright(C)    2022, morixinguan@vip.qq.com
  File name :     SystemVShareMem.h
  Author :        Yangyuanxin
  Version:        1.0
  Description:    System-V共享内存相关接口及测试程序实现
  Other:
  Mode History:
          <author>        <time>      <version>   <desc>
          Yangyuanxin    2022-9-2      V1.0.0.0
****************************************************************************/
#ifndef _SYSTEM_V_SHARE_MEM_H_
#define _SYSTEM_V_SHARE_MEM_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "SystemConfig.h"

typedef key_t SystemVShareMemKey_t;

S32 SystemVShareMemOpen(SystemVShareMemKey_t Key, S32 MemSize);
S32 SystemVShareMemClose(S32 Fd);

#ifdef TEST_OPEN
S32 SystemVShareMemTest(Void);
#endif

#ifdef __cplusplus
}
#endif
#endif  //ifndef _SYSTEM_V_SHARE_MEM_H_
/****************************************************************************/