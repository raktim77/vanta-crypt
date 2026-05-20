#include "../core/crypto_engine.h"

#include <chrono>
#include <iostream>
#include <random>
#include <vector>

int main() {

    //
    // 100 MB test payload
    //

    const std::size_t SIZE =
        100 * 1024 * 1024;

    std::vector<uint8_t> data(SIZE);

    //
    // Fill with random bytes
    //

    std::mt19937 rng(12345);

    std::uniform_int_distribution<int>
        dist(0, 255);

    for (std::size_t i = 0; i < SIZE; ++i) {

        data[i] =
            static_cast<uint8_t>(
                dist(rng)
            );
    }

    std::cout
        << "Benchmark payload: "
        << SIZE / (1024 * 1024)
        << " MB"
        << std::endl;

    auto start =
        std::chrono::high_resolution_clock::now();

    auto encrypted =
        vcrypt::encrypt_to_file_format(
            data,
            "password123"
        );

    auto end =
        std::chrono::high_resolution_clock::now();

    double seconds =
        std::chrono::duration<double>(
            end - start
        ).count();

    double throughput =
        (SIZE / (1024.0 * 1024.0)) / seconds;

    std::cout
        << "Encryption time: "
        << seconds
        << " seconds"
        << std::endl;

    std::cout
        << "Throughput: "
        << throughput
        << " MB/s"
        << std::endl;

    return 0;
}