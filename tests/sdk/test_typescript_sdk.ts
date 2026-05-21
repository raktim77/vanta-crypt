import {
    encryptFile,
    decryptFile
} from "../../npm/wrapper.js";

async function main() {

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

    const encrypted =
        await encryptFile(
            original,
            "password123",
            "test.bin"
        );

    const result =
        await decryptFile(
            encrypted,
            "password123"
        );

    const decrypted =
        result.data;

    let equal = true;

    if (
        original.length !==
        decrypted.length
    ) {

        equal = false;
    }

    for (
        let i = 0;
        i < original.length;
        i++
    ) {

        if (
            original[i] !==
            decrypted[i]
        ) {

            equal = false;
            break;
        }
    }

    if (!equal) {

        throw new Error(
            "TypeScript SDK roundtrip failed"
        );
    }

    if (
        result.filename !==
        "test.bin"
    ) {

        throw new Error(
            "Filename restoration failed"
        );
    }

    console.log(
        "TypeScript SDK test passed"
    );
}

main();