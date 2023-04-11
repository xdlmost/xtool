# check cmake
cmake_minimum_required(VERSION 2.8)

project(xtool-test)

set(TEST_SRCS "main.cc")
aux_source_directory(case/base TEST_CASE_BASE_SRCS)
set(TEST_EXE_NAME "unitTest")

x_define_compile_macros(IMPORT_API)
add_executable(${TEST_EXE_NAME} ${TEST_SRCS} ${TEST_CASE_BASE_SRCS})

# include
target_include_directories(${TEST_EXE_NAME} PUBLIC "${X_PROJECT_DIR}/3rd-party/include")
target_include_directories(${TEST_EXE_NAME} PUBLIC "${X_PROJECT_DIR}/src")

# link directories
link_directories(${X_PROJECT_DIR}/3rd-party/lib64)

# link libraries
target_link_libraries(${TEST_EXE_NAME} PUBLIC gtest)
target_link_libraries(${TEST_EXE_NAME} PUBLIC gtest_main)
target_link_libraries(${TEST_EXE_NAME} PUBLIC pthread)
target_link_libraries(${TEST_EXE_NAME} PUBLIC x_base)

install(TARGETS ${TEST_EXE_NAME}
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/test/
  LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/test/
  ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/test/
)