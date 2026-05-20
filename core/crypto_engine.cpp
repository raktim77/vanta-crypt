#include "crypto_engine.h"
#include "hashing.h"
#include <stdexcept>
namespace vcrypt
{

    namespace
    {

        std::array<u8, 16> generate_salt()
        {
            return {
                0x13, 0x37, 0x42, 0x99,
                0xAB, 0xCD, 0xEF, 0x10,
                0x55, 0x66, 0x77, 0x88,
                0x21, 0x43, 0x65, 0x87};
        }

        Block make_block(
            const std::vector<u8> &data,
            std::size_t offset)
        {
            Block block{};

            for (std::size_t i = 0; i < BLOCK_SIZE; ++i)
            {

                if (offset + i < data.size())
                {
                    block[i] = data[offset + i];
                }
                else
                {
                    block[i] = 0;
                }
            }

            return block;
        }

        void append_block(
            std::vector<u8> &output,
            const Block &block)
        {
            output.insert(
                output.end(),
                block.begin(),
                block.end());
        }

    } // namespace

    Block encrypt_block(
        Block block,
        const std::vector<RoundKey> &round_keys)
    {
        for (std::size_t round = 0;
             round < NUM_ROUNDS;
             ++round)
        {

            xor_mix(block, round_keys[round]);

            rotate_bits(block);

            substitute(block);

            permute(block);

            diffuse(block);
        }

        return block;
    }

    Block decrypt_block(
        Block block,
        const std::vector<RoundKey> &round_keys)
    {
        for (std::size_t round = NUM_ROUNDS;
             round-- > 0;)
        {

            inverse_diffuse(block);

            inverse_permute(block);

            inverse_substitute(block);

            inverse_rotate_bits(block);

            inverse_xor_mix(block, round_keys[round]);
        }

        return block;
    }

    std::vector<u8> encrypt(
        const std::vector<u8> &data,
        const std::string &password)
    {
        auto salt = generate_salt();

        MasterKey master_key =
            generate_master_key(
                password,
                salt);

        auto round_keys =
            generate_round_keys(master_key);

        std::vector<u8> encrypted;

        encrypted.reserve(data.size());

        for (std::size_t offset = 0;
             offset < data.size();
             offset += BLOCK_SIZE)
        {

            Block block =
                make_block(data, offset);

            Block encrypted_block =
                encrypt_block(block, round_keys);

            append_block(
                encrypted,
                encrypted_block);
        }

        return encrypted;
    }
    std::vector<u8> decrypt(
        const std::vector<u8> &data,
        const std::string &password)
    {
        auto salt = generate_salt();

        MasterKey master_key =
            generate_master_key(
                password,
                salt);

        auto round_keys =
            generate_round_keys(master_key);

        std::vector<u8> decrypted;

        decrypted.reserve(data.size());

        for (std::size_t offset = 0;
             offset < data.size();
             offset += BLOCK_SIZE)
        {

            Block block =
                make_block(data, offset);

            Block decrypted_block =
                decrypt_block(block, round_keys);

            append_block(
                decrypted,
                decrypted_block);
        }

        return decrypted;
    }

    std::vector<u8> encrypt_to_file_format(
        const std::vector<u8> &data,
        const std::string &password)
    {
        auto salt = generate_salt();

        MasterKey master_key =
            generate_master_key(
                password,
                salt);
        Hash256 integrity_hash =
            compute_hash(data);
        auto round_keys =
            generate_round_keys(master_key);

        std::vector<u8> encrypted;

        encrypted.reserve(data.size());

        for (std::size_t offset = 0;
             offset < data.size();
             offset += BLOCK_SIZE)
        {

            Block block =
                make_block(data, offset);

            Block encrypted_block =
                encrypt_block(block, round_keys);

            append_block(
                encrypted,
                encrypted_block);
        }

        return serialize(
            encrypted,
            salt,
            integrity_hash,
            static_cast<u64>(data.size()));
    }

    std::vector<u8> decrypt_from_file_format(
        const std::vector<u8> &file_data,
        const std::string &password)
    {
        SerializedPackage package =
            deserialize(file_data);

        MasterKey master_key =
            generate_master_key(
                password,
                package.salt);

        auto round_keys =
            generate_round_keys(master_key);

        std::vector<u8> decrypted;

        decrypted.reserve(
            package.encrypted_data.size());

        for (std::size_t offset = 0;
             offset < package.encrypted_data.size();
             offset += BLOCK_SIZE)
        {

            Block block =
                make_block(
                    package.encrypted_data,
                    offset);

            Block decrypted_block =
                decrypt_block(
                    block,
                    round_keys);

            append_block(
                decrypted,
                decrypted_block);
        }

        decrypted.resize(
            package.original_size);
        Hash256 computed_hash =
            compute_hash(decrypted);

        if (!hashes_equal(
                computed_hash,
                package.integrity_hash))
        {
            throw std::runtime_error(
                "Integrity verification failed");
        }
        return decrypted;
    }

} // namespace vcrypt