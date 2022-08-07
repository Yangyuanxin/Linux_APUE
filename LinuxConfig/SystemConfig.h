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

#ifdef OS_LINUX_
#include <poll.h>
#include <time.h>
#include <fcntl.h>
#include <errno.h>
#include <mqueue.h>
#include <dirent.h>
#include <termios.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <linux/serial.h>
#include <linux/i2c-dev.h>
#endif

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>


#ifdef __cplusplus
}
#endif
#endif  //ifndef _SYSTEM_CONFIG_H_
/****************************************************************************/