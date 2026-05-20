#include "../core/crypto_engine.h"
#include "../core/file_io.h"
#include "../core/streaming.h"
#include "../core/parallel_encrypt.h"
#include <iostream>
#include <string>
#include <chrono>

int main(int argc, char *argv[])
{
    if (argc < 4)
    {

        std::cout
            << "Usage:\n"
            << "  vcrypt encrypt <file> <password>\n"
            << "  vcrypt decrypt <file.vc> <password>\n";

        return 1;
    }

    std::string command = argv[1];
    std::string filepath = argv[2];
    std::string password = argv[3];

    try
    {

        if (!vcrypt::file_exists(filepath))
        {

            std::cout
                << "File does not exist.\n";

            return 1;
        }

        if (command == "encrypt")
        {

            std::string output_path =
                filepath + ".vc";
            auto start =
                std::chrono::high_resolution_clock::now();
            vcrypt::encrypt_file_streaming(
                filepath,
                output_path,
                password);

            auto end =
                std::chrono::high_resolution_clock::now();

            double seconds =
                std::chrono::duration<double>(
                    end - start)
                    .count();

            std::cout
                << "Encrypted file written to: "
                << output_path
                << '\n';
            std::cout
                << "Execution time: "
                << seconds
                << " sec\n";
        }
        else if (command == "encrypt-parallel")
        {

            std::string output_path =
                filepath + ".vc";
            auto start =
                std::chrono::high_resolution_clock::now();
            bool success = encrypt_file_parallel(
                filepath,
                output_path,
                password,
                1024 * 1024,
                4);
            auto end =
                std::chrono::high_resolution_clock::now();

            double seconds =
                std::chrono::duration<double>(
                    end - start)
                    .count();
            if (success)
            {
                std::cout
                    << "Parallel encryption complete\n";

                std::cout
                    << "Encrypted file written to: "
                    << output_path
                    << '\n';
                std::cout
                    << "Execution time: "
                    << seconds
                    << " sec\n";
            }
            else
            {
                std::cout
                    << "Parallel encryption failed\n";
            }
        }
        else if (command == "decrypt")
        {

            std::string output_path =
                filepath + ".dec";
            auto start =
                std::chrono::high_resolution_clock::now();
            vcrypt::decrypt_file_streaming(
                filepath,
                output_path,
                password);
            auto end =
                std::chrono::high_resolution_clock::now();

            double seconds =
                std::chrono::duration<double>(
                    end - start)
                    .count();

            std::cout
                << "Decrypted file written to: "
                << output_path
                << '\n';
            std::cout
                << "Execution time: "
                << seconds
                << " sec\n";
        }
        else
        {

            std::cout
                << "Unknown command.\n";

            return 1;
        }
    }
    catch (const std::exception &ex)
    {

        std::cout
            << "Error: "
            << ex.what()
            << '\n';

        return 1;
    }

    return 0;
}