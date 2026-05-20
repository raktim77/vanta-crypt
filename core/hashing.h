#pragma once

#include "types.h"

#include <array>
#include <vector>

namespace vcrypt {

using Hash256 = std::array<u8, 32>;

Hash256 compute_hash(
    const std::vector<u8>& data
);

bool hashes_equal(
    const Hash256& a,
    const Hash256& b
);

} // namespace vcrypt