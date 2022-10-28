#include "TCP.h"
#include "Pipe.h"
#include "Mutex.h"
#include "Timer.h"
#include "Signal.h"
#include "Thread.h"
#include "PollFds.h"
#include "RunExec.h"
#include "Terminal.h"
#include "PollFds.h"
#include "PosixMsg.h"
#include "PosixShm.h"
#include "TimeTool.h"
#include "DirOperate.h"
#include "SystemInfo.h"
#include "SystemVMsg.h"
#include "FileOperate.h"
#include "PosixSemaphore.h"

int main(int argc, char **argv)
{
    printf("Hello LinuxAPUE\n");
    TCPTest();
    PipeTest();
    MutexTest();
    TimerTest();
    SignalTest();
    ThreadTest();
    RunExecTest();
    PollFdsTest();
    TimeToolTest();
    //TerminalTest();
    DirOperateTest();
    SystemInfoTest();
    SystemVMsgTest();
    FileOperateTest();
    PosixSemaphoreTest();
    PosixMsgTest();
    
    return 0;
}
