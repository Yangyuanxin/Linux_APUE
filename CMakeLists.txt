cmake_minimum_required(VERSION 3.5)
project(Linux_APUE)

set(APUE_ROOT ./)
include_directories(${APUE_ROOT}/LinuxDir)
include_directories(${APUE_ROOT}/LinuxEpoll)
include_directories(${APUE_ROOT}/LinuxExec)
include_directories(${APUE_ROOT}/LinuxFifo)
include_directories(${APUE_ROOT}/LinuxInotify)
include_directories(${APUE_ROOT}/LinuxIO)
include_directories(${APUE_ROOT}/LinuxMemoryMap)
include_directories(${APUE_ROOT}/LinuxPoll)
include_directories(${APUE_ROOT}/LinuxPosixIPC)
include_directories(${APUE_ROOT}/LinuxProcess)
include_directories(${APUE_ROOT}/LinuxSharedLibrary)
include_directories(${APUE_ROOT}/LinuxSignal)
include_directories(${APUE_ROOT}/LinuxSocket)
include_directories(${APUE_ROOT}/LinuxSystemInfo)
include_directories(${APUE_ROOT}/LinuxSystemVIPC)
include_directories(${APUE_ROOT}/LinuxTerminal)
include_directories(${APUE_ROOT}/LinuxThread)
include_directories(${APUE_ROOT}/LinuxTime)
include_directories(${APUE_ROOT}/LinuxTimer)

aux_source_directory(${APUE_ROOT}/LinuxDir              LinuxDir)
aux_source_directory(${APUE_ROOT}/LinuxEpoll            LinuxEpoll)
aux_source_directory(${APUE_ROOT}/LinuxExec             LinuxExec)
aux_source_directory(${APUE_ROOT}/LinuxFifo             LinuxFifo)
aux_source_directory(${APUE_ROOT}/LinuxInotify          LinuxInotify)
aux_source_directory(${APUE_ROOT}/LinuxIO               LinuxIO)
aux_source_directory(${APUE_ROOT}/LinuxMemoryMap        LinuxMemoryMap)
aux_source_directory(${APUE_ROOT}/LinuxPoll             LinuxPoll)
aux_source_directory(${APUE_ROOT}/LinuxPosixIPC         LinuxPosixIPC)
aux_source_directory(${APUE_ROOT}/LinuxProcess          LinuxProcess)
aux_source_directory(${APUE_ROOT}/LinuxSharedLibrary    LinuxSharedLibrary)
aux_source_directory(${APUE_ROOT}/LinuxSignal           LinuxSignal)
aux_source_directory(${APUE_ROOT}/LinuxSocket           LinuxSocket)
aux_source_directory(${APUE_ROOT}/LinuxSystemInfo       LinuxSystemInfo)
aux_source_directory(${APUE_ROOT}/LinuxSystemVIPC       LinuxSystemVIPC)
aux_source_directory(${APUE_ROOT}/LinuxTerminal         LinuxTerminal)
aux_source_directory(${APUE_ROOT}/LinuxThread           LinuxThread)
aux_source_directory(${APUE_ROOT}/LinuxTime             LinuxTime)
aux_source_directory(${APUE_ROOT}/LinuxTimer            LinuxTimer)

set(APUE_SRC
    ${LinuxDir} 
    ${LinuxEpoll} 
    ${LinuxExec} 
    ${LinuxFifo} 
    ${LinuxInotify} 
    ${LinuxIO} 
    ${LinuxMemoryMap} 
    ${LinuxPoll} 
    ${LinuxPosixIPC} 
    ${LinuxProcess} 
    ${LinuxSharedLibrary} 
    ${LinuxSignal} 
    ${LinuxSocket} 
    ${LinuxSystemInfo} 
    ${LinuxSystemVIPC} 
    ${LinuxTerminal} 
    ${LinuxThread} 
    ${LinuxTime} 
    ${LinuxTimer} 
)

set(APP_SRCS 
    ${APUE_ROOT} main.c
    ${APUE_SRC}
)

add_compile_options(-std=gnu99 -Wall -O3 -g -Wno-discarded-qualifiers -Wmaybe-uninitialized)
add_executable(a.out ${APP_SRCS} ${ACDAZZLE_SRCS})
target_link_libraries(a.out pthread rt)