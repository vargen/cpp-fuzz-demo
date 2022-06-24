cmake_minimum_required(VERSION 3.10)

# set the project name
project(cpp-demo)

# add the executable
#add_executable(cpp-demo cpp-demo.cpp)
add_library(cpp-demo SHARED cpp-demo.cpp)