#include "../../core/crypto_engine.h"

#include <cassert>
#include <iostream>
#include <vector>

int main()
{

    std::vector<uint8_t> original = {
        0,
        255,
        128,
        64,
        1,
        2,
        3,
        4,
        5};

    std::string password =
        "password123";

    auto encrypted =
        vcrypt::encrypt_to_file_format(
            original,
            password,
            "test.txt");

    auto decrypted =
        vcrypt::decrypt_from_file_format(
            encrypted,
            password);

    assert(
        original ==
        decrypted.data);
    assert(
        decrypted.filename ==
        "test.txt");

    std::cout
        << "Native roundtrip test passed"
        << std::endl;

    return 0;
}