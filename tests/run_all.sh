#!/bin/bash

set -e

echo "=============================="
echo "Building native tests"
echo "=============================="

g++ \
native/test_roundtrip.cpp \
../core/crypto_engine.cpp \
../core/key_schedule.cpp \
../core/transforms.cpp \
../core/serializer.cpp \
../core/hashing.cpp \
-std=c++17 \
-o native/test_roundtrip

g++ \
native/test_wrong_password.cpp \
../core/crypto_engine.cpp \
../core/key_schedule.cpp \
../core/transforms.cpp \
../core/serializer.cpp \
../core/hashing.cpp \
-std=c++17 \
-o native/test_wrong_password

g++ \
native/test_corruption_detection.cpp \
../core/crypto_engine.cpp \
../core/key_schedule.cpp \
../core/transforms.cpp \
../core/serializer.cpp \
../core/hashing.cpp \
-std=c++17 \
-o native/test_corruption_detection

g++ \
native/test_randomized_roundtrip.cpp \
../core/crypto_engine.cpp \
../core/key_schedule.cpp \
../core/transforms.cpp \
../core/serializer.cpp \
../core/hashing.cpp \
-std=c++17 \
-o native/test_randomized_roundtrip

g++ \
native/test_edge_cases.cpp \
../core/crypto_engine.cpp \
../core/key_schedule.cpp \
../core/transforms.cpp \
../core/serializer.cpp \
../core/hashing.cpp \
-std=c++17 \
-o native/test_edge_cases

echo "=============================="
echo "Running native tests"
echo "=============================="

./native/test_roundtrip
./native/test_wrong_password
./native/test_corruption_detection
./native/test_randomized_roundtrip
./native/test_edge_cases

echo "=============================="
echo "Running Wasm tests"
echo "=============================="

node wasm/test_wasm_sdk.mjs

echo "=============================="
echo "Running SDK tests"
echo "=============================="

npx tsx sdk/test_typescript_sdk.ts

echo "=============================="
echo "ALL TESTS PASSED"
echo "=============================="