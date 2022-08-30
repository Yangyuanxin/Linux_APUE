/****************************************************************************
  Copyright(C)    2022, morixinguan@vip.qq.com
  File name :     SystemInfo.h
  Author :        Yangyuanxin
  Version:        1.0
  Description:    系统信息相关接口及测试程序实现
  Other:
  Mode History:
          <author>        <time>      <version>   <desc>
          Yangyuanxin    2022-8-15     V1.0.0.0
****************************************************************************/
#ifndef _SYSTEMINFO_H_
#define _SYSTEMINFO_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "DirOperate.h"
#include "SystemConfig.h"

typedef struct sysinfo SystemInfo_t;

S64 GetSystemRunTime(Void);
S32 GetMemSize(U64 *Total, U64 *Free);
S32 GetDiskInfo(const S8 *Path, Double *Available, Double *Total);


#ifdef TEST_OPEN
S32 SystemInfoTest(Void);
#endif

#ifdef __cplusplus
}
#endif
#endif  //ifndef _SYSTEMINFO_H_
/****************************************************************************/