#include <stdbool.h>
#include <string.h>

#include"../../set2/Challenge10/aes.c"

unsigned char* oracle(unsigned char* text){
    unsigned char* result = aes_cbc_encrypt_evp(text,strlen(text),"YELLOW SUBMARINE","YELLOW SUBMARINE");
    return result;
}

unsigned char* decipherOracle(unsigned char* ciphertext, int ciphertextLength){
    unsigned char* result = aes_cbc_decrypt_evp_nopadding(ciphertext,ciphertextLength,
        "YELLOW SUBMARINE","YELLOW SUBMARINE");
    return result;
}

int main(){

    // ciphertext = oracle("A"x48)
    unsigned char* firstCiphertext = oracle("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
    unsigned char* modifiedCiphertext = calloc(48, 1);
    memcpy(modifiedCiphertext,firstCiphertext,16);
    memcpy(modifiedCiphertext+32,firstCiphertext,16);
    unsigned char* deciphered = decipherOracle(modifiedCiphertext,48);
    unsigned char* P_1 = calloc(16,1);
    memcpy(P_1,deciphered,16);
    unsigned char* P_3 = calloc(16,1);
    memcpy(P_3,deciphered+32,16);
    unsigned char* result = xorRawStrings(P_1, P_3, 16);

    for(int i=0;i<16;i++){
        printf("%c",result[i]);
    }
    printf("\n");
    return 0;
}