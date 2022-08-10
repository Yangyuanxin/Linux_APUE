/****************************************************************************
  Copyright(C)    2022, morixinguan@vip.qq.com
  File name :     FileOperate.h
  Author :        Yangyuanxin
  Version:        1.0
  Description:    文件操作相关接口及测试程序实现
  Other:
  Mode History:
          <author>        <time>      <version>   <desc>
          Yangyuanxin    2022-8-7      V1.0.0.0
****************************************************************************/
#include "FileOperate.h"

S32 FileOpen(const S8 *Path, S32 Flags)
{
    return open(Path, Flags, 0666);
}

S32 FileWrite(S32 Fd, Void *Buff, S32 Count)
{
    return write(Fd, Buff, Count);
}

S32 FileRead(S32 Fd, Void *Buff, S32 Count)
{
    return read(Fd, Buff, Count);
}

S64 FileLseek(S32 Fd, S64 Offset, S32 Whence)
{
    return lseek(Fd, Offset, Whence);
}

S32 FileIsExist(const S8 *Path)
{
    return access(Path, F_OK);
}

S64 GetFileSize(const S8 *Path)
{
    struct stat FileState;
    
    if(0 != FileIsExist(Path))
        return 0;
    
    if(stat(Path, &FileState) < 0)
    {
        printf("%s stat error: %s\n", Path, strerror(errno));
        return -1;
    }
    
    if(FileState.st_size < 0)
        return -2;
    
    return FileState.st_size;
}

S32 FileReName(const S8 *OldFile, const S8 *NewFile)
{
    return rename(OldFile, NewFile);
}

S32 FileUnlink(const S8 *Path)
{
    return unlink(Path);
}

S32 FileClose(S32 Fd)
{
    return close(Fd);
}

#ifdef TEST_OPEN
S32 FileOperateTest(Void)
{
    S32 Fd = -1;
    S32 Ret = -1;
    S8 *Path = "./log.txt";
    S8 *Str = "Hello Linux";
    S8 Buff[15] = {0};
    
    Fd = FileOpen(Path, O_RDWR | O_CREAT);
    if(Fd < 0)
    {
        printf("FileOpen fail:%d!\n", Fd);
        goto ErrorHandler;
    }
    
    /*
    注意,对于字符串指针类型的数据来说,使用
    strlen函数获取长度时是不计算'\0'长度的,
    因此需要加上一个'\0'的长度。
    */
    Ret = FileWrite(Fd, Str, strlen(Str) + 1);
    if(Ret < 0)
    {
        printf("FileWrite fail:%d!\n", Ret);
        goto ErrorHandler;
    }
    
    Ret = FileClose(Fd);
    if(Ret < 0)
    {
        printf("FileClose fail:%d!\n", Ret);
        goto ErrorHandler;
    }
    
    printf("File Write Success!\n");
    
    Fd = FileOpen(Path, O_RDONLY);
    if(Fd < 0)
    {
        printf("FileOpen fail:%d!\n", Fd);
        goto ErrorHandler;
    }
    
    Ret = FileRead(Fd, Buff, sizeof(Buff));
    if(Ret < 0)
    {
        printf("FileRead fail:%d!\n", Ret);
        goto ErrorHandler;
    }
    
    printf("FileSize:%lld Buff: %s  Read Len:%ld\n", \
            GetFileSize(Path), Buff, strlen(Buff) + 1);
    printf("File Read Success!\n");
    
    Ret = FileClose(Fd);
    if(Ret < 0)
    {
        printf("FileClose fail:%d!\n", Ret);
        goto ErrorHandler;
    }
    
    Ret = FileUnlink(Path);
    if(Ret < 0)
    {
        printf("FileUnlink fail:%d!\n", Ret);
        goto ErrorHandler;
    }
    
    printf("FileOperate Test Success!\n");
    return 0;
    
ErrorHandler:
    return -1;
}
#endif
