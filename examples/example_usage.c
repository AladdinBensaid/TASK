#include "../include/nvm.h"
#include "../src/nvm.c"

int main() {
    nvm_init();

    UInt8 value = 10;
    gpNvm_SetAttribute(1, sizeof(value), &value);

    UInt8 retrievedValue;
    UInt8 retrievedLength;
    gpNvm_GetAttribute(1, &retrievedLength, &retrievedValue);

    printf("Retrieved value: %d\n", retrievedValue);

    return 0;
}