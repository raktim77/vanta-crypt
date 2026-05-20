#include "file_io.h"

#include <filesystem>
#include <fstream>
#include <stdexcept>

namespace vcrypt {

std::vector<u8> read_file(
    const std::string& path
)
{
    std::ifstream file(
        path,
        std::ios::binary
    );

    if (!file) {
        throw std::runtime_error(
            "Failed to open file for reading"
        );
    }

    file.seekg(0, std::ios::end);

    std::size_t size =
        static_cast<std::size_t>(
            file.tellg()
        );

    file.seekg(0, std::ios::beg);

    std::vector<u8> buffer(size);

    file.read(
        reinterpret_cast<char*>(buffer.data()),
        size
    );

    return buffer;
}

void write_file(
    const std::string& path,
    const std::vector<u8>& data
)
{
    std::ofstream file(
        path,
        std::ios::binary
    );

    if (!file) {
        throw std::runtime_error(
            "Failed to open file for writing"
        );
    }

    file.write(
        reinterpret_cast<const char*>(data.data()),
        data.size()
    );
}

bool file_exists(
    const std::string& path
)
{
    return std::filesystem::exists(path);
}

} // namespace vcrypt