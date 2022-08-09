#include "Thread.h"
#include "PollFds.h"
#include "TimeTool.h"
#include "FileOperate.h"

int main(int argc, char **argv)
{
    printf("Hello LinuxAPUE\n");
    ThreadTest();
    PollFdsTest();
    TimeToolTest();
    FileOperateTest();
    return 0;
}
