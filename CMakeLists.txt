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

enable_testing()

find_package(GTest REQUIRED)

add_executable(parser_tests
    tests/parser_test.cpp
    src/protocol/command_parser.cpp
)

target_include_directories(parser_tests PRIVATE include)

target_link_libraries(parser_tests
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(parser_tests)