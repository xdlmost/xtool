# check cmake
cmake_minimum_required(VERSION 3.9)
add_executable(logger_test "logger_test.c")
target_link_libraries(logger_test xbase)