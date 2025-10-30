// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

// Student practice C++ sort keys of unordered map on different containers libraries
// Copyright 2025 AlexBurnes@gmail.com
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <gmock/gmock-matchers.h>
#include <gmock/gmock-more-matchers.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <sort_keys.hpp>

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(TestSortKeysValuesInt, SortKeys) {
    std::unordered_map<int, int> map = {
        {1, 1},
        {3, 3},
        {5, 5},
        {4, 4},
        {2, 2}
    };
    auto             sorted = sort_keys<std::vector<int>, decltype(map)>(map);
    std::vector<int> expect = {1, 2, 3, 4, 5};
    EXPECT_THAT(sorted, ::testing::ContainerEq(expect));
}

TEST(TestSortKeysValuesString, SortKeys) {
    std::unordered_map<int, std::string> map = {
        {1, "1"},
        {3, "3"},
        {5, "5"},
        {4, "4"},
        {2, "2"}
    };
    auto             sorted = sort_keys<std::vector<int>, decltype(map)>(map);
    std::vector<int> expect = {1, 2, 3, 4, 5};
    EXPECT_THAT(sorted, ::testing::ContainerEq(expect));
}

TEST(TestSortKeysValuesInt, SortBigReturnVector) {
    std::unordered_map<int32_t, int32_t> map;
    for (size_t i = 0; i < 1e6; i++) {
        map[std::rand()] = std::rand();
    }
    auto sorted = sort_keys<std::vector<int32_t>, decltype(map)>(map);
    EXPECT_TRUE(std::is_sorted(sorted.begin(), sorted.end()));
}

TEST(TestSortKeysValuesInt, SortBigPassVectorReference) {
    std::unordered_map<int32_t, int32_t> map;
    for (size_t i = 0; i < 1e6; i++) {
        map[std::rand()] = std::rand();
    }
    std::vector<int32_t> sorted;
    sort_keys(sorted, map);
    EXPECT_TRUE(std::is_sorted(sorted.begin(), sorted.end()));
}
