# VantaCrypt

High-performance binary-safe file encryption runtime built with modern C++, WebAssembly, and TypeScript.

![Web Demo](https://raw.githubusercontent.com/raktim77/vanta-crypt/refs/heads/main/assets/web-demo.png)

VantaCrypt is a portable encryption SDK designed for:

- browser-side file encryption
- Node.js applications
- WebAssembly runtimes
- binary-safe data processing
- large-file streaming architectures

The project demonstrates:

- low-level systems programming
- custom binary serialization
- chunk-based encryption pipelines
- WebAssembly interoperability
- TypeScript SDK engineering
- cross-language runtime integration

---

# Features

- Binary-safe encryption pipeline
- WebAssembly-powered runtime
- TypeScript SDK
- Browser + Node.js support
- Custom encrypted file container format
- Integrity verification
- Automated native/Wasm/SDK tests
- Continuous Integration pipeline
- Cross-platform architecture

---

# Architecture

```text
TypeScript SDK
        ↓
Uint8Array ABI Layer
        ↓
WebAssembly Runtime
        ↓
C++ Encryption Engine
        ↓
Serialization + Integrity Layer
```

---

# Installation

```bash
npm install vanta-crypt
```

---

# Browser Usage

```ts
import {
    encryptFile,
    decryptFile
} from "vanta-crypt";

const fileBuffer =
    new Uint8Array(await file.arrayBuffer());

const encrypted =
    await encryptFile(
        fileBuffer,
        "password123"
    );

const decrypted =
    await decryptFile(
        encrypted,
        "password123"
    );
```

---

# Node.js Usage

```ts
import fs from "node:fs/promises";

import {
    encryptFile,
    decryptFile
} from "vanta-crypt";

const input =
    new Uint8Array(
        await fs.readFile("example.pdf")
    );

const encrypted =
    await encryptFile(
        input,
        "password123"
    );

await fs.writeFile(
    "example.vc",
    encrypted
);

const encryptedInput =
    new Uint8Array(
        await fs.readFile("example.vc")
    );

const decrypted =
    await decryptFile(
        encryptedInput,
        "password123"
    );

await fs.writeFile(
    "restored.pdf",
    decrypted
);
```

---

# API Reference

## `encryptFile`

Encrypts arbitrary binary data into the VantaCrypt container format.

```ts
encryptFile(
    data: Uint8Array,
    password: string
): Promise<Uint8Array>
```

### Parameters

| Parameter | Type | Description |
|---|---|---|
| `data` | `Uint8Array` | Arbitrary binary input |
| `password` | `string` | Encryption password |

### Returns

Encrypted VantaCrypt binary container.

---

## `decryptFile`

Decrypts a VantaCrypt container and restores the original binary payload.

```ts
decryptFile(
    data: Uint8Array,
    password: string
): Promise<Uint8Array>
```

### Parameters

| Parameter | Type | Description |
|---|---|---|
| `data` | `Uint8Array` | Encrypted VantaCrypt container |
| `password` | `string` | Encryption password |

### Returns

Original binary payload restored from the encrypted container.

---

# Binary-Safe Architecture

VantaCrypt uses a fully binary-safe transport pipeline:

```text
Uint8Array
    ↓
Embind VectorUint8
    ↓
WebAssembly Memory
    ↓
std::vector<uint8_t>
    ↓
Native Encryption Engine
```

The runtime does NOT rely on:

- UTF-8 string transport
- TextEncoder/TextDecoder conversion
- JavaScript string serialization

This enables safe encryption of arbitrary binary payloads including:

- PNG
- JPG
- PDF
- ZIP
- MP4
- executable binaries
- archives
- arbitrary byte streams

---

# Encryption Pipeline

```text
Input Data
    ↓
Chunk Processing
    ↓
Key Expansion
    ↓
Transformation Rounds
    ├── XOR Mixing
    ├── Byte Substitution
    ├── Bit Rotation
    ├── Permutation
    └── Diffusion
    ↓
Integrity Hashing
    ↓
Binary Serialization
    ↓
Encrypted Output
```

---

# WebAssembly Runtime

The native encryption engine is compiled to WebAssembly using Emscripten.

Generated outputs:

- `.wasm`
- JavaScript loader/runtime
- TypeScript-compatible SDK bindings

Supported environments:

- Browser
- Node.js
- Electron
- Web Workers

---

# Benchmark Results

![Benchmark Results](https://raw.githubusercontent.com/raktim77/vanta-crypt/refs/heads/main/assets/benchmark.png)


Current native runtime throughput on a 100 MB payload:

| Operation | Throughput |
|---|---|
| Encryption | ~22.3 MB/s |
| Decryption | ~23.1 MB/s |

Benchmarks include:

- single-thread throughput analysis
- chunk-processing overhead
- parallel runtime benchmarking
- large-file workload validation

---

# Testing

![Test Suite](https://raw.githubusercontent.com/raktim77/vanta-crypt/refs/heads/main/assets/test-suite.png)


VantaCrypt includes automated validation for:

- native encryption runtime
- WebAssembly runtime
- TypeScript SDK
- randomized binary payloads
- corruption detection
- integrity verification
- wrong-password handling
- edge-case payload sizes
- real-world binary file formats

Validated formats include:

- PNG
- PDF
- ZIP
- MP4
- TXT

Run all tests:

```bash
cd tests

./run_all.sh
```

---

# Continuous Integration

GitHub Actions automatically validates:

- native runtime compilation
- WebAssembly builds
- TypeScript SDK builds
- native tests
- Wasm tests
- SDK tests

on every push and pull request.

---

# Build Instructions

## Build WebAssembly Runtime

```bash
cd wasm

./build.sh
```

---

## Build npm SDK

```bash
cd npm

npm install

npm run build
```

---

# Demo

The browser demo supports:

- file upload
- in-browser encryption
- in-browser decryption
- binary-safe downloads
- arbitrary file formats

Run locally:

```bash
python3 -m http.server 8080
```

Then open:

```text
http://localhost:8080/demo/
```

---

# Security Disclaimer

VantaCrypt is an educational and engineering-focused encryption runtime.

The project is NOT intended to:

- replace AES/OpenSSL
- provide certified cryptographic guarantees
- resist nation-state cryptanalysis
- serve as production-grade cryptographic infrastructure

The project IS intended to demonstrate:

- systems programming
- binary runtime engineering
- WebAssembly interoperability
- streaming architectures
- cross-language SDK design
- low-level performance engineering

---


# License

MIT