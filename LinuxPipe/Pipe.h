/****************************************************************************
  Copyright(C)    2022, morixinguan@vip.qq.com
  File name :     Pipe.h
  Author :        Yangyuanxin
  Version:        1.0
  Description:    管道相关接口及测试程序实现
  Other:
  Mode History:
          <author>        <time>      <version>   <desc>
          Yangyuanxin    2022-9-1      V1.0.0.0
****************************************************************************/
#ifndef _PIPE_H_
#define _PIPE_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "SystemConfig.h"

S32 MkFifo(const S8 *Path, S32 Mode);

#ifdef TEST_OPEN
S32 PipeTest(Void);
#endif

#ifdef __cplusplus
}
#endif
#endif  //ifndef _PIPE_H_
/****************************************************************************/