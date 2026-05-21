export interface VantaCryptModule {
  encryptFile(
    data: Uint8Array,
    password: string,
    filename: string,
  ): Promise<Uint8Array>;

  decryptFile(
    data: Uint8Array,
    password: string,
  ): Promise<{
    data: Uint8Array;
    filename: string;
  }>;
}
