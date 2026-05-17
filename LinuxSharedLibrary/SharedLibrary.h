/****************************************************************************
  Copyright(C)    2022, morixinguan@vip.qq.com
  File name :     SharedLibrary.h
  Author :        Yangyuanxin
  Version:        1.0
  Description:    动态库加载相关接口及测试程序实现
  Other:
  Mode History:
          <author>        <time>      <version>   <desc>
          Yangyuanxin    2024-01-01    V1.0.0.0
****************************************************************************/
#ifndef _SHARED_LIBRARY_H_
#define _SHARED_LIBRARY_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "SystemConfig.h"

Void *SharedLibOpen(const S8 *Path);
S32 SharedLibClose(Void *Handle);
Void *SharedLibSym(Void *Handle, const S8 *Symbol);
S8 *SharedLibError(Void);

#ifdef TEST_OPEN
S32 SharedLibraryTest(Void);
#endif

#ifdef __cplusplus
}
#endif
#endif  //ifndef _SHARED_LIBRARY_H_
