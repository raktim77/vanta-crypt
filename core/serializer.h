#pragma once

#include "types.h"
#include "hashing.h"
#include <array>
#include <vector>

namespace vcrypt {

struct SerializedPackage {

    u32 version;

    std::array<u8, 16> salt;

    u64 original_size;

    std::vector<u8> encrypted_data;

    Hash256 integrity_hash;

    std::string original_filename;
};

std::vector<u8> serialize(

    const std::vector<u8>& encrypted_data,

    const std::array<u8, 16>& salt,

    const Hash256& integrity_hash,

    u64 original_size,

    const std::string& original_filename
);

SerializedPackage deserialize(

    const std::vector<u8>& file_data
);

} // namespace vcrypt