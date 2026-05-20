#pragma once

#include "types.h"

#include <string>
#include <vector>

namespace vcrypt {

std::vector<u8> read_file(
    const std::string& path
);

void write_file(
    const std::string& path,
    const std::vector<u8>& data
);

bool file_exists(
    const std::string& path
);

} // namespace vcrypt