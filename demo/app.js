import init from "../wasm/dist/vantacrypt.js";

const wasm = await init();

const fileInput =
    document.getElementById("fileInput");

const passwordInput =
    document.getElementById("passwordInput");

const encryptBtn =
    document.getElementById("encryptBtn");

const decryptBtn =
    document.getElementById("decryptBtn");

const status =
    document.getElementById("status");

function uint8ArrayToVector(data) {

    const vec = new wasm.VectorUint8();

    for (const byte of data) {
        vec.push_back(byte);
    }

    return vec;
}

function vectorToUint8Array(vec) {

    const result =
        new Uint8Array(vec.size());

    for (let i = 0; i < vec.size(); i++) {
        result[i] = vec.get(i);
    }

    return result;
}

function downloadFile(
    data,
    filename
) {

    const blob =
        new Blob([data]);

    const url =
        URL.createObjectURL(blob);

    const a =
        document.createElement("a");

    a.href = url;

    a.download = filename;

    document.body.appendChild(a);

    a.click();

    a.remove();

    URL.revokeObjectURL(url);
}

async function readSelectedFile() {

    const file =
        fileInput.files[0];

    if (!file) {

        throw new Error(
            "No file selected"
        );
    }

    return {
        file,
        data: new Uint8Array(
            await file.arrayBuffer()
        )
    };
}

encryptBtn.addEventListener(
    "click",
    async () => {

        try {

            status.textContent =
                "Encrypting...";

            const password =
                passwordInput.value;

            if (!password) {

                throw new Error(
                    "Password required"
                );
            }

            const {
                file,
                data
            } = await readSelectedFile();

            const inputVec =
                uint8ArrayToVector(data);

            const encryptedVec =
                wasm.encryptFile(
                    inputVec,
                    password
                );

            const encrypted =
                vectorToUint8Array(
                    encryptedVec
                );

            inputVec.delete();
            encryptedVec.delete();

            downloadFile(
                encrypted,
                file.name + ".vc"
            );

            status.textContent =
                "Encryption complete";

        } catch (err) {

            console.error(err);

            status.textContent =
                err.message;
        }
    }
);

decryptBtn.addEventListener(
    "click",
    async () => {

        try {

            status.textContent =
                "Decrypting...";

            const password =
                passwordInput.value;

            if (!password) {

                throw new Error(
                    "Password required"
                );
            }

            const {
                file,
                data
            } = await readSelectedFile();

            const inputVec =
                uint8ArrayToVector(data);

            const decryptedVec =
                wasm.decryptFile(
                    inputVec,
                    password
                );

            const decrypted =
                vectorToUint8Array(
                    decryptedVec
                );

            inputVec.delete();
            decryptedVec.delete();

            let outputName =
                file.name;

            if (
                outputName.endsWith(".vc")
            ) {

                outputName =
                    outputName.slice(0, -3);

            } else {

                outputName =
                    "decrypted_" +
                    outputName;
            }

            downloadFile(
                decrypted,
                outputName
            );

            status.textContent =
                "Decryption complete";

        } catch (err) {

            console.error(err);

            status.textContent =
                err.message;
        }
    }
);