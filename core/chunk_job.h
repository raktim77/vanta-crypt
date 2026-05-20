#pragma once

#include <vector>
#include <cstddef>
#include <cstdint>

struct ChunkJob {
    size_t index;

    std::vector<uint8_t> input;

    std::vector<uint8_t> output;
};