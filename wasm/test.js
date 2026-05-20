import init from "./dist/vantacrypt.js";

const wasm = await init();

const original = new Uint8Array([
    0,
    255,
    128,
    64,
    1,
    2,
    3,
    4,
    5
]);

console.log("Original:", original);

//
// JS Uint8Array -> Embind VectorUint8
//

const inputVec = new wasm.VectorUint8();

for (const byte of original) {
    inputVec.push_back(byte);
}

//
// Encrypt
//

const encryptedVec = wasm.encryptFile(
    inputVec,
    "password123"
);

//
// Embind VectorUint8 -> Uint8Array
//

const encrypted = new Uint8Array(
    encryptedVec.size()
);

for (let i = 0; i < encrypted.length; i++) {
    encrypted[i] = encryptedVec.get(i);
}

console.log("Encrypted:", encrypted);

//
// Prepare encrypted input
//

const encryptedInputVec = new wasm.VectorUint8();

for (const byte of encrypted) {
    encryptedInputVec.push_back(byte);
}

//
// Decrypt
//

const decryptedVec = wasm.decryptFile(
    encryptedInputVec,
    "password123"
);

//
// Convert decrypted output
//

const decrypted = new Uint8Array(
    decryptedVec.size()
);

for (let i = 0; i < decrypted.length; i++) {
    decrypted[i] = decryptedVec.get(i);
}

console.log("Decrypted:", decrypted);

//
// Validate binary equality
//

let equal = true;

if (original.length !== decrypted.length) {
    equal = false;
}

for (let i = 0; i < original.length; i++) {

    if (original[i] !== decrypted[i]) {
        equal = false;
        break;
    }
}

console.log("Binary roundtrip success:", equal);

//
// Cleanup embind allocations
//

inputVec.delete();
encryptedVec.delete();
encryptedInputVec.delete();
decryptedVec.delete();