#include <vector>

/*
template <
    template <typename, typename...> class Vector, typename T, typename... VecArgs,
    template <typename, typename...> class Map, typename Key, typename Value, typename... MapArgs>
function name(..., Vector<T, VecArgs...>& vector, Map<Key, Value, Args...>& map
*/

template <template <typename...> class Map, typename Key, typename Value, typename... Optional>
std::vector<Key> sort_keys(const Map<Key, Value, Optional...> &map) {
    std::vector<Key> keys(map.size());
    std::transform(map.begin(), map.end(), keys.begin(), [](auto pair) { return pair.first; });
    std::sort(keys.begin(), keys.end());
    return keys;
}
