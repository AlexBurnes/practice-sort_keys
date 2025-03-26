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
    std::vector<int> sorted = sort_keys(map);
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
    std::vector<int> sorted = sort_keys(map);
    std::vector<int> expect = {1, 2, 3, 4, 5};
    EXPECT_THAT(sorted, ::testing::ContainerEq(expect));
}

TEST(TestSortKeysValuesInt, SortBig) {
    std::unordered_map<int32_t, int32_t> map;
    for(size_t i = 0; i < 1e6; i++) {
        map[std::rand()] = std::rand();
    }
    std::vector<int> sorted = sort_keys(map);
    EXPECT_TRUE(std::is_sorted(sorted.begin(), sorted.end()));
}