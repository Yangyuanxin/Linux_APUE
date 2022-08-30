/****************************************************************************
  Copyright(C)    2022, morixinguan@vip.qq.com
  File name :     DirOperate.h
  Author :        Yangyuanxin
  Version:        1.0
  Description:    目录操作相关接口及测试程序实现
  Other:
  Mode History:
          <author>        <time>      <version>   <desc>
          Yangyuanxin    2022-8-11     V1.0.0.0
****************************************************************************/
#ifndef _DIR_OPERATE_H_
#define _DIR_OPERATE_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "SystemConfig.h"

typedef DIR Dir_t;
typedef struct statfs DirFs_t;
typedef struct dirent DirGet_t;

Dir_t *OpenDir(const S8 *Name);
S32 CloseDir(Dir_t *Dirp);
DirGet_t *ReadDir(Dir_t *Dirp);
S32 StatFs(const S8 *Path, DirFs_t *Attr);
Bool IsDirExist(const S8 *Path);

#ifdef TEST_OPEN
S32 DirOperateTest(Void);
#endif

#ifdef __cplusplus
}
#endif
#endif  //ifndef _DIR_OPERATE_H_
/****************************************************************************/
