# check cmake
cmake_minimum_required(VERSION 2.8)

project(${X_BASE_LIB})

x_define_compile_macros(X_BUILD)
aux_source_directory(. DIR_XBASE_SRCS)
add_library(${X_BASE_LIB} SHARED ${DIR_XBASE_SRCS})
target_include_directories(${X_BASE_LIB} PUBLIC ${X_PROJECT_DIR}/src/base/include)

# install 
FILE(GLOB_RECURSE output_h_files CONFIGURE_DEPENDS "include/*.h" )

install(TARGETS ${X_BASE_LIB}
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/
  LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/
  ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/
)

install(FILES ${output_h_files}
  DESTINATION ${CMAKE_INSTALL_PREFIX}/include/base/
)