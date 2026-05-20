#include <emscripten/bind.h>

#include "../core/crypto_engine.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(vantacrypt) {

    register_vector<uint8_t>("VectorUint8");

    function(
        "encrypt",
        &vcrypt::encrypt
    );

    function(
        "decrypt",
        &vcrypt::decrypt
    );

    function(
        "encryptFile",
        &vcrypt::encrypt_to_file_format
    );

    function(
        "decryptFile",
        &vcrypt::decrypt_from_file_format
    );
}