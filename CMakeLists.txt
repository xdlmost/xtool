# check cmake
cmake_minimum_required(VERSION 3.9)
project(xtool)
include_directories("${PROJECT_SOURCE_DIR}")
add_subdirectory(xbase)
add_subdirectory(test)