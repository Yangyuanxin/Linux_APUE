/****************************************************************************
  Copyright(C)    2022, morixinguan@vip.qq.com
  File name :     Terminal.c
  Author :        Yangyuanxin
  Version:        1.0
  Description:    终端输出相关接口及测试程序实现
  Other:
  Mode History:
          <author>        <time>      <version>   <desc>
          Yangyuanxin    2022-8-24     V1.0.0.0
****************************************************************************/
#include "Terminal.h"

S32 TerminalOpen(TerminalAttr_t *Attr)
{
    return 0;
}

S32 TerminalClose(S32 Fd)
{
    return close(Fd);
}

S32 TerminalWrite(S32 Fd, S8 *Buff, S32 Len)
{
    return write(Fd, Buff, Len);
}

S32 TerminalRead(S32 Fd, S8 *Buff, S32 Len)
{
    return read(Fd, Buff, Len);
}

#ifdef TEST_OPEN

S32 TerminalTest(Void)
{
    printf("Terminal Test Success!");
    return 0;
}
#endif
