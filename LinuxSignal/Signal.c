/****************************************************************************
  Copyright(C)    2022, morixinguan@vip.qq.com
  File name :     Signal.c
  Author :        Yangyuanxin
  Version:        1.0
  Description:    信号相关接口及测试程序实现
  Other:
  Mode History:
          <author>        <time>      <version>   <desc>
          Yangyuanxin    2022-8-12     V1.0.0.0
****************************************************************************/
#include "Signal.h"

S32 Signal(S32 SigNum, Void(*Fun)(S32))
{
    if(SIG_ERR == signal(SigNum, Fun))
        return -1;
    return 0;
}

Void SignalIgnore(Void)
{
    /*忽略Linux程序产生Broken pipe*/
    /*该接口应于APP运行前调用*/
    sigset_t Set;
    
    sigemptyset(&Set);
    sigaddset(&Set, SIGPIPE);
    sigprocmask(SIG_BLOCK, &Set, Null);
}

#ifdef TEST_OPEN
S32 Flag = 0;
Void SiganlCallBack(S32 Sig)
{
    printf("Sig:%d\n", Sig);
    Flag = 1;
}

S32 SignalTest(Void)
{
    S32 Ret = -1;
    Ret = Signal(1, SiganlCallBack);
    if(0 != Ret)
    {
        printf("Signal fail!\n");
        goto ErrorHandler;
    }
    
    Ret = Signal(2, SiganlCallBack);
    if(0 != Ret)
    {
        printf("Signal fail!\n");
        goto ErrorHandler;
    }
    
    Ret = Signal(3, SiganlCallBack);
    if(0 != Ret)
    {
        printf("Signal fail!\n");
        goto ErrorHandler;
    }
    
    sleep(2);
    raise(3);
    while(!Flag);
    printf("Signal Test Success!\n");
    return 0;
    
ErrorHandler:
    return -1;
}
#endif