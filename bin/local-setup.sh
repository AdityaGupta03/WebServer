#!/bin/bash

echo "Building C++ WebServer"
echo

# Builds an executable called "WebServer" from CMakeLists.txt
cd ./build
cmake . && make

echo
echo "Running your WebServer Application:"
echo

# Runs executable built by cmake/make
./WebServer

echo
cd ..