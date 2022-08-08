/****************************************************************************
  Copyright(C)    2022, morixinguan@vip.qq.com
  File name :     FileOperate.h
  Author :        Yangyuanxin
  Version:        1.0
  Description:    文件操作相关接口及测试程序实现
  Other:
  Mode History:
          <author>        <time>      <version>   <desc>
          Yangyuanxin    2022-8-7      V1.0.0.0
****************************************************************************/
#ifndef _FILE_OPERATE_H_
#define _FILE_OPERATE_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "SystemConfig.h"

/******************************************************************************
    功能      : 打开一个文件
    输入      : Path:  文件路径
                Flags: 文件打开标志, 参考man 2 open中的flags
    输出      : 无
    返回值    : 成功返回文件描述符，失败返回 -1，失败原因可通过获取errno得知
    描述      : 无
******************************************************************************/
S32 FileOpen(const S8 *Path, S32 Flags);

/******************************************************************************
    功能      : 往一个文件写入数据
    输入      : Fd:    文件描述符
                Buff:  数据缓冲区 
                Count: 写入数据缓冲区的长度
    输出      : 无
    返回值    : 成功返回写入文件的字节数, 失败返回-1，失败原因可通过获取errno得知
    描述      : 无
******************************************************************************/
S32 FileWrite(S32 Fd, Void *Buff, S32 Count);

/******************************************************************************
    功能      : 从一个文件中读出数据
    输入      : Fd:    文件描述符
                Buff:  数据缓冲区 
                Count: 可能读取文件的长度
    输出      : 无
    返回值    : 成功返回实际读取的字节数, 失败返回-1，失败原因可通过获取errno得知
    描述      : 无
******************************************************************************/
S32 FileRead(S32 Fd, Void *Buff, S32 Count);

/******************************************************************************
    功能      : 移动打开文件的指针位置
    输入      : Fd:      文件描述符
                Offset:  文件偏移大小 
                Whence:  偏移的位置
                         SEEK_SET(文件开头)
                         SEEK_CUR(文件当前位置)
                         SEEK_END(文件的末尾)
    输出      : 无
    返回值    : 移动文件指针后的文件指针位置, 失败返回-1，失败原因可通过获取errno得知
    描述      : 无
******************************************************************************/
S64 FileLseek(S32 Fd, S64 Offset, S32 Whence);

/******************************************************************************
    功能      : 删除一个文件
    输入      : Path:  文件路径
    输出      : 无
    返回值    : 成功返回0，失败返回 -1，失败原因可通过获取errno得知
    描述      : 无
******************************************************************************/
S32 FileUnlink(const S8 *Path);

/******************************************************************************
    功能      : 判断一个文件是否存在
    输入      : Path:  文件路径
    输出      : 无
    返回值    : 成功返回0，失败返回 -1，失败原因可通过获取errno得知
    描述      : 无
******************************************************************************/
S32 FileIsExist(const S8 *Path);

/******************************************************************************
    功能      : 获取文件的大小
    输入      : Path:  文件路径
    输出      : 无
    返回值    : 成功返回文件的大小，失败返回 -1，失败原因可通过获取errno得知
    描述      : 无
******************************************************************************/
U64 GetFileSize(const S8 *Path);

/******************************************************************************
    功能      : 文件关闭
    输入      : Fd:  文件描述符
    输出      : 无
    返回值    : 成功返回0，失败返回 -1，失败原因可通过获取errno得知
    描述      : 无
******************************************************************************/
S32 FileClose(S32 Fd);

#ifdef TEST_OPEN
S32 FileOperateTest(Void);
#endif

#ifdef __cplusplus
}
#endif
#endif  //ifndef _FILE_OPERATE_H_
/****************************************************************************/