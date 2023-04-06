# check cmake
cmake_minimum_required(VERSION 2.8)

project(xtool-base)
set (X_BASE_LIB "x_base")

x_define_compile_macros(EXPORT_API)

aux_source_directory(. DIR_XBASE_SRCS)
add_library(${X_BASE_LIB} SHARED ${DIR_XBASE_SRCS} )
target_include_directories(${X_BASE_LIB} PUBLIC "..")

# set so output dir
set_target_properties(${X_BASE_LIB} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_PATH}/lib)

#copy include files
set(X_BASE_OUTPUT_INCLUDE_DIR ${OUTPUT_PATH}/include/base)
set(X_BASE_OUTPUT_LIB_DIR ${OUTPUT_PATH}/lib)

add_custom_command(TARGET ${X_BASE_LIB}
                   POST_BUILD
                   COMMAND echo "copy [base] include files"
                   COMMAND ${CMAKE_COMMAND} -E make_directory  ${X_BASE_OUTPUT_INCLUDE_DIR}
                   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/predefine.h"   ${X_BASE_OUTPUT_INCLUDE_DIR}
                   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/x_memory.h"   ${X_BASE_OUTPUT_INCLUDE_DIR}
                   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/log.h"   ${X_BASE_OUTPUT_INCLUDE_DIR}
                   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/x_array.h"   ${X_BASE_OUTPUT_INCLUDE_DIR}
                   )

add_custom_command(TARGET ${X_BASE_LIB}
                   POST_BUILD
                   COMMAND echo "copy [base] lib files"
                   COMMAND ${CMAKE_COMMAND} -E make_directory  ${X_BASE_OUTPUT_LIB_DIR}
                   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/lib${X_BASE_LIB}.so"   ${X_BASE_OUTPUT_LIB_DIR}
                   )