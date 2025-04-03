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

add_executable(
    test_sort_keys
        test.cpp
)

target_compile_options(
    test_sort_keys 
    PRIVATE 
        -coverage
        -O0
)

target_link_libraries(
    test_sort_keys
    PRIVATE
            GTest::gtest_main
)

target_link_options(
    test_sort_keys
    PRIVATE
        -coverage
)

add_test(
    NAME test_sort_keys
    COMMAND $<TARGET_FILE:test_sort_keys>
)

add_executable(
    test_bench
        bench.cpp
)

target_link_libraries(
    test_bench
        PRIVATE
            benchmark::benchmark_main
            boost::boost
            EASTL::EASTL
            abseil::abseil
            gperftools::gperftools
)


install(
    TARGETS 
        test_sort_keys 
        test_bench
    RUNTIME DESTINATION bin
)