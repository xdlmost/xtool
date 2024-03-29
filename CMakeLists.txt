# check cmake
cmake_minimum_required(VERSION 2.8)

project(xtool)

option (LIBRARY_SHARED "build base library into shared library" on)
option (USE_TEST "build with test" on)

# include all cmake files
set (X_PROJECT_DIR "${PROJECT_SOURCE_DIR}")
set (X_PROJECT_CMAKE_DIR "${X_PROJECT_DIR}/cmake")
include("${X_PROJECT_CMAKE_DIR}/cmake_debug.cmake")
include("${X_PROJECT_CMAKE_DIR}/internal_utils.cmake")

x_display_buildin_vars()
x_check_platform()

set (CMAKE_BUILD_TYPE "Debug")
set (OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output)
set (CMAKE_INSTALL_PREFIX ${OUTPUT_PATH})

set (X_BASE_LIB "x_base")


# lib
add_subdirectory(src)

# test
if(USE_TEST)
  add_subdirectory(test)
endif()

# tools
add_subdirectory(tools)