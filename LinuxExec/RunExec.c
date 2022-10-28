/****************************************************************************
  Copyright(C)    2022, morixinguan@vip.qq.com
  File name :     RunExec.c
  Author :        Yangyuanxin
  Version:        1.0
  Description:    执行器相关接口及测试程序实现
  Other:
  Mode History:
          <author>        <time>      <version>   <desc>
          Yangyuanxin    2022-8-15     V1.0.0.0
****************************************************************************/
#include "RunExec.h"

S32 RunExec(S8 *Cmd)
{
    S32 Status;
    pid_t ChildPid;
    ChildPid = fork();
    if(ChildPid < 0)
    {
        return -1;
    }
    else if(0 == ChildPid)
    {
        execl("/bin/sh","sh","-c", Cmd, (S8*)Null);
    }
    else
    {
        if(-1 == waitpid(ChildPid, &Status, 0))
            return -1;
        return Status;
    }
    return -1;
}

S32 RunCommond(const S8 *Cmd, S8 *Result) 
{
    S32 Len = 0;
    S32 Ret = 0;
    S8 *P = Result;
    FILE *File = Null;
    S8 Buf[1024] = {0};
    
    if(Null == Cmd || Null == Result)
    {
        printf("Cmd or Result is Null!\n");
        goto ErrorHandler;
    }

    File = popen(Cmd, "r");
    if(Null == File) 
    {
        printf("popen error!\n");
        goto ErrorHandler;
    }

    while(fgets(Buf, sizeof(Buf) - 1, File) != 0)
    {
        Len = strlen(Buf); 
        strncpy(P, Buf, Len);
        P += Len;
    }
    
    pclose(File);
    File = Null;
    
    return 0;

ErrorHandler:
    return Ret;
}

S32 SystemFork(const S8* Cmd)
{
    pid_t  ChildPid;
    S32 Status;
    ChildPid = vfork();
    if (ChildPid == 0)
    {
        execl("/bin/sh", "/bin/sh", "-c", Cmd, (const S8 *) 0);
        perror("execv");
        _exit(-1);
    }
    if (waitpid(ChildPid, (S32 *) &Status, 0) == ChildPid)
    {
        if (WIFEXITED(Status))
        {
            Status = WEXITSTATUS(Status);
            printf("%s(\"%s\") returns %d\n", __FUNCTION__, Cmd, Status);
            return Status;
        }
    }
    return -1;
}


#ifdef TEST_OPEN
S32 RunExecTest(Void)
{
    S32 Ret = 0;
    Ret = RunExec("ls");
    if(Ret < 0)
    {
        printf("RunExec is fail!\n");
        return -1;
    }
    
    Ret = SystemFork("ps");
    if(Ret < 0)
    {
        printf("SystemFork is fail!\n");
        return -1;
    }
    
    return 0;
}
#endif