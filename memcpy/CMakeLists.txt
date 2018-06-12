project(memcpy)
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable (memcpy_unit_test memcpy_test.cpp)
target_link_libraries(memcpy_unit_test gtest gtest_main)
add_test(memcpy_unit_test memcpy_unit_test)