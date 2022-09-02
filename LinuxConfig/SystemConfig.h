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
****************************************************************************/
#ifndef _SYSTEM_CONFIG_H_
#define _SYSTEM_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

#define TEST_OPEN
#define OS_LINUX
#ifdef OS_LINUX
#include <poll.h>
#include <time.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <mqueue.h>
#include <dirent.h>
#include <termios.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/vfs.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/sysinfo.h>
#include <linux/serial.h>
#include <linux/i2c-dev.h>
#endif

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

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
/****************************************************************************/