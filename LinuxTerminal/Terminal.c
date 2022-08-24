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


#ifdef TEST_OPEN

S32 TerminalTest(Void)
{
    printf("Terminal Test Success!");
    return 0;
}
#endif