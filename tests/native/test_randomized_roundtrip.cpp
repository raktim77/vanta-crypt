#include "../../core/crypto_engine.h"

#include <cassert>
#include <iostream>
#include <vector>
#include <random>

int main()
{

    std::mt19937 rng(12345);

    std::uniform_int_distribution<int>
        size_dist(1, 4096);

    std::uniform_int_distribution<int>
        byte_dist(0, 255);

    for (int test = 0; test < 100; ++test)
    {

        int size = size_dist(rng);

        std::vector<uint8_t> original(size);

        for (int i = 0; i < size; ++i)
        {
            original[i] =
                static_cast<uint8_t>(
                    byte_dist(rng));
        }

        auto encrypted =
            vcrypt::encrypt_to_file_format(
                original,
                "password123",
                "random.bin");

        auto decrypted =
            vcrypt::decrypt_from_file_format(
                encrypted,
                "password123");

        assert(
            original ==
            decrypted.data);

        assert(
            decrypted.filename ==
            "random.bin");
    }

    std::cout
        << "Randomized roundtrip tests passed"
        << std::endl;

    return 0;
}