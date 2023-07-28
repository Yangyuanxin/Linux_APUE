/****************************************************************************
  Copyright(C)    2023, 15078940894@163.com
  File name :     MemoryMap.h
  Author :        Tangping
  Version:        1.0
  Description:    内存映射相关接口及测试程序实现
  Other:
  Mode History:
          <author>        <time>      <version>   <desc>
          Tangping       20223-7-26   V1.0.0.0
****************************************************************************/
#ifndef _MEMORYMAP_H_
#define _MEMORYMAP_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "SystemConfig.h"

#ifdef TEST_OPEN
S32 MemoryMapTest(void);
#endif

#ifdef __cplusplus
}
#endif
#endif  //ifndef _MEMORYMAP_H_
/****************************************************************************/