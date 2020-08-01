cmake_minimum_required(VERSION 3.10)

project(LRUCache)
set(CMAKE_CXX_STANDARD 11)
find_package(GTest REQUIRED)
find_package(cereal REQUIRED)

#SET(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage ")
#SET(CMAKE_C_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage ")

enable_testing()
include(GoogleTest)
add_executable(type_RAII_test type_RAII_test.cpp)
target_link_libraries(type_RAII_test PUBLIC GTest::GTest)
gtest_add_tests(TARGET      type_RAII_test
                TEST_SUFFIX .noArgs
                TEST_LIST   noArgsTests
)

