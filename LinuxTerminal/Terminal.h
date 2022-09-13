/****************************************************************************
  Copyright(C)    2022, morixinguan@vip.qq.com
  File name :     Terminal.h
  Author :        Yangyuanxin
  Version:        1.0
  Description:    终端输出相关接口及测试程序实现
  Other:
  Mode History:
          <author>        <time>      <version>   <desc>
          Yangyuanxin    2022-8-24     V1.0.0.0
****************************************************************************/
#ifndef _TERMINAL_H_
#define _TERMINAL_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "SystemConfig.h"

#define DEV_PATH_LEN 128

enum  DataBit_t
{
    UART_5BIT = 0,
    UART_6BIT,
    UART_7BIT,
    UART_8BIT
};

enum ParityBit_t
{
    NO_Parity = 0,
    ODD_PARITY,
    EVEN_PARITY,
    MARK_PARITY,
    SPACE_PARITY
};

enum StopBit_t
{
    STOP_BITS_1 = 0,
    STOP_BITS_1_5,
    STOP_BITS_2
};

typedef struct UartAttr_t
{
    U32 BaudRate;
    enum  DataBit_t  Len;
    enum ParityBit_t Parity;
    enum StopBit_t   StopBits;
    Bool  DtrDsrOn;
    Bool  RtsCtsOn;
    Bool  XonXoffOn;
}UartAttr_t;

typedef struct TerminalAttr_t
{
    UartAttr_t Attr_t;
    S8 Dev[DEV_PATH_LEN];
    U32 DevFunctionAttr;
}TerminalAttr_t;

S32 TerminalOpen(TerminalAttr_t *Attr);
S32 TerminalClose(S32 Fd);
S32 TerminalWrite(S32 Fd, S8 *Buff, S32 Len);
S32 TerminalRead(S32 Fd, S8 *Buff, S32 Len);

#ifdef TEST_OPEN
S32 TerminalTest(Void);
#endif

#ifdef __cplusplus
}
#endif
#endif //_TERMINAL_H_
