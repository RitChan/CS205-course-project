cmake_minimum_required(VERSION 3.16)
project(CourseProject)

set(CMAKE_CXX_STANDARD 14)
include_directories(src src/aggregate)
set(MAJOR )

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

add_executable(main main.cpp)