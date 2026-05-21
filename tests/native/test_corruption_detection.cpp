#include "../../core/crypto_engine.h"

#include <cassert>
#include <iostream>
#include <vector>
#include <stdexcept>

int main()
{

    std::vector<uint8_t> original = {
        10,
        20,
        30,
        40,
        50};

    auto encrypted =
        vcrypt::encrypt_to_file_format(
            original,
            "password123",
            "test.txt");

    //
    // Corrupt one byte
    //

    encrypted[25] ^= 0xFF;

    bool exception_thrown = false;

    try
    {

        auto decrypted =
            vcrypt::decrypt_from_file_format(
                encrypted,
                "password123");
    }
    catch (const std::runtime_error &)
    {

        exception_thrown = true;
    }

    assert(exception_thrown);

    std::cout
        << "Corruption detection test passed"
        << std::endl;

    return 0;
}