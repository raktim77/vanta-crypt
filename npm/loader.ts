import ModuleFactory from "./wasm/vantacrypt.js";
import { VantaCryptModule } from "./types.js";

let instance: VantaCryptModule | undefined;

export async function loadVantaCrypt(): Promise<VantaCryptModule> {

    if (!instance) {
        instance =
            await ModuleFactory() as VantaCryptModule;
    }

    return instance;
}