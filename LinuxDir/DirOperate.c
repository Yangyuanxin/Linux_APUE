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

S32 ScanListFiles(S8 *Path, S8 *Suffix, Void (*CallBack)(S8 *))
{
    S32 Index = 0;
    S32 Counter = 0;
    S32 FileNum = 0;
    S8  BufSuffix[50];
    DirGet_t **FileList;
    
    if(Null == Path || Null == CallBack)
    {
        printf("Path or CallBack is Null!\n");
        goto ErrorHandler;
    }
    
    if(Null != Suffix)
    {
        memset(BufSuffix, 0, sizeof(BufSuffix));
        strncpy(BufSuffix, Suffix, strlen(Suffix));
        BufSuffix[strlen(Suffix)] = '\0';
    }
    
    FileNum = scandir(Path, &FileList, 0, alphasort);
    if(FileNum < 0)
    {
        printf("scandir fail!\n");
        goto ErrorHandler;
    }
    
    for(Index = 0; Index < FileNum; Index++)
    {
        if (0 == strcmp(FileList[Index]->d_name, ".") || \
            0 == strcmp(FileList[Index]->d_name, ".."))  \
        {
            /*此处也需要释放内存,否则会造成内存泄漏*/
            free(FileList[Index]);
            FileList[Index] = Null;
            continue;
        }
        
        if(Null == Suffix)
        {
            CallBack(FileList[Index]->d_name);
            Counter++;
        }
        else
        {
            if(strstr(FileList[Index]->d_name, BufSuffix))
            {
                CallBack(FileList[Index]->d_name);
                Counter++;
            }
        }
        
        free(FileList[Index]);
        FileList[Index] = Null;
    }
    
    free(FileList);
    FileList = Null;
    
    return Counter;
    
ErrorHandler:
    return -1;
}

#ifdef TEST_OPEN
Void CallBack(S8 *Name)
{
    printf("Name: %s\n", Name);
}

S32 DirOperateTest(Void)
{
    S32 Counter = 0;
    
    Counter = ScanListFiles(".", Null, CallBack);
    if(Counter < 0)
    {
        printf("ScanListFiles fail!\n");
        return -1;
    }
    printf("Have't Suffix Counter = %d\n", Counter);
    
    Counter = ScanListFiles(".", ".txt", CallBack);
    if(Counter < 0)
    {
        printf("ScanListFiles fail!\n");
        return -1;
    }
    printf("Have Suffix Counter = %d\n", Counter);
    printf("DirOperate Test Success!\n");
    return 0;
}
#endif