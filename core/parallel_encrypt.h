#pragma once

#include <string>
#include <thread>

bool encrypt_file_parallel(
    const std::string& input_path,
    const std::string& output_path,
    const std::string& password,
    size_t chunk_size = 1024 * 1024,
    size_t thread_count =
    std::thread::hardware_concurrency()
);