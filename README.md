# Linux_APUE

记录关于Linux应用编程的点点滴滴，编程相关例程及总结笔记。

## 项目结构

每个模块为独立的可执行目标，可单独编译运行：

| 模块目录 | 编译目标 | 说明 | 平台 |
|---------|---------|------|------|
| LinuxDir | `dir_operate` | 目录操作：打开/读取/遍历目录、statfs/statvfs | Linux/macOS |
| LinuxEpoll | `epoll` | epoll IO多路复用：创建/添加/删除/等待，配合FIFO测试 | Linux |
| LinuxExec | `run_exec` | exec函数族：execl/execv/execvp等替换进程映像 | Linux/macOS |
| LinuxInotify | `inotify` | 文件系统事件监控：inotify_init/add_watch/read | Linux |
| LinuxIO | `file_operate` | 文件IO操作：open/read/write/lseek/fcntl/stat | Linux/macOS |
| LinuxMemoryMap | `memory_map` | 内存映射：mmap/munmap/msync，多线程读写测试 | Linux/macOS |
| LinuxMutex | `mutex` | 互斥锁：pthread_mutex_init/lock/unlock/destroy | Linux/macOS |
| LinuxPipe | `pipe` | 管道与FIFO：pipe/mkfifo，配合poll多路监听 | Linux/macOS |
| LinuxPoll | `poll_fds` | poll IO多路复用：poll监听标准输入与文件 | Linux/macOS |
| LinuxPosixIPC | `posix_semaphore` | POSIX信号量：sem_open/wait/post/unlink | Linux/macOS |
| LinuxPosixIPC | `posix_shm` | POSIX共享内存：shm_open/mmap读写，多线程测试 | Linux/macOS |
| LinuxPosixIPC | `posix_msg` | POSIX消息队列：mq_open/send/receive/close | Linux |
| LinuxProcess | `process` | 进程管理：fork/wait/getpid/getppid，父子进程通信 | Linux/macOS |
| LinuxSharedLibrary | `shared_library` | 动态库加载：dlopen/dlsym/dlclose | Linux/macOS |
| LinuxSignal | `signal_test` | 信号处理：sigaction/signal/kill，自定义处理函数 | Linux/macOS |
| LinuxSocket | `tcp` | TCP套接字：socket/bind/listen/accept/connect，服务端/客户端通信 | Linux/macOS |
| LinuxSystemInfo | `system_info` | 系统信息：CPU/内存/磁盘/运行时间/主机名 | Linux/macOS |
| LinuxSystemVIPC | `systemv_msg` | System V消息队列：msgget/msgsnd/msgrctl | Linux |
| LinuxSystemVIPC | `systemv_shm` | System V共享内存：shmget/shmat/shmdt/shmctl | Linux |
| LinuxTerminal | `terminal` | 终端操作：tcgetattr/tcsetattr/termios配置 | Linux/macOS |
| LinuxThread | `thread` | 线程操作：pthread_create/join/detach/self | Linux/macOS |
| LinuxTime | `time_tool` | 时间工具：clock_gettime/localtime/strftime/gettimeofday | Linux/macOS |
| LinuxTimer | `timer` | 定时器：timer_create/timer_settime/timer_delete | Linux/macOS |

## 编译和运行

### 1. 克隆项目

```shell
git clone https://github.com/Yangyuanxin/Linux_APUE.git
cd Linux_APUE
```

### 2. 编译所有目标

```shell
mkdir build && cd build
cmake ..
cmake --build .
```

编译产物输出到 `build/bin/` 目录。

### 3. 编译指定目标

通过 `-DBUILD_TARGET=<目标名>` 选择只编译某个示例：

```shell
mkdir build && cd build
cmake -DBUILD_TARGET=time_tool ..
cmake --build .
```

### 4. 运行示例

```shell
./bin/time_tool
./bin/tcp
./bin/file_operate
```

### 5. 内存泄漏检测

```shell
valgrind --tool=memcheck --leak-check=yes --show-reachable=yes ./bin/time_tool
```

## 跨平台说明

- **macOS 可用目标**（18个）：`dir_operate` `run_exec` `file_operate` `memory_map` `mutex` `pipe` `poll_fds` `posix_semaphore` `posix_shm` `process` `shared_library` `signal_test` `tcp` `system_info` `terminal` `thread` `time_tool` `timer`
- **Linux 额外可用目标**（5个）：`epoll` `inotify` `posix_msg` `systemv_msg` `systemv_shm`

> macOS 上已做兼容处理：`sem_timedwait` 用轮询替代、`sysinfo()` 用 `sysctl` 替代、`statfs` 用 `statvfs` 替代等。

## 参与贡献

1. Fork 本仓库
2. 新建 Feat_xxx 分支
3. 提交代码
4. 新建 Pull Request
