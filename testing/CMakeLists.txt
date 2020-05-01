cmake_minimum_required(VERSION 3.13)
project(testing)

set(CMAKE_CXX_STANDARD 14)

include_directories(googletest)

add_executable(testing main.cpp test.h main_test.cpp)

add_subdirectory("${CMAKE_SOURCE_DIR}/googletest")

target_link_libraries( testing gtest gtest_main )