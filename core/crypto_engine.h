#pragma once

#include "key_schedule.h"
#include "transforms.h"
#include "serializer.h"

#include <string>
#include <vector>
#include <cstdint>

namespace vcrypt
{

    struct DecryptionResult
    {
        std::vector<uint8_t> data;

        std::string filename;
    };

    Block encrypt_block(
        Block block,
        const std::vector<RoundKey> &round_keys);

    Block decrypt_block(
        Block block,
        const std::vector<RoundKey> &round_keys);

    std::vector<uint8_t> encrypt(
        const std::vector<uint8_t> &data,
        const std::string &password);

    std::vector<uint8_t> decrypt(
        const std::vector<uint8_t> &data,
        const std::string &password);

    std::vector<uint8_t> encrypt_to_file_format(
        const std::vector<uint8_t> &data,
        const std::string &password,
        const std::string &filename);

    DecryptionResult decrypt_from_file_format(
        const std::vector<uint8_t> &file_data,
        const std::string &password);

}