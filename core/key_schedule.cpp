#include "key_schedule.h"

namespace vcrypt {

namespace {

inline u8 rotl8(u8 value, unsigned shift)
{
    return static_cast<u8>((value << shift) | (value >> (8 - shift)));
}

} // namespace

MasterKey generate_master_key(
    const std::string& password,
    const std::array<u8, 16>& salt
)
{
    MasterKey key{};

    for (std::size_t i = 0; i < KEY_SIZE; ++i) {

        u8 password_byte =
            static_cast<u8>(
                password[i % password.size()]
            );

        u8 salt_byte =
            salt[i % salt.size()];

        u8 mixed =
            password_byte ^
            salt_byte ^
            static_cast<u8>(i * 31);

        mixed =
            rotl8(mixed, (i % 7) + 1);

        key[i] = mixed;
    }

    for (std::size_t round = 0; round < 64; ++round) {

        for (std::size_t i = 0; i < KEY_SIZE; ++i) {

            u8 left  = key[(i + KEY_SIZE - 1) % KEY_SIZE];
            u8 right = key[(i + 1) % KEY_SIZE];

            key[i] ^= rotl8(left ^ right, (i % 5) + 1);

            key[i] =
                static_cast<u8>(
                    (key[i] * 17 + 13) % 256
                );
        }
    }

    return key;
}

std::vector<RoundKey> generate_round_keys(
    const MasterKey& master_key
)
{
    std::vector<RoundKey> round_keys(NUM_ROUNDS);

    for (std::size_t round = 0; round < NUM_ROUNDS; ++round) {

        for (std::size_t i = 0; i < BLOCK_SIZE; ++i) {

            std::size_t index =
                (round * 7 + i) % KEY_SIZE;

            u8 value =
                master_key[index];

            value =
                rotl8(value ^ static_cast<u8>(round * 19),
                      (i % 7) + 1);

            round_keys[round][i] = value;
        }
    }

    return round_keys;
}

} // namespace vcrypt