#include <benchmark/benchmark.h>

#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <vector>

#include "sort_keys.hpp"

namespace bm = benchmark;

static void sorting(bm::State &state) {
    auto count = static_cast<size_t>(state.range(0));

    std::unordered_map<int32_t, int32_t> map(count);
    for (size_t i = 0; i < count; i++) {
        map[std::rand()] = std::rand();
    }

    for (auto _ : state) {
        auto keys [[maybe_unused]] = sort_keys(map);
        // bm::DoNotOptimize(keys.size());
    }
    state.SetComplexityN(count);
    state.SetItemsProcessed(count * state.iterations());
    state.SetBytesProcessed(count * state.iterations() * sizeof(int32_t) * 2);
}

BENCHMARK(sorting)->Args({10});
BENCHMARK(sorting)->Args({100});
BENCHMARK(sorting)->Args({size_t(1e3)});
BENCHMARK(sorting)->Args({size_t(1e6)});
