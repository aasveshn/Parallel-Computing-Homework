cmake_minimum_required(VERSION 3.0)

project(ParallelComputingHomework)

set(CMAKE_CXX_STANDARD 11)

add_executable(a.out main.cpp FirstTask/FirstTask.cpp)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

