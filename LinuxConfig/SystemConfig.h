/****************************************************************************
  Copyright(C)    2022, morixinguan@vip.qq.com
  File name :     SystemConfig.h
  Author :        Yangyuanxin
  Version:        1.0
  Description:    例程所需要的头文件及数据类型、基础配置
  Other:
  Mode History:
          <author>        <time>      <version>   <desc>
          Yangyuanxin    2022-8-7      V1.0.0.0
          Yangyuanxin    2024-01-01    V1.0.0.1   平台兼容性改造
****************************************************************************/
#ifndef _SYSTEM_CONFIG_H_
#define _SYSTEM_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

#define TEST_OPEN

/* ========== 基础 POSIX 头文件 (跨平台) ========== */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <errno.h>
#include <poll.h>
#include <signal.h>
#include <dirent.h>
#include <termios.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <dlfcn.h>

/* ========== Linux 特有头文件 ========== */
#ifdef __linux__
#include <mqueue.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/vfs.h>
#include <sys/sysinfo.h>
#include <sys/inotify.h>
#include <sys/epoll.h>
#include <linux/i2c.h>
#include <linux/serial.h>
#include <linux/i2c-dev.h>
#endif

/* ========== 类型定义 ========== */
#ifdef  __cplusplus
#define Null    0
#else
#define Null    ((void *)0)
#endif

typedef void               Void;
typedef char               S8;
typedef short              S16;
typedef int                S32;
typedef long long          S64;
typedef unsigned char      U8;
typedef unsigned short     U16;
typedef unsigned int       U32;
typedef unsigned long long U64;
typedef float              Float;
typedef double             Double;
typedef unsigned char      Bool;

#define True 1
#define False 0

#ifdef __cplusplus
}
#endif
#endif  //ifndef _SYSTEM_CONFIG_H_
