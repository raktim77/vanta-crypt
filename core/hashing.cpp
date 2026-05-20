#include "hashing.h"

namespace vcrypt {

namespace {

inline u8 rotl8(u8 value, unsigned shift)
{
    return static_cast<u8>(
        (value << shift) |
        (value >> (8 - shift))
    );
}

} // namespace

Hash256 compute_hash(
    const std::vector<u8>& data
)
{
    Hash256 hash{};

    for (std::size_t i = 0; i < 32; ++i) {

        hash[i] =
            static_cast<u8>(
                i * 11 + 17
            );
    }

    for (std::size_t i = 0; i < data.size(); ++i) {

        u8 value = data[i];

        for (std::size_t j = 0; j < 32; ++j) {

            hash[j] ^=
                rotl8(
                    static_cast<u8>(
                        value + j + i
                    ),
                    (j % 7) + 1
                );

            hash[j] =
                static_cast<u8>(
                    (hash[j] * 31 + 7) % 256
                );
        }
    }

    return hash;
}

bool hashes_equal(
    const Hash256& a,
    const Hash256& b
)
{
    for (std::size_t i = 0; i < 32; ++i) {

        if (a[i] != b[i]) {
            return false;
        }
    }

    return true;
}

} // namespace vcrypt