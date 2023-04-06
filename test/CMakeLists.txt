# check cmake
cmake_minimum_required(VERSION 2.8)

project(xtool-test)

set(TEST_SRCS "main.cc")
aux_source_directory(case/base/log TEST_CASE_SRCS)
set(TEST_EXE_NAME "test")

x_define_compile_macros(IMPORT_API)
add_executable(${TEST_EXE_NAME} ${TEST_SRCS} ${TEST_CASE_SRCS})

# include
target_include_directories(${TEST_EXE_NAME} PUBLIC "${PROJECT_DIR}/3rd-party/include")
target_include_directories(${TEST_EXE_NAME} PUBLIC "${OUTPUT_PATH}/include")

# link directories
link_directories(${PROJECT_DIR}/3rd-party/lib64)
link_directories(${OUTPUT_PATH}/lib)

# link libraries
target_link_libraries(${TEST_EXE_NAME} PUBLIC gtest)
target_link_libraries(${TEST_EXE_NAME} PUBLIC gtest_main)
target_link_libraries(${TEST_EXE_NAME} PUBLIC pthread)
target_link_libraries(${TEST_EXE_NAME} PUBLIC x_base)


