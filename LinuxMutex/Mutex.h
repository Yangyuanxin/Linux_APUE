/****************************************************************************
  Copyright(C)    2022, morixinguan@vip.qq.com
  File name :     Mutex.h
  Author :        Yangyuanxin
  Version:        1.0
  Description:    互斥锁相关接口及测试程序实现
  Other:
  Mode History:
          <author>        <time>      <version>   <desc>
          Yangyuanxin    2022-8-24     V1.0.0.0
****************************************************************************/
#ifndef _MUTEX_H_
#define _MUTEX_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "SystemConfig.h"

typedef pthread_mutex_t Mutex_t;

Void *MutexCreate(Void);
S32 MutexDestroy(Void *Mutex);
S32 MutexLock(Void *Mutex);
S32 MutexTryLock(Void *Mutex);
S32 MutexUnlock(Void *Mutex);

#ifdef TEST_OPEN
S32 MutexTest(Void);
#endif

#ifdef __cplusplus
}
#endif
#endif //_MUTEX_H_