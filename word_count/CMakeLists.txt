project(word_count)
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(word_count_lib word_count.cpp)

add_executable (word_count_unit_test word_count_test.cpp)
target_link_libraries(word_count_unit_test gtest gtest_main)
add_test(word_count_unit_test word_count_unit_test)