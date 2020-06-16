cmake_minimum_required(VERSION 3.16)
project(CourseProject)

set(CMAKE_CXX_STANDARD 14)
include_directories(src)
set(MAJOR src/_utility.cpp src/_utility.h)

#add_executable(CourseProject main.cpp src/matrix.h)
add_executable(rtest ${MAJOR} test/test_file_0.cpp test/test_main.cpp test/test_header.h test/test_assert.h test/test_file_1.cpp test/test_file_2.cpp)
target_include_directories(rtest PUBLIC rtest)

# GoogleTest
include_directories(gtestlib/includes/gtest gtestlib/includes)
find_library(GTEST_LIB gtestd PATHS gtestlib PATH_SUFFIXES lib)
find_library(GTEST_MAIN_LIB gtest_maind PATHS gtestlib PATH_SUFFIXES lib)
add_executable(matrix_gtest ${MAJOR} gtest/basicTest.cpp gtest/operatorTest.cpp gtest/statisticTest.cpp gtest/smartArrayTest.cpp gtest/matrixViewTest.cpp)
target_link_libraries(matrix_gtest PUBLIC ${GTEST_LIB} PUBLIC ${GTEST_MAIN_LIB})

# demo
add_executable(demo1 ${MAJOR} demo/simple_ann.cpp)
target_include_directories(demo1 PUBLIC demo)
add_executable(demo2 ${MAJOR} demo/simple_cnn.cpp)
target_include_directories(demo2 PUBLIC demo)