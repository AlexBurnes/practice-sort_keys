cmake_minimum_required(VERSION 3.20)
project(sort_keys CXX)

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

include(CTest)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(out_of_source_dir)
include(pedantic)
include(standart)
include(cppcheck)

find_package(fmt REQUIRED)
find_package(range-v3)
find_package(GTest)
find_package(gperftools)
find_package(benchmark)

enable_testing()

add_subdirectory(src)


