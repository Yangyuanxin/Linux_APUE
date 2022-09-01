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

S32 TimeSleepMs(U64 Ms)
{
    TimeToolTimeVal_t Tv;
    Tv.tv_sec = 0;
    Tv.tv_usec = Ms*1000;
    return select(0, NULL, NULL, NULL, &Tv);
}

S32 TimeSleepUs(S32 Us)
{
    TimeToolTimeVal_t Tv;
    Tv.tv_sec =     Us / 1000000;
    Tv.tv_usec =    Us % 1000000;

    S32 ret = select(0, NULL, NULL, NULL, &Tv);
    if(0 != ret) 
        return -1;

    return 0;
}

S8 *GetFormatTimeStr(S8 *Str, S32 Len)
{
    S8 DataFmt[20];
    S8 DateMs[4];
    TimeToolTimeVal_t Tv;
    TimeToolTm_t NowTm;
    S32 NowMs;
    TimeTool_t NowSec;
    if (Len < 24) {
        printf("time string Len must bigger than 24\n");
        return NULL;
    }
    if (-1 == gettimeofday(&Tv, NULL)) {
        printf("gettimeofday failed %d:%s\n", errno, strerror(errno));
        return NULL;
    }
    NowSec = Tv.tv_sec;
    NowMs = Tv.tv_usec/1000;
    if (NULL == localtime_r(&NowSec, &NowTm)) {
        printf("localtime_r failed %d:%s\n", errno, strerror(errno));
        return NULL;
    }

    strftime(DataFmt, 20, "%Y-%m-%d %H:%M:%S", &NowTm);
    snprintf(DateMs, sizeof(DateMs), "%03d", NowMs);
    snprintf(Str, Len, "%s.%s", DataFmt, DateMs);
    return Str;
}

#ifdef TEST_OPEN
S32 TimeToolTest(Void)
{
    S8 Buf[50];
    S8 *TimeStr = Null;
    S8 *ForMatStr = Null;
    TimeTool_t Time;
    TimeToolTm_t NewTime;
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
    
    memset(Buf, 0, sizeof(Buf));
    ForMatStr = GetFormatTimeStr(Buf, sizeof(Buf));
    printf("ForMatStr:%s\n", ForMatStr);
           
    printf("TimeToolTest Success!\n");
    return 0;
    
ErrorHandler:
    return -1;
}
#endif