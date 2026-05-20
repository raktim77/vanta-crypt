#include "transforms.h"

#include <algorithm>

namespace vcrypt {

namespace {

constexpr std::array<u8, 256> SBOX = [] {
    std::array<u8, 256> table{};

    for (u32 i = 0; i < 256; ++i) {
        table[i] = static_cast<u8>((i * 73 + 41) % 256);
    }

    return table;
}();

constexpr std::array<u8, 256> INV_SBOX = [] {
    std::array<u8, 256> table{};

    for (u32 i = 0; i < 256; ++i) {
        table[SBOX[i]] = static_cast<u8>(i);
    }

    return table;
}();

inline u8 rotl8(u8 value, unsigned shift)
{
    return static_cast<u8>((value << shift) | (value >> (8 - shift)));
}

inline u8 rotr8(u8 value, unsigned shift)
{
    return static_cast<u8>((value >> shift) | (value << (8 - shift)));
}

} // namespace

void xor_mix(Block& block, const RoundKey& key)
{
    for (std::size_t i = 0; i < BLOCK_SIZE; ++i) {
        block[i] ^= key[i];
    }
}

void inverse_xor_mix(Block& block, const RoundKey& key)
{
    xor_mix(block, key);
}

void substitute(Block& block)
{
    for (auto& byte : block) {
        byte = SBOX[byte];
    }
}

void inverse_substitute(Block& block)
{
    for (auto& byte : block) {
        byte = INV_SBOX[byte];
    }
}

void rotate_bits(Block& block)
{
    for (std::size_t i = 0; i < BLOCK_SIZE; ++i) {
        block[i] = rotl8(block[i], (i % 7) + 1);
    }
}

void inverse_rotate_bits(Block& block)
{
    for (std::size_t i = 0; i < BLOCK_SIZE; ++i) {
        block[i] = rotr8(block[i], (i % 7) + 1);
    }
}

void permute(Block& block)
{
    Block temp = block;

    for (std::size_t i = 0; i < BLOCK_SIZE; ++i) {
        block[i] = temp[(i * 5) % BLOCK_SIZE];
    }
}

void inverse_permute(Block& block)
{
    Block temp = block;

    for (std::size_t i = 0; i < BLOCK_SIZE; ++i) {
        block[(i * 5) % BLOCK_SIZE] = temp[i];
    }
}

void diffuse(Block& block)
{
    for (std::size_t i = 1; i < BLOCK_SIZE; ++i) {
        block[i] ^= block[i - 1];
    }
}

void inverse_diffuse(Block& block)
{
    for (std::size_t i = BLOCK_SIZE - 1; i > 0; --i) {
        block[i] ^= block[i - 1];
    }
}

} // namespace vcrypt