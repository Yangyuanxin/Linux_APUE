/****************************************************************************
  Copyright(C)    2022, morixinguan@vip.qq.com
  File name :     Semaphore.h
  Author :        Yangyuanxin
  Version:        1.0
  Description:    信号量相关接口及测试程序实现
  Other:
  Mode History:
          <author>        <time>      <version>   <desc>
          Yangyuanxin    2022-8-24     V1.0.0.0
****************************************************************************/
#ifndef _SEMAPHORE_H_
#define _SEMAPHORE_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "SystemConfig.h"

typedef sem_t Semaphore_t;

Void *SemaphoreCreate(Void);
S32 SemaphoreDestroy(Void *Sem);
S32 SemaphorePost(Void *Sem);
S32 SemaphoreWait(Void *Sem, U32 TimeoutMs);


#ifdef TEST_OPEN
S32 SemaphoreTest(Void);
#endif

#ifdef __cplusplus
}
#endif
#endif //_SEMAPHORE_H_