#include "../../core/crypto_engine.h"

#include <cassert>
#include <iostream>
#include <vector>

void run_test(
    const std::vector<uint8_t>& input,
    const std::string& label
) {

    auto encrypted =
        vcrypt::encrypt_to_file_format(
            input,
            "password123"
        );

    auto decrypted =
        vcrypt::decrypt_from_file_format(
            encrypted,
            "password123"
        );

    assert(input == decrypted);

    std::cout
        << label
        << " passed"
        << std::endl;
}

int main() {

    //
    // Empty input
    //

    run_test({}, "Empty input");

    //
    // Single byte
    //

    run_test({42}, "Single byte");

    //
    // Exact block size
    //

    run_test(
        std::vector<uint8_t>(16, 0xAA),
        "Exact block size"
    );

    //
    // One byte under block size
    //

    run_test(
        std::vector<uint8_t>(15, 0xBB),
        "15-byte input"
    );

    //
    // One byte over block size
    //

    run_test(
        std::vector<uint8_t>(17, 0xCC),
        "17-byte input"
    );

    //
    // Large aligned buffer
    //

    run_test(
        std::vector<uint8_t>(4096, 0xDD),
        "Large aligned buffer"
    );

    //
    // Large unaligned buffer
    //

    run_test(
        std::vector<uint8_t>(4097, 0xEE),
        "Large unaligned buffer"
    );

    std::cout
        << "All edge case tests passed"
        << std::endl;

    return 0;
}