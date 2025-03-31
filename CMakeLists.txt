cmake_minimum_required(VERSION 3.20)
project(sort_keys CXX)

include(CTest)

include(cmake/modules.cmake)

include(pedantic)
include(cppcheck)

find_package(fmt REQUIRED)
find_package(range-v3)
find_package(GTest)
find_package(gperftools)
find_package(benchmark)
find_package(Boost)
find_package(EASTL)
find_package(absl)

enable_testing()

add_subdirectory(src)


