#include "Timer.h"
#include "Thread.h"
#include "PollFds.h"
#include "TimeTool.h"
#include "DirOperate.h"
#include "FileOperate.h"

int main(int argc, char **argv)
{
    printf("Hello LinuxAPUE\n");
    TimerTest();
    ThreadTest();
    PollFdsTest();
    TimeToolTest();
    DirOperateTest();
    FileOperateTest();
    return 0;
}
