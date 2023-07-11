# check cmake
cmake_minimum_required(VERSION 2.8)

project(xtool-3rd-party)

set(THIRD_PARTY_INSTALL_DIR ${PROJECT_SOURCE_DIR}/../3rd-party)

set(CMAKE_INSTALL_PREFIX ${THIRD_PARTY_INSTALL_DIR})

# wget 
# add_subdirectory(googletest-1.13.0)

# wget https://codeload.github.com/google/googletest/tar.gz/refs/tags/release-1.11.0
# add_subdirectory(googletest-release-1.11.0)

# wget https://codeload.github.com/google/googletest/tar.gz/refs/tags/release-1.8.1
add_subdirectory(googletest-release-1.8.1)

# wget https://github.com/danmar/cppcheck/archive/2.10.zip
add_subdirectory(cppcheck-2.10)