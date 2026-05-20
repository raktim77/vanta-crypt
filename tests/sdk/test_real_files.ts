import fs from "node:fs/promises";

import {
    encryptFile,
    decryptFile
} from "../../npm/wrapper.js";

async function testFile(path: string) {

    const original =
        new Uint8Array(
            await fs.readFile(path)
        );

    const encrypted =
        await encryptFile(
            original,
            "password123"
        );

    const decrypted =
        await decryptFile(
            encrypted,
            "password123"
        );

    if (
        original.length !==
        decrypted.length
    ) {

        throw new Error(
            `${path}: size mismatch`
        );
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

            throw new Error(
                `${path}: binary mismatch at byte ${i}`
            );
        }
    }

    console.log(
        `${path}: PASSED`
    );
}

async function main() {

    await testFile(
        "tests/files/sample.png"
    );

    await testFile(
        "tests/files/sample.pdf"
    );

    await testFile(
        "tests/files/sample.zip"
    );

    await testFile(
        "tests/files/sample.mp4"
    );

    await testFile(
        "tests/files/sample.txt"
    );

    console.log(
        "All real file tests passed"
    );
}

main();