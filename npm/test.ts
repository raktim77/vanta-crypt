import {
    encryptFile,
    decryptFile
} from "./wrapper.js";

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

const encrypted = await encryptFile(
    original,
    "password123"
);

console.log("Encrypted:", encrypted);

const decrypted = await decryptFile(
    encrypted,
    "password123"
);

console.log("Decrypted:", decrypted);

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

console.log("SDK roundtrip success:", equal);