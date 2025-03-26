#pragma once

template <typename VectorT, typename MapT>
VectorT sort_keys(const MapT &map) {
    VectorT keys(map.size());
    std::transform(map.begin(), map.end(), keys.begin(), [](auto pair) { return pair.first; });
    std::sort(keys.begin(), keys.end());
    return keys;
}
