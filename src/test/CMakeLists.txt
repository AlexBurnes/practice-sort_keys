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
)

add_test(
    NAME test_bench
    COMMAND $<TARGET_FILE:test_bench>
)


install(
    TARGETS 
        test_sort_keys 
        test_bench
    RUNTIME DESTINATION bin
)