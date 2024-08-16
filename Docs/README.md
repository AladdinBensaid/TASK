# NVM SDK

This SDK provides a Non-Volatile Memory (NVM) storage component that allows you to save and retrieve data.

## Features
- Supports storage and retrieval of basic types and structs.
- Includes boundary checks to prevent data overflow.
- Provides easy-to-use APIs for setting and getting attributes.

## Structure
- `/include`: Contains the header files for the SDK.
- `/src`: Contains the source code for the SDK.
- `/tests`: Contains unit tests for the SDK.
- `/examples`: Contains example code showing how to use the SDK.
- `/docs`: Contains documentation for the SDK.

## Getting Started
1. Include the `nvm.h` header file in your project.
2. Initialize the NVM storage with `nvm_init()`.
3. Use `gpNvm_SetAttribute()` to store data and `gpNvm_GetAttribute()` to retrieve it.

## Example
```c
#include "nvm.h"

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