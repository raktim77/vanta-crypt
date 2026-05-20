#!/bin/bash

mkdir -p dist

emcc \
    bindings.cpp \
    ../core/crypto_engine.cpp \
    ../core/key_schedule.cpp \
    ../core/transforms.cpp \
    ../core/serializer.cpp \
    ../core/hashing.cpp \
    -O3 \
    --bind \
    -s WASM=1 \
    -s MODULARIZE=1 \
    -s EXPORT_ES6=1 \
    -s ENVIRONMENT='web,node' \
    -s ALLOW_MEMORY_GROWTH=1 \
    -s EXPORT_ALL=1 \
    -s EXPORTED_FUNCTIONS='["_malloc","_free"]' \
    -o dist/vantacrypt.js