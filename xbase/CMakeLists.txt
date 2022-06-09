# check cmake
cmake_minimum_required(VERSION 3.9)
aux_source_directory(. DIR_XBASE_SRCS)
aux_source_directory(mem DIR_XBASE_MEM_SRCS)
aux_source_directory(logger DIR_XBASE_LOGGER_SRCS)
aux_source_directory(common DIR_XBASE_COMMON_SRCS)
add_library(xbase ${DIR_XBASE_SRCS} ${DIR_XBASE_MEM_SRCS} ${DIR_XBASE_LOGGER_SRCS} ${DIR_XBASE_COMMON_SRCS})