cmake_minimum_required(VERSION 3.20)
project(redis_clone)

set(CMAKE_CXX_STANDARD 20)

add_executable(redis_clone src/main.cpp)

#cmake --build build && ./build/redis_clone