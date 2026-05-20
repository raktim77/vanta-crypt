#pragma once

#include "types.h"

namespace vcrypt {

void xor_mix(Block& block, const RoundKey& key);
void inverse_xor_mix(Block& block, const RoundKey& key);

void substitute(Block& block);
void inverse_substitute(Block& block);

void rotate_bits(Block& block);
void inverse_rotate_bits(Block& block);

void permute(Block& block);
void inverse_permute(Block& block);

void diffuse(Block& block);
void inverse_diffuse(Block& block);

} // namespace vcrypt