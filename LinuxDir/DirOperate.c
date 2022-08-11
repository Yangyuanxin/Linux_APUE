/****************************************************************************
  Copyright(C)    2022, morixinguan@vip.qq.com
  File name :     DirOperate.h
  Author :        Yangyuanxin
  Version:        1.0
  Description:    目录操作相关接口及测试程序实现
  Other:
  Mode History:
          <author>        <time>      <version>   <desc>
          Yangyuanxin    2022-8-11     V1.0.0.0
****************************************************************************/
#include "DirOperate.h"

Dir_t *OpenDir(const S8 *Name)
{
    return opendir(Name);
}

S32 CloseDir(Dir_t *Dirp)
{
    return closedir(Dirp);
}

DirGet_t *ReadDir(Dir_t *Dirp)
{
    return readdir(Dirp);
}

S32 StatFs(const S8 *Path, DirFs_t *Attr)
{
    return statfs(Path, Attr);
}

Bool IsDirExist(const S8 *Path)
{
    Dir_t *CurDir = NULL;
    
    CurDir = OpenDir(Path);
    if(NULL == CurDir)
    {
        return False;
    }
    else
    {
        CloseDir(CurDir);
        return True;
    }
    
    return False;
}

S32 GetDiskSize(const S8 *Path, U64 *DiskSize)
{
    if(IsDirExist(Path))
    {
        DirFs_t DiskInfo;
        StatFs(Path, &DiskInfo);
        *DiskSize = DiskInfo.f_bsize * DiskInfo.f_bavail;
        return 0;
    }
    else
    {
        *DiskSize = 0;
        return -1;
    }
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
        
    BlockSize = DiskInfo.f_bsize;                   // 每个block里包含的字节数
    TotalSize = BlockSize * DiskInfo.f_blocks;      // 总的字节数，f_blocks为block的数目
    AvailableSize = DiskInfo.f_bavail * BlockSize;  // 可用空间大小
    *Available = AvailableSize ;
    *Total = TotalSize ;
    
    return 0 ;
}

#ifdef TEST_OPEN
S32 DirOperateTest(Void)
{
    S8 AvUnit[10];
    S8 ToUnit[10];
    S32 Ret = -1;
    U64 DiskSize;
    Double TotalSize = 0.0;
    Double AvailableSize = 0.0;
    
    memset(AvUnit, 0,sizeof(AvUnit));
    memset(ToUnit, 0,sizeof(ToUnit));
    
    Ret = GetDiskSize("./", &DiskSize);
    if(Ret < 0)
    {
        printf("GetDiskSize fail!\n");
        goto ErrorHandler;
    }
    
    Ret = GetDiskInfo("./", &AvailableSize, &TotalSize);
    if(Ret < 0)
    {
        printf("GetDiskInfo fail!\n");
        goto ErrorHandler;
    }
    
    AvailableSize /= 1024 ;
    if(AvailableSize > 1024){
        AvailableSize /= 1024 ;
        snprintf(AvUnit, sizeof(AvUnit), "%s", "M");
    }
    if(AvailableSize > 1024){
        AvailableSize /= 1024 ;
        snprintf(AvUnit, sizeof(AvUnit), "%s", "G");
    }
    TotalSize /= 1024 ;
    if(TotalSize > 1024){
        TotalSize /= 1024 ;
        snprintf(ToUnit, sizeof(ToUnit), "%s", "M");
    }
    if(TotalSize > 1024){
        TotalSize /= 1024 ;
        snprintf(ToUnit, sizeof(ToUnit), "%s", "G");
    }
    
    printf("Current DiskSize:%lld\n", DiskSize);
    printf("AvailableSize:%.2lf%s  TotalSize:%.2lf%s\n", AvailableSize, AvUnit, TotalSize, ToUnit);
    
    printf("DirOperate Test Success!\n");
    return 0;
    
ErrorHandler:
    return -1;
}
#endif