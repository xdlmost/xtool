# check cmake
cmake_minimum_required(VERSION 2.8)

project(xtool-tools)

aux_source_directory(case/base TEST_CASE_BASE_SRCS)

set(TOOLS_NET_INFO "net_infos")
set(TOOLS_NET_INFO_SRC "net_infos.c")

x_define_compile_macros(IMPORT_API)
add_executable(${TOOLS_NET_INFO} ${TOOLS_NET_INFO_SRC})

# include
# target_include_directories(${TOOLS_NET_INFO} PUBLIC "${X_PROJECT_DIR}/3rd-party/include")
target_include_directories(${TOOLS_NET_INFO} PUBLIC "${X_PROJECT_DIR}/src")

# link directories
# link_directories(${X_PROJECT_DIR}/3rd-party/lib64)

# link libraries
# target_link_libraries(${TOOLS_NET_INFO} PUBLIC gtest)
# target_link_libraries(${TOOLS_NET_INFO} PUBLIC gtest_main)
# target_link_libraries(${TOOLS_NET_INFO} PUBLIC pthread)
target_link_libraries(${TOOLS_NET_INFO} PUBLIC x_base)

install(TARGETS ${TOOLS_NET_INFO}
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/tools/
  LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/tools/
  ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/tools/
)