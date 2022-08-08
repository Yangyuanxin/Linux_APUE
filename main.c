#include "Thread.h"
#include "TimeTool.h"
#include "FileOperate.h"

int main(int argc, char **argv)
{
    printf("Hello LinuxAPUE\n");
    ThreadTest();
    TimeToolTest();
    FileOperateTest();
    return 0;
}
