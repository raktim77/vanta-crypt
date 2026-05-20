let wasm: any = null;

async function loadWasmModule() {

    //
    // Running directly from source
    //

    try {

        return await import(
            "../wasm/dist/vantacrypt.js"
        );

    } catch {

        //
        // Running from compiled dist/
        //

        return await import(
            "../../wasm/dist/vantacrypt.js"
        );
    }
}

async function getWasm() {

    if (wasm) {
        return wasm;
    }

    const wasmModule =
        await loadWasmModule();

    let initializer: any =
        wasmModule;

    while (
        initializer &&
        typeof initializer !== "function" &&
        initializer.default
    ) {
        initializer = initializer.default;
    }

    if (typeof initializer !== "function") {

        throw new Error(
            "Failed to resolve Wasm module initializer"
        );
    }

    wasm = await initializer();

    return wasm;
}

function uint8ArrayToVector(wasm: any, data: Uint8Array) {
  const vec = new wasm.VectorUint8();

  for (const byte of data) {
    vec.push_back(byte);
  }

  return vec;
}

function vectorToUint8Array(vec: any) {
  const result = new Uint8Array(vec.size());

  for (let i = 0; i < vec.size(); i++) {
    result[i] = vec.get(i);
  }

  return result;
}

export async function encryptFile(
  data: Uint8Array,
  password: string,
): Promise<Uint8Array> {
  const wasm = await getWasm();

  const inputVec = uint8ArrayToVector(wasm, data);

  const encryptedVec = wasm.encryptFile(inputVec, password);

  const result = vectorToUint8Array(encryptedVec);

  inputVec.delete();
  encryptedVec.delete();

  return result;
}

export async function decryptFile(
  data: Uint8Array,
  password: string,
): Promise<Uint8Array> {
  const wasm = await getWasm();

  const inputVec = uint8ArrayToVector(wasm, data);

  const decryptedVec = wasm.decryptFile(inputVec, password);

  const result = vectorToUint8Array(decryptedVec);

  inputVec.delete();
  decryptedVec.delete();

  return result;
}
