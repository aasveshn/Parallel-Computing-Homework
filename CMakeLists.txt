cmake_minimum_required(VERSION 3.0)

project(ParallelComputingHomework)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

add_executable(a.out main.cpp FirstTask/FirstTask.cpp SecondTask/SecondTask.cpp ThirdTask/ThirdTask.cpp)

if(OpenMP_CXX_FOUND)
    target_compile_options(ThirdTask/ThirdTask.cpp PRIVATE -fopenmp)
endif()

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

