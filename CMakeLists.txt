cmake_minimum_required(VERSION 3.16)

project(VantaCrypt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(vcrypt_core

    core/crypto_engine.cpp
    core/key_schedule.cpp
    core/transforms.cpp
    core/serializer.cpp
    core/file_io.cpp
    core/hashing.cpp
    core/streaming.cpp
    core/thread_pool.cpp
    core/parallel_encrypt.cpp
)

target_include_directories(vcrypt_core PUBLIC core)

find_package(Threads REQUIRED)

target_link_libraries(vcrypt_core
    PUBLIC
    Threads::Threads
)

add_executable(vcrypt_tests

    tests/core_tests.cpp
)

target_link_libraries(vcrypt_tests
    PRIVATE
    vcrypt_core
)

add_executable(vcrypt

    cli/main.cpp
)

target_link_libraries(vcrypt
    PRIVATE
    vcrypt_core
)

add_executable(thread_pool_test
    tests/thread_pool_test.cpp
)

target_link_libraries(thread_pool_test
    PRIVATE
    vcrypt_core
)

add_executable(benchmark_parallel
    benchmarks/benchmark_parallel.cpp
)

target_link_libraries(benchmark_parallel
    PRIVATE
    vcrypt_core
)