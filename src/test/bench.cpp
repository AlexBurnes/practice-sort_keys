#include <benchmark/benchmark.h>

#include <cstdlib>

#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <vector>

#include <EASTL/vector.h>
#include <EASTL/unordered_map.h>

#include <malloc.h>
//EASTL documenation recommends use void* __cdecl and new uint8_t[size]
void* operator new[](size_t size, const char* name, int flags, unsigned debugFlags, const char* file, int line) {
    //return malloc(size);
    return new uint8_t[size];
}

void* operator new[](
    size_t size, size_t alignment, size_t alignmentOffset, const char* pName, int flags, unsigned debugFlags,
    const char* file, int line
) {
    return memalign(alignment, size);
}

#include <boost/container/vector.hpp>
#include <boost/unordered/unordered_map.hpp>

#include "sparsepp/spp.h"

#include <absl/container/flat_hash_map.h>
#include <absl/container/node_hash_map.h>

#include "sort_keys.hpp"

namespace bm = benchmark;

unsigned int seed = time(nullptr);

template<typename VectorT, typename MapT>
static void sorting(bm::State &state) {
    auto count = static_cast<size_t>(state.range(0));
    std::srand(seed);
    MapT map(count);
    for (size_t i = 0; i < count; i++) {
        map[std::rand()] = std::rand();
    }

    for (auto _ : state) {
        auto keys = sort_keys<std::vector<int32_t>,decltype(map)>(map);
        // bm::DoNotOptimize(keys.size());
    }
    state.SetComplexityN(count);
    state.SetItemsProcessed(count * state.iterations());
    state.SetBytesProcessed(count * state.iterations() * sizeof(int32_t) * 2);
}

template<typename MapT>
static void search(bm::State &state) {
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
}

typedef std::vector<int32_t> std_vec;
typedef std::unordered_map<int32_t, int32_t> std_map;

typedef eastl::vector<int32_t> eastl_vec;
typedef eastl::unordered_map<int32_t, int32_t> eastl_map;

typedef boost::container::vector<int32_t> boost_vec;
typedef boost::unordered::unordered_map<int32_t, int32_t> boost_map;

typedef spp::sparse_hash_map<int32_t, int32_t> spp_map;

typedef absl::flat_hash_map<int32_t, int32_t> absl_flat_map;
typedef absl::node_hash_map<int32_t, int32_t> absl_node_map;

// STD STL
BENCHMARK(sorting<std_vec,std_map>)->Args({10});
BENCHMARK(sorting<std_vec,std_map>)->Args({100});
BENCHMARK(sorting<std_vec,std_map>)->Args({size_t(1e3)});
BENCHMARK(sorting<std_vec,std_map>)->Args({size_t(1e6)});
BENCHMARK(search<std_map>)->Args({size_t(1e6)});

// EASTL STL
BENCHMARK(sorting<eastl_vec,eastl_map>)->Args({10});
BENCHMARK(sorting<eastl_vec,eastl_map>)->Args({100});
BENCHMARK(sorting<eastl_vec,eastl_map>)->Args({size_t(1e3)});
BENCHMARK(sorting<eastl_vec,eastl_map>)->Args({size_t(1e6)});
BENCHMARK(search<eastl_map>)->Args({size_t(1e6)});

// BOOST STL
BENCHMARK(sorting<boost_vec,boost_map>)->Args({10});
BENCHMARK(sorting<boost_vec,boost_map>)->Args({100});
BENCHMARK(sorting<boost_vec,boost_map>)->Args({size_t(1e3)});
BENCHMARK(sorting<boost_vec,boost_map>)->Args({size_t(1e6)});
BENCHMARK(search<boost_map>)->Args({size_t(1e6)});

// SPARSEPP
BENCHMARK(sorting<std_vec,spp_map>)->Args({10});
BENCHMARK(sorting<std_vec,spp_map>)->Args({100});
BENCHMARK(sorting<std_vec,spp_map>)->Args({size_t(1e3)});
BENCHMARK(sorting<std_vec,spp_map>)->Args({size_t(1e6)});
BENCHMARK(search<spp_map>)->Args({size_t(1e6)});

// ABSEIL
BENCHMARK(search<absl_flat_map>)->Args({size_t(1e6)});
BENCHMARK(search<absl_node_map>)->Args({size_t(1e6)});
