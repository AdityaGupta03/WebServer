#!/bin/bash

echo "Building C++ WebServer..."

# Create build directory and navigate
rm -rf ./build &> /dev/null
mkdir ./build &> /dev/null
cd ./build

# Create log files
> log_build_cmake
> log_build_make

# Builds an executable called "WebServer" from CMakeLists.txt
rm WebServer 2> /dev/null
cmake .. &> log_build_cmake
if [ $? -ne 0 ]; then
  echo "Error: Cmake. Check \"log_build_cmake\" file..."
  exit
fi
make &> log_build_make
if [ $? -ne 0 ]; then
  echo "Error: Make. Check \"log_build_make\" file..."
  exit
fi

echo "Running your WebServer Application..."
echo

# If port passed, specify port to program and run
if [ $# -eq 1 ]; then
  ./WebServer $1
else
  ./WebServer
fi

# Reset current working directory
echo
cd ..