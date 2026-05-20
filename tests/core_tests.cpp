#include "../core/crypto_engine.h"

#include <iostream>
#include <string>

int main()
{
    std::string input =
        "VantaCrypt serialized runtime test.";

    std::vector<vcrypt::u8> plaintext(
        input.begin(),
        input.end()
    );

    std::string password =
        "super_secure_password";

    auto encrypted_file =
        vcrypt::encrypt_to_file_format(
            plaintext,
            password
        );

    auto decrypted =
        vcrypt::decrypt_from_file_format(
            encrypted_file,
            password
        );

    std::string recovered(
        decrypted.begin(),
        decrypted.end()
    );

    std::cout << "Original : "
              << input
              << '\n';

    std::cout << "Recovered: "
              << recovered
              << '\n';

    std::cout << "Serialized Size: "
              << encrypted_file.size()
              << " bytes\n";

    if (input == recovered) {

        std::cout
            << "[PASS] .vc serialization verified.\n";

        return 0;
    }

    std::cout
        << "[FAIL] Serialization mismatch.\n";

    return 1;
}