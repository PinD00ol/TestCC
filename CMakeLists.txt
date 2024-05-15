cmake_minimum_required(VERSION 3.28)
project(TestCC)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/33af80a883ddc33d9c0fac0a5b4578301efb18de.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

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
