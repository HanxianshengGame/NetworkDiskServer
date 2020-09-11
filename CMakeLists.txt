cmake_minimum_required(VERSION 3.10)
project(NetworkDiskServer C)

set(CMAKE_C_STANDARD 99)
add_executable(NetworkDiskServer source/ChildThreadWork.c source/DataBaseWork.c source/Epoll.c
        source/main.c source/MessageProtocol.c source/MyLog.c source/TaskQueue.c
        source/TCPServer.c source/TCPServer.c include/MessageProtocol.h)