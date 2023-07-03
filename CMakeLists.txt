cmake_minimum_required(VERSION 3.23)
project(WebServer)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(WebServer
        src/server.cpp
        src/server.h)
