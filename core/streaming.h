#pragma once

#include <string>

namespace vcrypt {

void encrypt_file_streaming(
    const std::string& input_path,
    const std::string& output_path,
    const std::string& password
);

void decrypt_file_streaming(
    const std::string& input_path,
    const std::string& output_path,
    const std::string& password
);

} // namespace vcrypt