export interface VantaCryptModule {

    encrypt_buffer(
        input: string,
        password: string
    ): number[];

    decrypt_buffer(
        input: number[],
        password: string
    ): string;
}