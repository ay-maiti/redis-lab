find_package(GTest REQUIRED)

add_executable(parser_tests
    parser_test.cpp
    ../src/protocol/command_parser.cpp
)

target_include_directories(parser_tests PRIVATE
    ../include
)

target_link_libraries(parser_tests
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(parser_tests)