cmake_minimum_required(VERSION 3.16)
project(CourseProject)

set(CMAKE_CXX_STANDARD 14)
include_directories(includes)
set(MAJOR )

add_executable(CourseProject main.cpp)
add_executable(test test/test_file_0.cpp test/test_main.cpp test/test_header.h test/test_assert.h)
target_include_directories(test PUBLIC test)