cmake_minimum_required(VERSION 3.28)
project(TestCC)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/googletest"
        "googletest"
)

add_executable(
        TestCC
        src/main.cpp
        src/computer.cpp
        src/event.cpp
)

enable_testing()

add_executable(
        hello_test
        tests/hello_test.cc
)
target_link_libraries(
        hello_test
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(hello_test)
