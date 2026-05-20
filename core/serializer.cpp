#include "serializer.h"

#include <stdexcept>

namespace vcrypt
{

    namespace
    {

        constexpr std::size_t HEADER_SIZE =
            4 + 4 + 16 + 32 + 8;
        constexpr std::array<u8, 4> MAGIC = {
            'V', 'C', 'R', 'Y'};
        constexpr u32 VERSION = 1;

        void write_u32(
            std::vector<u8> &buffer,
            u32 value)
        {
            for (int i = 0; i < 4; ++i)
            {

                buffer.push_back(
                    static_cast<u8>(
                        (value >> (i * 8)) & 0xFF));
            }
        }

        void write_u64(
            std::vector<u8> &buffer,
            u64 value)
        {
            for (int i = 0; i < 8; ++i)
            {

                buffer.push_back(
                    static_cast<u8>(
                        (value >> (i * 8)) & 0xFF));
            }
        }

        u32 read_u32(
            const std::vector<u8> &buffer,
            std::size_t offset)
        {
            u32 value = 0;

            for (int i = 0; i < 4; ++i)
            {

                value |=
                    static_cast<u32>(
                        buffer[offset + i])
                    << (i * 8);
            }

            return value;
        }

        u64 read_u64(
            const std::vector<u8> &buffer,
            std::size_t offset)
        {
            u64 value = 0;

            for (int i = 0; i < 8; ++i)
            {

                value |=
                    static_cast<u64>(
                        buffer[offset + i])
                    << (i * 8);
            }

            return value;
        }

    } // namespace

std::vector<u8> serialize(

    const std::vector<u8>& encrypted_data,

    const std::array<u8, 16>& salt,

    const Hash256& integrity_hash,

    u64 original_size
)
{
    std::vector<u8> output;

    output.insert(
        output.end(),
        MAGIC.begin(),
        MAGIC.end()
    );

    write_u32(output, VERSION);

    output.insert(
        output.end(),
        salt.begin(),
        salt.end()
    );

    output.insert(
        output.end(),
        integrity_hash.begin(),
        integrity_hash.end()
    );

    write_u64(output, original_size);

    output.insert(
        output.end(),
        encrypted_data.begin(),
        encrypted_data.end()
    );

    return output;
}
    SerializedPackage deserialize(

        const std::vector<u8> &file_data)
    {
        constexpr std::size_t HEADER_SIZE =
            4 + 4 + 16 + 32 + 8;

        if (file_data.size() < HEADER_SIZE)
        {

            throw std::runtime_error(
                "Invalid file size");
        }

        for (std::size_t i = 0; i < MAGIC.size(); ++i)
        {

            if (file_data[i] != MAGIC[i])
            {

                throw std::runtime_error(
                    "Invalid VantaCrypt file");
            }
        }

        SerializedPackage package{};

        package.version =
            read_u32(file_data, 4);

        std::size_t salt_offset = 8;

        for (std::size_t i = 0; i < 16; ++i)
        {

            package.salt[i] =
                file_data[salt_offset + i];
        }

        std::size_t hash_offset = 24;

        for (std::size_t i = 0; i < 32; ++i)
        {

            package.integrity_hash[i] =
                file_data[hash_offset + i];
        }

        package.original_size =
            read_u64(file_data, 56);

        package.encrypted_data.assign(

            file_data.begin() + HEADER_SIZE,

            file_data.end());

        return package;
    }
} // namespace vcrypt