/****************************************************************************
  Copyright(C)    2022, morixinguan@vip.qq.com
  File name :     Process.c
  Author :        Yangyuanxin
  Version:        1.0
  Description:    进程相关接口及测试程序实现
  Other:
  Mode History:
          <author>        <time>      <version>   <desc>
          Yangyuanxin    2024-01-01    V1.0.0.0
****************************************************************************/
#include "Process.h"

S32 ProcessFork(Void)
{
    return fork();
}

S32 ProcessWait(S32 *Status)
{
    return wait(Status);
}

S32 ProcessWaitPid(pid_t Pid, S32 *Status, S32 Options)
{
    return waitpid(Pid, Status, Options);
}

pid_t ProcessGetPid(Void)
{
    return getpid();
}

pid_t ProcessGetPpid(Void)
{
    return getppid();
}

#ifdef TEST_OPEN
S32 ProcessTest(Void)
{
    pid_t Pid;
    S32 Status;

    Pid = ProcessFork();
    if(Pid < 0)
    {
        printf("Fork failed!\n");
        return -1;
    }
    else if(0 == Pid)
    {
        /* 子进程 */
        printf("Child process: PID=%d, PPID=%d\n", ProcessGetPid(), ProcessGetPpid());
        exit(0);
    }
    else
    {
        /* 父进程 */
        printf("Parent process: PID=%d, Child PID=%d\n", ProcessGetPid(), Pid);
        S32 Ret = ProcessWaitPid(Pid, &Status, 0);
        if(Ret < 0)
        {
            printf("WaitPid failed!\n");
            return -1;
        }
        if(WIFEXITED(Status))
        {
            printf("Child exited with code: %d\n", WEXITSTATUS(Status));
        }
    }

    printf("ProcessTest Success!\n");
    return 0;
}
#endif
