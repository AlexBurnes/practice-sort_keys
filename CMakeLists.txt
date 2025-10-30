# Student practice C++ sort keys of unordered map on different containers libraries
# Copyright 2025 AlexBurnes@gmail.com
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

cmake_minimum_required(VERSION 3.20)
project(sort_keys CXX)

set(CMAKE_INSTALL_PREFIX "./")
set(CMAKE_EXPORT_COMPILE_COMMANDS "On")

include(CTest)

include(cmake/modules.cmake)

include(pedantic)

include(build/sparsepp.cmake)

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


