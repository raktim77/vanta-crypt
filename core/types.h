#pragma once

#include <array>
#include <cstdint>
#include <vector>

namespace vcrypt {

using u8  = std::uint8_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

constexpr std::size_t BLOCK_SIZE = 16;
constexpr std::size_t KEY_SIZE   = 32;
constexpr std::size_t NUM_ROUNDS = 8;

using Block     = std::array<u8, BLOCK_SIZE>;
using MasterKey = std::array<u8, KEY_SIZE>;
using RoundKey  = std::array<u8, BLOCK_SIZE>;

} // namespace vcrypt