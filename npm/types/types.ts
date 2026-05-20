export interface VantaCryptModule {

    encryptFile(
        data: Uint8Array,
        password: string
    ): Promise<Uint8Array>;

    decryptFile(
        data: Uint8Array,
        password: string
    ): Promise<Uint8Array>;
}