/****************************************************************************
  Copyright(C)    2022, morixinguan@vip.qq.com
  File name :     SystemInfo.c
  Author :        Yangyuanxin
  Version:        1.0
  Description:    系统信息相关接口及测试程序实现
  Other:
  Mode History:
          <author>        <time>      <version>   <desc>
          Yangyuanxin    2022-8-15     V1.0.0.0
****************************************************************************/
#include "SystemInfo.h"

S64 GetSystemRunTime(Void)
{
    S32 Ret = -1;
    SystemInfo_t  Info;
    
    Ret = sysinfo(&Info);
    if(Ret != 0)
    {
        printf("call sysinfo fail!\n");
        return -1;
    }
    
    return Info.uptime;
}

S32 GetMemSize(U64 *Total, U64 *Free)
{
    S32 Ret = -1;
    SystemInfo_t  Info;
    
    Ret = sysinfo(&Info);
    if(Ret != 0)
    {
        printf("call sysinfo fail!\n");
        return -1;
    }
    
    *Total = Info.totalram;
    *Free = Info.freeram;
    
    return 0;
}

S32 GetDiskInfo(const S8 *Path, Double *Available, Double *Total)
{
    U64 BlockSize;
    U64 TotalSize;
    U64 AvailableSize;
    DirFs_t DiskInfo;
    
    if(IsDirExist(Path))
        StatFs(Path, &DiskInfo);
    else
        return -1 ;
        
    BlockSize = DiskInfo.f_bsize;
    TotalSize = BlockSize * DiskInfo.f_blocks;
    AvailableSize = DiskInfo.f_bavail * BlockSize;
    *Available = AvailableSize ;
    *Total = TotalSize ;
    
    return 0 ;
}

#ifdef TEST_OPEN
S32 SystemInfoTest(Void)
{
    S32 Ret;
    S8 AvUnit[10];
    S8 ToUnit[10];
    U64 DiskSize;
    U64 Total, Free;
    U64 RunTime = 0;
    Double TotalSize = 0.0;
    Double AvailableSize = 0.0;
    
    RunTime = GetSystemRunTime();
    if(RunTime < 0)
    {
        printf("GetSystemRunTime fail!\n");
        return -1;
    }
    
    printf("RunTime = %lld\n", RunTime);
    
    Ret = GetMemSize(&Total, &Free);
    if(Ret < 0)
    {
        printf("GetMemSize fail!\n");
        return -1;
    }
    
    memset(AvUnit, 0,sizeof(AvUnit));
    memset(ToUnit, 0,sizeof(ToUnit));
    
    Ret = GetDiskInfo("./", &AvailableSize, &TotalSize);
    if(Ret < 0)
    {
        printf("GetDiskInfo fail!\n");
        goto ErrorHandler;
    }
    
    AvailableSize /= 1024 ;
    if(AvailableSize > 1024)
    {
        AvailableSize /= 1024 ;
        snprintf(AvUnit, sizeof(AvUnit), "%s", "M");
    }
    if(AvailableSize > 1024)
    {
        AvailableSize /= 1024 ;
        snprintf(AvUnit, sizeof(AvUnit), "%s", "G");
    }
    TotalSize /= 1024 ;
    if(TotalSize > 1024)
    {
        TotalSize /= 1024 ;
        snprintf(ToUnit, sizeof(ToUnit), "%s", "M");
    }
    if(TotalSize > 1024)
    {
        TotalSize /= 1024 ;
        snprintf(ToUnit, sizeof(ToUnit), "%s", "G");
    }
    
    printf("Current DiskSize:%lld\n", DiskSize);
    printf("AvailableSize:%.2lf%s  TotalSize:%.2lf%s\n", AvailableSize, AvUnit, TotalSize, ToUnit);
    
    printf("Total = %lld, Free = %lld\n", Total, Free);
    printf("SystemInfoTest success!\n");
    
    return 0;
    
ErrorHandler:
    return -1;
}
#endif