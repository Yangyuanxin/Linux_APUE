/****************************************************************************
  Copyright(C)    2022, morixinguan@vip.qq.com
  File name :     FileOperate.h
  Author :        Yangyuanxin
  Version:        1.0
  Description:    时间相关接口及测试程序实现
  Other:
  Mode History:
          <author>        <time>      <version>   <desc>
          Yangyuanxin    2022-8-7      V1.0.0.0
****************************************************************************/
#ifndef _TIME_TOOL_H_
#define _TIME_TOOL_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "SystemConfig.h"

typedef time_t TimeTool_t;
typedef struct tm TimeToolTm_t;

TimeTool_t GetTime(TimeTool_t *Time);
S8 *GetTimeFixedFormatOutPut(const TimeTool_t *Time, S8 *Buf);
TimeToolTm_t *GetLocalTime(const TimeTool_t *TimeVal, TimeToolTm_t *Result);


#ifdef TEST_OPEN
S32 TimeToolTest(Void);
#endif

#ifdef __cplusplus
}
#endif
#endif  //ifndef _TIME_TOOL_H_
/****************************************************************************/