/****************************************************************************
  Copyright(C)    2022, morixinguan@vip.qq.com
  File name :     PosixSemaphore.h
  Author :        Yangyuanxin
  Version:        1.0
  Description:    Posix信号量相关接口及测试程序实现
  Other:
  Mode History:
          <author>        <time>      <version>   <desc>
          Yangyuanxin    2022-8-24     V1.0.0.0
****************************************************************************/
#ifndef _POSIX_SEMAPHORE_H_
#define _POSIX_SEMAPHORE_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "SystemConfig.h"

typedef sem_t PosixSemaphore_t;

Void *PosixSemaphoreCreate(Void);
S32 PosixSemaphoreDestroy(Void *Sem);
S32 PosixSemaphorePost(Void *Sem);
S32 PosixSemaphoreWait(Void *Sem, U32 TimeoutMs);


#ifdef TEST_OPEN
S32 PosixSemaphoreTest(Void);
#endif

#ifdef __cplusplus
}
#endif
#endif //_POSIX_SEMAPHORE_H_