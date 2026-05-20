#include "parallel_encrypt.h"

#include "thread_pool.h"
#include "chunk_job.h"
#include "crypto_engine.h"

#include <fstream>
#include <future>
#include <vector>
#include <deque>

bool encrypt_file_parallel(
    const std::string &input_path,
    const std::string &output_path,
    const std::string &password,
    size_t chunk_size,
    size_t thread_count)
{
    if (thread_count == 0)
    {
        thread_count = 4;
    }
    ThreadPool pool(thread_count);

    std::ifstream input(
        input_path,
        std::ios::binary);

    if (!input.is_open())
    {
        return false;
    }

    std::ofstream output(
        output_path,
        std::ios::binary);

    if (!output.is_open())
    {
        return false;
    }

    std::deque<std::future<ChunkJob>> futures;

    const size_t max_inflight =
        thread_count * 2;

    size_t chunk_index = 0;

    while (true)
    {
        ChunkJob job;

        job.index = chunk_index++;

        job.input.resize(chunk_size);

        input.read(
            reinterpret_cast<char *>(
                job.input.data()),
            chunk_size);

        std::streamsize bytes_read =
            input.gcount();

        if (bytes_read <= 0)
        {
            break;
        }

        job.input.resize(
            static_cast<size_t>(
                bytes_read));

        futures.push_back(
            pool.enqueue(
                [job, password]() mutable -> ChunkJob
                {
                    job.output.clear();

                    vcrypt::encrypt_buffer(
                        job.input,
                        job.output,
                        password);

                    return job;
                }));

        if (futures.size() >= max_inflight)
        {
            ChunkJob result =
                futures.front().get();

            futures.pop_front();

            output.write(
                reinterpret_cast<char *>(
                    result.output.data()),
                result.output.size());
        }
    }

    while (!futures.empty())
    {
        ChunkJob result =
            futures.front().get();

        futures.pop_front();

        output.write(
            reinterpret_cast<char *>(
                result.output.data()),
            result.output.size());
    }

    return true;
}