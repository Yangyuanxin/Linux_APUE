/****************************************************************************
  Copyright(C)    2022, morixinguan@vip.qq.com
  File name :     Thread.h
  Author :        Yangyuanxin
  Version:        1.0
  Description:    线程相关接口及测试程序实现
  Other:
  Mode History:
          <author>        <time>      <version>   <desc>
          Yangyuanxin    2022-8-9      V1.0.0.0
          Yangyuanxin    2022-8-20     V1.0.0.1   增加线程分离接口
****************************************************************************/
#ifndef _THREAD_H_
#define _THREAD_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "SystemConfig.h"

typedef pthread_t Thread_t;
typedef pthread_attr_t ThreadAttr_t;

S32 ThreadCreate(Thread_t *Thread, const ThreadAttr_t *Attr, Void *(*ThreadFunc) (Void *), Void *Arg);
S32 ThreadCancel(Thread_t Thread);
Void ThreadExit(Void *Ret);
S32 ThreadJohin(Thread_t Thread, Void **Ret);
S32 ThreadDetach(Thread_t Thread);

#ifdef TEST_OPEN
S32 ThreadTest(Void);
#endif

#ifdef __cplusplus
}
#endif
#endif  //ifndef _THREAD_H_
/****************************************************************************/