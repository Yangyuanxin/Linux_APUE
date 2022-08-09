# Linux_APUE
记录关于Linux应用编程的点点滴滴,编程相关例程及总结笔记

#### 1、编译和运行方法

##### 1.1、克隆本项目

```shell
git clone https://github.com/Yangyuanxin/Linux_APUE.git
```

##### 1.2、在根目录下创建build目录并进入该目录

```shell
mkdir build && cd build
```

##### 1.3、执行cmake生成Makefile命令

```shell
cmake ..
```

终端输出：

```shell
root@100ask:~/workspace/Linux_APUE# ls
CMakeLists.txt  LinuxEpoll  LinuxInotify    LinuxPoll      LinuxSharedLibrary  LinuxSystemInfo  LinuxThread  main.c
LICENSE         LinuxExec   LinuxIO         LinuxPosixIPC  LinuxSignal         LinuxSystemVIPC  LinuxTime    README.md
LinuxDir        LinuxFifo   LinuxMemoryMap  LinuxProcess   LinuxSocket         LinuxTerminal    LinuxTimer
root@100ask:~/workspace/Linux_APUE# mkdir build && cd build
root@100ask:~/workspace/Linux_APUE/build# ls
root@100ask:~/workspace/Linux_APUE/build# cmake ..
-- The C compiler identification is GNU 7.5.0
-- The CXX compiler identification is GNU 7.5.0
-- Check for working C compiler: /usr/bin/cc
-- Check for working C compiler: /usr/bin/cc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Check for working CXX compiler: /usr/bin/c++
-- Check for working CXX compiler: /usr/bin/c++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: /home/book/workspace/Linux_APUE/build
root@100ask:~/workspace/Linux_APUE/build# 
```

##### 1.4、执行make并运行

```shell
root@100ask:~/workspace/Linux_APUE/build# make
Scanning dependencies of target a.out
[ 50%] Building C object CMakeFiles/a.out.dir/main.c.o
[100%] Linking C executable a.out
[100%] Built target a.out
root@100ask:~/workspace/Linux_APUE/build# ./a.out 
Hello LinuxAPUE
root@100ask:~/workspace/Linux_APUE/build#
```

##### 1.5、内存泄露测试

```shell
valgrind --tool=memcheck --leak-check=yes --show-reachable=yes ./a.out
```

#### 2、参与贡献

1. Fork 本仓库
2. 新建 Feat_xxx 分支
3. 提交代码
4. 新建 Pull Request
