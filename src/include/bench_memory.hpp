#pragma once

#include <gperftools/malloc_hook.h>

#include <cstring>

#include "benchmark/benchmark.h"

/// FIXME unable to use a class cause MallocHook require function reference not a std::function

class BenchmarkMemory {
    public:
        explicit BenchmarkMemory(benchmark::State &state)
            : state{state}, g_num_new{0}, g_sum_size_new{0}, g_max_size_new{0}, g_min_size_new{-1} {
            new_hook = [this](const void *, size_t size) {
                ++g_num_new;
                g_sum_size_new += size;
                g_max_size_new = std::max(g_max_size_new, size);
                g_min_size_new = std::min(g_min_size_new, size);
            };
            MallocHook::AddNewHook(new_hook);
        }
        ~BenchmarkMemory() {
            MallocHook::RemoveNewHook(new_hook);
            auto iter = state.iterations();
            state.counters["#new"] = (g_num_new) / iter;
            state.counters["sum_new_B"] = (g_sum_size_new) / iter;
            state.counters["avg_new_B"] = (g_sum_size_new) / (g_num_new);
            state.counters["max_new_B"] = g_max_size_new;
            if (((benchmark::IterationCount)-1) != g_min_size_new) {
                state.counters["min_new_B"] = g_min_size_new;
            }
        }

    private:
        benchmark::State                              &state;
        benchmark::IterationCount                      g_num_new;
        benchmark::IterationCount                      g_sum_size_new;
        benchmark::IterationCount                      g_max_size_new;
        benchmark::IterationCount                      g_min_size_new;
        std::function<void(const void *, size_t size)> new_hook;
};
