#pragma once

#include "types.h"

#include <string>
#include <vector>

namespace vcrypt {

MasterKey generate_master_key(
    const std::string& password,
    const std::array<u8, 16>& salt
);

std::vector<RoundKey> generate_round_keys(
    const MasterKey& master_key
);

} // namespace vcrypt