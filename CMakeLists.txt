cmake_minimum_required(VERSION 3.23)
project(WebServer)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(WebServer
        src/server.cpp
        src/WebServer.h
        src/WebServer.cpp)