#include "../core/parallel_encrypt.h"

#include <iostream>
#include <chrono>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

void run_benchmark(
    const std::string &input_file,
    size_t thread_count)
{
    const std::string output_file =
        "benchmark_output_" +
        std::to_string(thread_count) +
        ".vc";

    const std::string password =
        "benchmark-password";

    uintmax_t file_size =
        fs::file_size(input_file);

    auto start =
        std::chrono::high_resolution_clock::now();

    bool success =
        encrypt_file_parallel(
            input_file,
            output_file,
            password,
            1024 * 1024,
            thread_count);

    auto end =
        std::chrono::high_resolution_clock::now();

    if (!success)
    {

        std::cout
            << "Benchmark failed for "
            << thread_count
            << " threads\n";

        return;
    }

    double seconds =
        std::chrono::duration<double>(
            end - start)
            .count();

    double mb =
        static_cast<double>(file_size) / (1024.0 * 1024.0);

    double throughput =
        mb / seconds;

    std::cout
        << "Threads: "
        << thread_count
        << '\n';

    std::cout
        << "Time: "
        << seconds
        << " sec\n";

    std::cout
        << "Throughput: "
        << throughput
        << " MB/s\n";

    std::cout
        << "--------------------------\n";
}

int main()
{

    const std::string input_file =
        "large_test_file.bin";

    std::vector<size_t> thread_counts = {
        1,
        2,
        4,
        8};

    std::vector<size_t> chunk_sizes = {
        256 * 1024,
        512 * 1024,
        1024 * 1024,
        2 * 1024 * 1024,
        4 * 1024 * 1024};

   for (size_t chunk_size : chunk_sizes)
{
    std::cout
        << "\n=========================\n";

    std::cout
        << "Chunk Size: "
        << (chunk_size / 1024)
        << " KB\n";

    std::cout
        << "=========================\n";

    for (size_t threads : thread_counts)
    {
        const std::string output_file =
            "benchmark_output.vc";

        const std::string password =
            "benchmark-password";

        uintmax_t file_size =
            fs::file_size(input_file);

        auto start =
            std::chrono::high_resolution_clock::now();

        bool success =
            encrypt_file_parallel(
                input_file,
                output_file,
                password,
                chunk_size,
                threads
            );

        auto end =
            std::chrono::high_resolution_clock::now();

        if (!success)
        {
            std::cout
                << "Benchmark failed\n";

            continue;
        }

        double seconds =
            std::chrono::duration<double>(
                end - start
            ).count();

        double mb =
            static_cast<double>(file_size)
            / (1024.0 * 1024.0);

        double throughput =
            mb / seconds;

        std::cout
            << "Threads: "
            << threads
            << '\n';

        std::cout
            << "Time: "
            << seconds
            << " sec\n";

        std::cout
            << "Throughput: "
            << throughput
            << " MB/s\n";

        std::cout
            << "--------------------------\n";
    }
}

    return 0;
}