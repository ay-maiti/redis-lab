cmake_minimum_required(VERSION 3.10)

project(redis_lab)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(redis_lab
    src/main.cpp
    src/server/blocking_server.cpp
    src/protocol/command_parser.cpp
    src/dispatcher/command_dispatcher.cpp
    src/storage/storage_engine.cpp
)