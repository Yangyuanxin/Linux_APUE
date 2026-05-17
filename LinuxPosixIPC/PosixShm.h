/****************************************************************************
  Copyright(C)    2022, morixinguan@vip.qq.com
  File name :     PosixShm.h
  Author :        Yangyuanxin
  Version:        1.0
  Description:    Posix共享内存相关接口及测试程序实现
  Other:
  Mode History:
          <author>        <time>      <version>   <desc>
          Yangyuanxin    2022-8-24     V1.0.0.0
          Yangyuanxin    2024-01-01    V1.0.0.1   补全共享内存接口
****************************************************************************/
#ifndef _POSIX_SHM_H_
#define _POSIX_SHM_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "SystemConfig.h"

S32 PosixShmOpen(const S8 *Name, S32 Flags, S32 Mode);
S32 PosixShmClose(S32 Fd);
S32 PosixShmUnlink(const S8 *Name);
S32 PosixShmTruncate(S32 Fd, S64 Length);
Void *PosixShmMmap(Void *Addr, S64 Length, S32 Prot, S32 Flags, S32 Fd, S64 Offset);
S32 PosixShmUnmap(Void *Addr, S64 Length);

#ifdef TEST_OPEN
S32 PosixShmTest(Void);
#endif

#ifdef __cplusplus
}
#endif
#endif //_POSIX_SHM_H_
