cmake_minimum_required(VERSION 3.28)
project(TestCC)

set(CMAKE_CXX_STANDARD 20)

add_executable(TestCC)

target_sources(TestCC PRIVATE
    "${CMAKE_SOURCE_DIR}/src/main.cpp"
    "${CMAKE_SOURCE_DIR}/src/compclub/computer.cpp")
