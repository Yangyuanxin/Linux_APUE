#include "TCP.h"
#include "Mutex.h"
#include "Timer.h"
#include "Signal.h"
#include "Thread.h"
#include "PollFds.h"
#include "RunExec.h"
#include "TimeTool.h"
#include "PosixSemaphore.h"
#include "DirOperate.h"
#include "FileOperate.h"

int main(int argc, char **argv)
{
    printf("Hello LinuxAPUE\n");
    TCPTest();
    MutexTest();
    TimerTest();
    SignalTest();
    ThreadTest();
    RunExecTest();
    PollFdsTest();
    TimeToolTest();
    DirOperateTest();
    FileOperateTest();
    PosixSemaphoreTest();
    return 0;
}
