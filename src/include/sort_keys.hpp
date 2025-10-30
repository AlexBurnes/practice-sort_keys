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

#pragma once

/*
    Example usage with STL:
        std::unorderd_map<int, int> map;
        auto sorted = sort_keys<std::vector<int>,decltype(map)>sort_keys(map)

    Problem how to make usage like this
        std::vector<int> sorted = sort_key(map)

    Solution #1
        template<template<typename ...> class MapT, typename KeyT, typename ValueT, typename... OptionT>
        std::vector<KeyT> sort_keys(const MapT<KeyT,ValueT,OptionT...> &map)
    But this solution not allowed to define any vector container, only std::vector

    Solution #2
        template<
            template<typename ...> class VectT, typename VecValueT, typename... VecOptionT,
            template<typename ...> class MapT, typename MapKeyT, typename MapValueT, typename... MapOptionT
        >
        VectorT<VecValueT, VecOptionT...> sort_keys(const MapT<MapKeyT,MapValueT,MapOptionT...> &map)
    But this solution will not compiled, trouble with variadic typenames for vector and still require
    vec = sort_keys<decltype(vec),decltype(map)>(map)

    Solution #3
        template<
            typename VectorT,
            template<typename ...> class MapT, typename MapKeyT, typename MapValueT, typename... MapOptionT
        >
        sort_keys(VectorT& keys, const MapT<MapKeyT,MapValueT,MapOptionT...> &map)
    Usage: sort_keys(vec, map), simple but this solution works for STL, but EASTL do not compiled for example

    Solution #4
        template <typename VectorT, typename MapT>
        void sort_keys(VectorT& keys, const MapT &map)
    KISS principe

    Task: add concept to accept only VectorT as container type of vector and MapT as container type of map

*/

template <typename VectorT, typename MapT>
VectorT sort_keys(const MapT &map) {
    VectorT keys(map.size());
    std::transform(map.begin(), map.end(), keys.begin(), [](auto pair) { return pair.first; });
    std::sort(keys.begin(), keys.end());
    return keys;
}

template <typename VectorT, typename MapT>
void sort_keys(VectorT &keys, const MapT &map) {
    keys.reserve(map.size());
    std::transform(map.begin(), map.end(), keys.begin(), [](auto pair) { return pair.first; });
    std::sort(keys.begin(), keys.end());
}
