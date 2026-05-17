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
          Yangyuanxin    2024-01-01    V1.0.0.1   跨平台兼容性改造
****************************************************************************/
#include "SystemInfo.h"

S64 GetSystemRunTime(Void)
{
#ifdef __linux__
    S32 Ret = -1;
    SystemInfo_t Info;
    
    Ret = sysinfo(&Info);
    if(Ret != 0)
    {
        printf("call sysinfo fail!\n");
        return -1;
    }
    
    return Info.uptime;
#elif __APPLE__
    S32 Mib[2];
    size_t Size;
    struct timeval Tv;
    
    Mib[0] = CTL_KERN;
    Mib[1] = KERN_BOOTTIME;
    Size = sizeof(Tv);
    
    if(sysctl(Mib, 2, &Tv, &Size, Null, 0) < 0)
    {
        printf("sysctl KERN_BOOTTIME fail!\n");
        return -1;
    }
    S64 BootTime = Tv.tv_sec;
    S64 CurrentTime = (S64)time(Null);
    return CurrentTime - BootTime;
#else
    return -1;
#endif
}

S32 GetMemSize(U64 *Total, U64 *Free)
{
    if(Null == Total || Null == Free)
        return -1;

#ifdef __linux__
    S32 Ret = -1;
    SystemInfo_t Info;
    
    Ret = sysinfo(&Info);
    if(Ret != 0)
    {
        printf("call sysinfo fail!\n");
        return -1;
    }
    
    *Total = Info.totalram;
    *Free = Info.freeram;
    
    return 0;
#elif __APPLE__
    S64 MemSize;
    S32 Mib[2];
    size_t Len;
    S32 Ret;
    
    Mib[0] = CTL_HW;
    Mib[1] = HW_MEMSIZE;
    Len = sizeof(MemSize);
    Ret = sysctl(Mib, 2, &MemSize, &Len, Null, 0);
    if(Ret != 0)
    {
        printf("sysctl HW_MEMSIZE fail!\n");
        return -1;
    }
    *Total = (U64)MemSize;
    *Free = 0; /* macOS 不容易获取精确的空闲物理内存 */

    return 0;
#else
    return -1;
#endif
}

S32 GetDiskInfo(const S8 *Path, Double *Available, Double *Total)
{
    DirVfs_t DiskInfo;
    
    if(Null == Path || Null == Available || Null == Total)
        return -1;
        
    if(!IsDirExist(Path))
        return -1;
    
    if(StatVfs(Path, &DiskInfo) < 0)
        return -1;
        
    U64 BlockSize = DiskInfo.f_frsize;
    U64 TotalSize = BlockSize * DiskInfo.f_blocks;
    U64 AvailableSize = DiskInfo.f_bavail * BlockSize;
    *Available = (Double)AvailableSize;
    *Total = (Double)TotalSize;
    
    return 0;
}

#ifdef TEST_OPEN
S32 SystemInfoTest(Void)
{
    S32 Ret;
    S8 AvUnit[10];
    S8 ToUnit[10];
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
    
    printf("System RunTime = %lld seconds\n", RunTime);
    
    Ret = GetMemSize(&Total, &Free);
    if(Ret < 0)
    {
        printf("GetMemSize fail!\n");
        return -1;
    }
    
    printf("Total Memory = %llu bytes, Free = %llu bytes\n", Total, Free);
    
    memset(AvUnit, 0, sizeof(AvUnit));
    memset(ToUnit, 0, sizeof(ToUnit));
    
    Ret = GetDiskInfo("./", &AvailableSize, &TotalSize);
    if(Ret < 0)
    {
        printf("GetDiskInfo fail!\n");
        goto ErrorHandler;
    }
    
    AvailableSize /= 1024;
    snprintf(AvUnit, sizeof(AvUnit), "%s", "K");
    if(AvailableSize > 1024)
    {
        AvailableSize /= 1024;
        snprintf(AvUnit, sizeof(AvUnit), "%s", "M");
    }
    if(AvailableSize > 1024)
    {
        AvailableSize /= 1024;
        snprintf(AvUnit, sizeof(AvUnit), "%s", "G");
    }
    TotalSize /= 1024;
    snprintf(ToUnit, sizeof(ToUnit), "%s", "K");
    if(TotalSize > 1024)
    {
        TotalSize /= 1024;
        snprintf(ToUnit, sizeof(ToUnit), "%s", "M");
    }
    if(TotalSize > 1024)
    {
        TotalSize /= 1024;
        snprintf(ToUnit, sizeof(ToUnit), "%s", "G");
    }
    
    printf("Disk AvailableSize: %.2lf%s  TotalSize: %.2lf%s\n", AvailableSize, AvUnit, TotalSize, ToUnit);
    printf("SystemInfoTest success!\n");
    
    return 0;
    
ErrorHandler:
    return -1;
}
#endif
