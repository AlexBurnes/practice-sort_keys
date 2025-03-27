#include <EASTL/unordered_map.h>
#include <EASTL/vector.h>
#include <benchmark/benchmark.h>
#include <malloc.h>

#include <algorithm>
#include <cstdlib>
#include <numeric>
#include <unordered_map>
#include <vector>
// EASTL documenation recommends use void* __cdecl and new uint8_t[size]
void* operator new[](size_t size, const char* name, int flags, unsigned debugFlags, const char* file, int line) {
    // return malloc(size);
    return new uint8_t[size];
}

void* operator new[](
    size_t size, size_t alignment, size_t alignmentOffset, const char* pName, int flags, unsigned debugFlags,
    const char* file, int line
) {
    return memalign(alignment, size);
}

#include <gperftools/malloc_hook.h>

#include <cstring>

benchmark::IterationCount g_num_new = 0;
benchmark::IterationCount g_sum_size_new = 0;
benchmark::IterationCount g_max_size_new = 0;
benchmark::IterationCount g_min_size_new = -1;
auto                      new_hook = [](const void*, size_t size) {
    ++g_num_new;
    g_sum_size_new += size;
    g_max_size_new = std::max((long int)g_max_size_new, (long int)size);
    g_min_size_new = std::min((long int)g_min_size_new, (long int)size);
};

#define BENCH_MEM_BEFORE_TEST                                \
    benchmark::IterationCount num_new = g_num_new;           \
    benchmark::IterationCount sum_size_new = g_sum_size_new; \
    g_max_size_new = 0;                                      \
    g_min_size_new = -1;                                     \
    MallocHook::AddNewHook(new_hook);

#define BENCH_MEM_AFTER_TEST                                                                      \
    MallocHook::RemoveNewHook(new_hook);                                                          \
    auto iter = state.iterations();                                                               \
    state.counters["#new"] = (g_num_new - num_new) / iter;                                        \
    state.counters["sum_new_B"] = (g_sum_size_new - sum_size_new) / iter;                         \
    state.counters["avg_new_B"] =                                                                 \
        (g_num_new - num_new) == 0 ? 0 : (g_sum_size_new - sum_size_new) / (g_num_new - num_new); \
    state.counters["max_new_B"] = g_max_size_new;                                                 \
    if (((benchmark::IterationCount) - 1) != g_min_size_new) {                                    \
        state.counters["min_new_B"] = g_min_size_new;                                             \
    }

#include <absl/container/flat_hash_map.h>
#include <absl/container/node_hash_map.h>

#include <boost/container/vector.hpp>
#include <boost/unordered/unordered_map.hpp>

#include "sort_keys.hpp"
#include "sparsepp/spp.h"

namespace bm = benchmark;

unsigned int seed = time(nullptr);

static void memory_test(bm::State& state) {
    BENCH_MEM_BEFORE_TEST
    for (auto _ : state) {
        void* ret1 = malloc(state.range(0));
        void* ret2 = malloc(state.range(1));
        void* ret3 = malloc(state.range(2));
        free(ret1);
        free(ret2);
        free(ret3);
    }
    BENCH_MEM_AFTER_TEST
}
BENCHMARK(memory_test)->Args({32, 128, 32});
BENCHMARK(memory_test)->Args({320, 640, 960});

template <typename VectorT, typename MapT>
static void sorting(bm::State& state) {
    BENCH_MEM_BEFORE_TEST
    auto count = static_cast<size_t>(state.range(0));
    std::srand(seed);
    MapT map(count);
    for (size_t i = 0; i < count; i++) {
        map[std::rand()] = std::rand();
    }
    for (auto _ : state) {
        auto keys = sort_keys<VectorT, decltype(map)>(map);
        // bm::DoNotOptimize(keys.size());
    }
    state.SetComplexityN(count);
    state.SetItemsProcessed(count * state.iterations());
    state.SetBytesProcessed(count * state.iterations() * sizeof(int32_t) * 2);
    BENCH_MEM_AFTER_TEST
}

template <typename VectorT, typename MapT>
static void sort_keys(bm::State& state) {
    BENCH_MEM_BEFORE_TEST
    auto count = static_cast<size_t>(state.range(0));
    std::srand(seed);
    MapT map(count);
    for (size_t i = 0; i < count; i++) {
        map[std::rand()] = std::rand();
    }
    VectorT keys;
    for (auto _ : state) {
        sort_keys(keys, map);
        // bm::DoNotOptimize(keys.size());
    }
    state.SetComplexityN(count);
    state.SetItemsProcessed(count * state.iterations());
    state.SetBytesProcessed(count * state.iterations() * sizeof(int32_t) * 2);
    BENCH_MEM_AFTER_TEST
}

template <typename MapT>
static void search(bm::State& state) {
    BENCH_MEM_BEFORE_TEST
    auto count = static_cast<size_t>(state.range(0));
    std::srand(seed);
    MapT map(count);
    for (size_t i = 0; i < count; i++) {
        map[std::rand()] = std::rand();
    }

    int32_t key = std::rand();

    for (auto _ : state) {
        auto value = map.count(key);
    }

    state.SetComplexityN(1);
    state.SetItemsProcessed(count * state.iterations());
    state.SetBytesProcessed(count * state.iterations() * sizeof(int32_t) * 2);
    BENCH_MEM_AFTER_TEST
}

typedef std::vector<int32_t>                 std_vec;
typedef std::unordered_map<int32_t, int32_t> std_map;

typedef eastl::vector<int32_t>                 eastl_vec;
typedef eastl::unordered_map<int32_t, int32_t> eastl_map;

typedef boost::container::vector<int32_t>                 boost_vec;
typedef boost::unordered::unordered_map<int32_t, int32_t> boost_map;

typedef spp::sparse_hash_map<int32_t, int32_t> spp_map;

typedef absl::flat_hash_map<int32_t, int32_t> absl_flat_map;
typedef absl::node_hash_map<int32_t, int32_t> absl_node_map;

// STD STL
BENCHMARK(sorting<std_vec, std_map>)->Args({10});
BENCHMARK(sorting<std_vec, std_map>)->Args({100});
BENCHMARK(sorting<std_vec, std_map>)->Args({size_t(1e3)});
BENCHMARK(sorting<std_vec, std_map>)->Args({size_t(1e6)});
BENCHMARK(sort_keys<std_vec, std_map>)->Args({size_t(1e6)});
BENCHMARK(search<std_map>)->Args({size_t(1e6)});

// EASTL STL
BENCHMARK(sorting<eastl_vec, eastl_map>)->Args({10});
BENCHMARK(sorting<eastl_vec, eastl_map>)->Args({100});
BENCHMARK(sorting<eastl_vec, eastl_map>)->Args({size_t(1e3)});
BENCHMARK(sorting<eastl_vec, eastl_map>)->Args({size_t(1e6)});
BENCHMARK(sort_keys<eastl_vec, eastl_map>)->Args({size_t(1e6)});
BENCHMARK(search<eastl_map>)->Args({size_t(1e6)});

// BOOST STL
BENCHMARK(sorting<boost_vec, boost_map>)->Args({10});
BENCHMARK(sorting<boost_vec, boost_map>)->Args({100});
BENCHMARK(sorting<boost_vec, boost_map>)->Args({size_t(1e3)});
BENCHMARK(sorting<boost_vec, boost_map>)->Args({size_t(1e6)});
BENCHMARK(sort_keys<boost_vec, boost_map>)->Args({size_t(1e6)});
BENCHMARK(search<boost_map>)->Args({size_t(1e6)});

// SPARSEPP
BENCHMARK(sorting<std_vec, spp_map>)->Args({10});
BENCHMARK(sorting<std_vec, spp_map>)->Args({100});
BENCHMARK(sorting<std_vec, spp_map>)->Args({size_t(1e3)});
BENCHMARK(sorting<std_vec, spp_map>)->Args({size_t(1e6)});
BENCHMARK(sort_keys<std_vec, spp_map>)->Args({size_t(1e6)});
BENCHMARK(search<spp_map>)->Args({size_t(1e6)});

// ABSEIL
BENCHMARK(search<absl_flat_map>)->Args({size_t(1e6)});
BENCHMARK(search<absl_node_map>)->Args({size_t(1e6)});

// BEST
BENCHMARK(sorting<eastl_vec, spp_map>)->Args({size_t(1e6)});
BENCHMARK(sort_keys<eastl_vec, spp_map>)->Args({size_t(1e6)});