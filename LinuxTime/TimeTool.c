#include "TimeTool.h"

TimeTool_t GetTime(TimeTool_t *Time)
{
    return time(Time);
}

S8 *GetTimeFixedFormatOutPut(const TimeTool_t *Time, S8 *Buf)
{
    return ctime_r(Time, Buf);
}

TimeToolTm_t *GetLocalTime(const TimeTool_t *TimeVal, TimeToolTm_t *Result)
{
    return localtime_r(TimeVal, Result);
}

#ifdef TEST_OPEN
S32 TimeToolTest(Void)
{
    S8 Buf[50];
    TimeTool_t Time;
    TimeToolTm_t NewTime;
    S8 *TimeStr = Null;
    if(-1 == GetTime(&Time))
    {
        printf("GetTime fail!\n");
        goto ErrorHandler;
    }
    printf("Time: %ld\n", Time);
    
    memset(Buf, 0, sizeof(Buf));
    TimeStr = GetTimeFixedFormatOutPut(&Time, Buf);
    if(Null == TimeStr)
    {
        printf("GetTimeFixedFormatOutPut fail!\n");
        goto ErrorHandler;
    }
    printf("TimeStr: %s", TimeStr);
    
    if(Null == GetLocalTime(&Time, &NewTime))
    {
        printf("GetLocalTime fail!\n");
        goto ErrorHandler;
    }
    printf("%d-%d-%d %d:%d:%d\n", NewTime.tm_year + 1900,        \
           NewTime.tm_mon + 1, NewTime.tm_mday, NewTime.tm_hour, \
           NewTime.tm_min, NewTime.tm_sec);
    printf("TimeToolTest Success!\n");
    return 0;
    
ErrorHandler:
    return -1;
}
#endif