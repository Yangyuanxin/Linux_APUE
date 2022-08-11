/****************************************************************************
  Copyright(C)    2022, morixinguan@vip.qq.com
  File name :     Timer.c
  Author :        Yangyuanxin
  Version:        1.0
  Description:    定时器相关接口及测试程序实现
  Other:
  Mode History:
          <author>        <time>      <version>   <desc>
          Yangyuanxin    2022-8-11     V1.0.0.0
****************************************************************************/
#include "Timer.h"


Void TimerSet(S32 Sec, Void (*Cb)(S32 Sig))
{
    signal(SIGALRM , Cb);
    alarm(Sec);
}

#ifdef TEST_OPEN
S32 Count = 0;

Void TimerCallBack(S32 Sig)
{
    if(SIGALRM == Sig)
    {
        printf("Hello Timer!\n");
        Count++;
    }
}

S32 TimerTest(Void)
{
    TimerSet(1, TimerCallBack);
    for(;;)
    {
        if(1 == Count)
        {
            Count = 0;
            printf("Timeout!\n");
            break;
        }
        usleep(10);
    }
    printf("Timer Success!\n");
    return 0;
}
#endif