#include "streaming.h"

#include "crypto_engine.h"
#include "hashing.h"
#include "serializer.h"
#include "file_io.h"
#include <fstream>
#include <stdexcept>

namespace vcrypt {

namespace {

constexpr std::size_t CHUNK_SIZE =
    64 * 1024;

std::array<u8, 16> generate_salt()
{
    return {
        0x13, 0x37, 0x42, 0x99,
        0xAB, 0xCD, 0xEF, 0x10,
        0x55, 0x66, 0x77, 0x88,
        0x21, 0x43, 0x65, 0x87
    };
}

void write_header(
    std::ofstream& out,
    const std::array<u8, 16>& salt,
    const Hash256& hash,
    u64 original_size
)
{
    auto header =
        serialize({}, salt, hash, original_size);

    constexpr std::size_t HEADER_SIZE =
        4 + 4 + 16 + 32 + 8;

    out.write(
        reinterpret_cast<const char*>(header.data()),
        HEADER_SIZE
    );
}

} // namespace

void encrypt_file_streaming(
    const std::string& input_path,
    const std::string& output_path,
    const std::string& password
)
{
    std::ifstream in(
        input_path,
        std::ios::binary
    );

    if (!in) {
        throw std::runtime_error(
            "Failed to open input file"
        );
    }

    std::ofstream out(
        output_path,
        std::ios::binary
    );

    if (!out) {
        throw std::runtime_error(
            "Failed to open output file"
        );
    }

    in.seekg(0, std::ios::end);

    u64 original_size =
        static_cast<u64>(in.tellg());

    in.seekg(0, std::ios::beg);

    std::vector<u8> full_data(
        original_size
    );

    in.read(
        reinterpret_cast<char*>(full_data.data()),
        original_size
    );

    Hash256 integrity_hash =
        compute_hash(full_data);

    in.clear();
    in.seekg(0, std::ios::beg);

    auto salt = generate_salt();

    write_header(
        out,
        salt,
        integrity_hash,
        original_size
    );

    MasterKey master_key =
        generate_master_key(
            password,
            salt
        );

    auto round_keys =
        generate_round_keys(master_key);

    std::vector<u8> buffer(
        CHUNK_SIZE
    );

    while (in) {

        in.read(
            reinterpret_cast<char*>(buffer.data()),
            CHUNK_SIZE
        );

        std::size_t bytes_read =
            static_cast<std::size_t>(
                in.gcount()
            );

        if (bytes_read == 0) {
            break;
        }

        std::vector<u8> chunk(
            buffer.begin(),
            buffer.begin() + bytes_read
        );

        auto encrypted =
            encrypt(chunk, password);

        out.write(
            reinterpret_cast<const char*>(
                encrypted.data()
            ),
            encrypted.size()
        );
    }
}

void decrypt_file_streaming(
    const std::string& input_path,
    const std::string& output_path,
    const std::string& password
)
{
    auto file_data =
        read_file(input_path);

    auto decrypted =
        decrypt_from_file_format(
            file_data,
            password
        );

    write_file(
        output_path,
        decrypted
    );
}

} // namespace vcrypt