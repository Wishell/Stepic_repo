cmake_minimum_required(VERSION 3.5.0)

add_executable(posix_queue posix_queue.cpp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
