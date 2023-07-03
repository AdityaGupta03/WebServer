#!/bin/bash

echo "Building C++ WebServer"
echo

# Builds an executable called "WebServer" from CMakeLists.txt
cd ./build
cmake .. && make

echo
echo "Running your WebServer Application:"
echo

# If port passed, specify port to program
if [ $# -eq 1 ]; then
  ./WebServer $1
else
  ./WebServer
fi

echo
cd ..