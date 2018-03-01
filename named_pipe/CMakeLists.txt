cmake_minimum_required(VERSION 3.5.0)

add_executable(homepipe named_pipe.cpp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
