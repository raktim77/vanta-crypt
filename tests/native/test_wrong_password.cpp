#include "../../core/crypto_engine.h"

#include <cassert>
#include <iostream>
#include <vector>
#include <stdexcept>

int main()
{

    std::vector<uint8_t> original = {
        1,
        2,
        3,
        4,
        5};

    auto encrypted =
        vcrypt::encrypt_to_file_format(
            original,
            "correct_password",
            "test.txt");

    bool exception_thrown = false;

    try
    {

        auto decrypted =
            vcrypt::decrypt_from_file_format(
                encrypted,
                "wrong_password");
    }
    catch (const std::runtime_error &)
    {

        exception_thrown = true;
    }

    assert(exception_thrown);

    std::cout
        << "Wrong password test passed"
        << std::endl;

    return 0;
}