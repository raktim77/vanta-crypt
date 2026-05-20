import init from "../../wasm/dist/vantacrypt.js";

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

function uint8ArrayToVector(data) {

    const vec = new wasm.VectorUint8();

    for (const byte of data) {
        vec.push_back(byte);
    }

    return vec;
}

function vectorToUint8Array(vec) {

    const result = new Uint8Array(
        vec.size()
    );

    for (let i = 0; i < vec.size(); i++) {
        result[i] = vec.get(i);
    }

    return result;
}

const inputVec =
    uint8ArrayToVector(original);

const encryptedVec =
    wasm.encryptFile(
        inputVec,
        "password123"
    );

const encrypted =
    vectorToUint8Array(encryptedVec);

const encryptedInputVec =
    uint8ArrayToVector(encrypted);

const decryptedVec =
    wasm.decryptFile(
        encryptedInputVec,
        "password123"
    );

const decrypted =
    vectorToUint8Array(decryptedVec);

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

if (!equal) {

    throw new Error(
        "Wasm roundtrip failed"
    );
}

console.log(
    "Wasm SDK test passed"
);

inputVec.delete();
encryptedVec.delete();
encryptedInputVec.delete();
decryptedVec.delete();