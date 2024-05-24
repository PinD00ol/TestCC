cmake_minimum_required(VERSION 3.28)
project(TaskCC)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-O2 -Wall")

add_executable(
        TaskCC
        src/main.cpp
        src/computer.cpp
        src/event.cpp
        src/insertion.cpp
)

project(Tests)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "")

add_subdirectory(
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/googletest"
        "googletest"
)
add_executable(
        tests
        tests/insertion_test.cpp
        src/event.cpp
        src/computer.cpp
        src/insertion.cpp
        tests/computer_test.cpp
        tests/event_test.cpp
)
target_link_libraries(
        tests
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)