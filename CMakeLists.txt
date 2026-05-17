cmake_minimum_required(VERSION 3.10)
project(Linux_APUE C)

# 默认编译选项
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O3 -g")

# 公共配置头文件路径 (仅 LinuxConfig)
set(CONFIG_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/LinuxConfig)

# 输出到项目根目录的 bin 目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 平台差异: Linux 需要 librt, macOS 不需要
if(UNIX AND NOT APPLE)
    set(RT_LIB rt)
else()
    set(RT_LIB "")
endif()

# ============================================================================
# 辅助函数: 为目标添加依赖模块的头文件路径
# ============================================================================
function(add_module_includes TARGET)
    foreach(MOD_DIR ${ARGN})
        target_include_directories(${TARGET} PRIVATE ${CMAKE_SOURCE_DIR}/${MOD_DIR})
    endforeach()
endfunction()

# ============================================================================
# 定义所有示例目标
# ============================================================================

# --- Dir ---
add_executable(dir_operate
    LinuxDir/DirOperate.c
    LinuxDir/main.c
)
add_module_includes(dir_operate LinuxConfig LinuxDir)

# --- Epoll (Linux only) ---
if(UNIX AND NOT APPLE)
add_executable(epoll
    LinuxEpoll/Epoll.c
    LinuxEpoll/main.c
)
add_module_includes(epoll LinuxConfig LinuxEpoll LinuxPipe LinuxThread LinuxIO)
target_link_libraries(epoll pthread)
endif()

# --- Exec ---
add_executable(run_exec
    LinuxExec/RunExec.c
    LinuxExec/main.c
)
add_module_includes(run_exec LinuxConfig LinuxExec)

# --- Inotify (Linux only) ---
if(UNIX AND NOT APPLE)
add_executable(inotify
    LinuxInotify/Inotify.c
    LinuxInotify/main.c
)
add_module_includes(inotify LinuxConfig LinuxInotify)
endif()

# --- IO ---
add_executable(file_operate
    LinuxIO/FileOperate.c
    LinuxIO/main.c
)
add_module_includes(file_operate LinuxConfig LinuxIO)

# --- MemoryMap ---
add_executable(memory_map
    LinuxMemoryMap/MemoryMap.c
    LinuxThread/Thread.c
    LinuxMemoryMap/main.c
)
add_module_includes(memory_map LinuxConfig LinuxMemoryMap LinuxThread)
target_link_libraries(memory_map pthread)

# --- Mutex ---
add_executable(mutex
    LinuxMutex/Mutex.c
    LinuxMutex/main.c
)
add_module_includes(mutex LinuxConfig LinuxMutex)
target_link_libraries(mutex pthread)

# --- Pipe ---
add_executable(pipe
    LinuxPipe/Pipe.c
    LinuxThread/Thread.c
    LinuxPoll/PollFds.c
    LinuxIO/FileOperate.c
    LinuxPipe/main.c
)
add_module_includes(pipe LinuxConfig LinuxPipe LinuxThread LinuxPoll LinuxIO)
target_link_libraries(pipe pthread)

# --- Poll ---
add_executable(poll_fds
    LinuxPoll/PollFds.c
    LinuxThread/Thread.c
    LinuxIO/FileOperate.c
    LinuxPoll/main.c
)
add_module_includes(poll_fds LinuxConfig LinuxPoll LinuxThread LinuxIO)
target_link_libraries(poll_fds pthread)

# --- PosixMsg (Linux only - uses mqueue.h) ---
if(__linux__)
add_executable(posix_msg
    LinuxPosixIPC/PosixMsg.c
    LinuxPosixIPC/main_msg.c
)
add_module_includes(posix_msg LinuxConfig LinuxPosixIPC)
target_link_libraries(posix_msg pthread ${RT_LIB})
endif()

# --- PosixSemaphore ---
add_executable(posix_semaphore
    LinuxPosixIPC/PosixSemaphore.c
    LinuxPosixIPC/main_semaphore.c
)
add_module_includes(posix_semaphore LinuxConfig LinuxPosixIPC)
target_link_libraries(posix_semaphore pthread)

# --- PosixShm ---
add_executable(posix_shm
    LinuxPosixIPC/PosixShm.c
    LinuxThread/Thread.c
    LinuxPosixIPC/main_shm.c
)
add_module_includes(posix_shm LinuxConfig LinuxPosixIPC LinuxThread)
target_link_libraries(posix_shm pthread ${RT_LIB})

# --- Process ---
add_executable(process
    LinuxProcess/Process.c
    LinuxProcess/main.c
)
add_module_includes(process LinuxConfig LinuxProcess)

# --- SharedLibrary ---
add_executable(shared_library
    LinuxSharedLibrary/SharedLibrary.c
    LinuxSharedLibrary/main.c
)
add_module_includes(shared_library LinuxConfig LinuxSharedLibrary)
target_link_libraries(shared_library dl)

# --- Signal ---
add_executable(signal_test
    LinuxSignal/SigHandle.c
    LinuxSignal/main.c
)
add_module_includes(signal_test LinuxConfig LinuxSignal)

# --- Socket ---
add_executable(tcp
    LinuxSocket/TCP.c
    LinuxThread/Thread.c
    LinuxSocket/main.c
)
add_module_includes(tcp LinuxConfig LinuxSocket LinuxThread)
target_link_libraries(tcp pthread)

# --- SystemInfo ---
add_executable(system_info
    LinuxDir/DirOperate.c
    LinuxSystemInfo/SystemInfo.c
    LinuxSystemInfo/main.c
)
add_module_includes(system_info LinuxConfig LinuxDir LinuxSystemInfo)

# --- SystemVMsg (Linux only - uses sys/ipc.h, sys/msg.h) ---
if(__linux__)
add_executable(systemv_msg
    LinuxSystemVIPC/SystemVMsg.c
    LinuxThread/Thread.c
    LinuxSystemVIPC/main_msg.c
)
add_module_includes(systemv_msg LinuxConfig LinuxSystemVIPC LinuxThread)
target_link_libraries(systemv_msg pthread ${RT_LIB})
endif()

# --- SystemVShareMem (Linux only - uses sys/ipc.h, sys/shm.h) ---
if(__linux__)
add_executable(systemv_shm
    LinuxSystemVIPC/SystemVShareMem.c
    LinuxThread/Thread.c
    LinuxSystemVIPC/main_shm.c
)
add_module_includes(systemv_shm LinuxConfig LinuxSystemVIPC LinuxThread)
target_link_libraries(systemv_shm pthread ${RT_LIB})
endif()

# --- Terminal ---
add_executable(terminal
    LinuxTerminal/Terminal.c
    LinuxTerminal/main.c
)
add_module_includes(terminal LinuxConfig LinuxTerminal)

# --- Thread ---
add_executable(thread
    LinuxThread/Thread.c
    LinuxThread/main.c
)
add_module_includes(thread LinuxConfig LinuxThread)
target_link_libraries(thread pthread)

# --- Time ---
add_executable(time_tool
    LinuxTime/TimeTool.c
    LinuxTime/main.c
)
add_module_includes(time_tool LinuxConfig LinuxTime)

# --- Timer ---
add_executable(timer
    LinuxTimer/Timer.c
    LinuxTimer/main.c
)
add_module_includes(timer LinuxConfig LinuxTimer)

# ============================================================================
# BUILD_TARGET 选择: 只编译指定目标
# 用法: cmake -DBUILD_TARGET=epoll .. 或 cmake -DBUILD_TARGET=all ..
# ============================================================================
set(ALL_TARGETS
    dir_operate run_exec file_operate memory_map mutex
    pipe poll_fds posix_semaphore posix_shm process
    shared_library signal_test tcp system_info
    terminal thread time_tool timer
)

if(UNIX AND NOT APPLE)
    list(APPEND ALL_TARGETS epoll inotify posix_msg systemv_msg systemv_shm)
endif()

if(DEFINED BUILD_TARGET)
    if(BUILD_TARGET STREQUAL "all")
        message(STATUS "Building all targets")
    else()
        # 验证目标是否有效
        if(NOT BUILD_TARGET IN_LIST ALL_TARGETS)
            message(FATAL_ERROR "Unknown target: ${BUILD_TARGET}\nAvailable targets: all, ${ALL_TARGETS}")
        endif()
        # 只保留指定目标
        foreach(t ${ALL_TARGETS})
            if(NOT t STREQUAL BUILD_TARGET)
                if(TARGET ${t})
                    set_target_properties(${t} PROPERTIES EXCLUDE_FROM_ALL TRUE EXCLUDE_FROM_DEFAULT_BUILD TRUE)
                endif()
            endif()
        endforeach()
        message(STATUS "Building target: ${BUILD_TARGET}")
    endif()
else()
    message(STATUS "No BUILD_TARGET specified, building all targets")
    message(STATUS "Usage: cmake -DBUILD_TARGET=<target_name> .. to build a specific target")
    message(STATUS "Available targets: all, ${ALL_TARGETS}")
endif()
