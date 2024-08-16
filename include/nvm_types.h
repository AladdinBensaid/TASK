#ifndef NVM_TYPES_H
#define NVM_TYPES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Type definitions for the module
typedef unsigned char UInt8;
typedef unsigned int UInt32;
typedef UInt8 gpNvm_AttrId;
typedef UInt8 gpNvm_Result;

#define NVM_MAX_ATTRIBUTES 256
#define MAX_VALUE_LENGTH 128
#define MAX_LENGTH 20
//Binairy file to simulate NVM
#define NVM_STORAGE_FILE "nvm_storage.bin"
 
 //Example of structure type of pvalue
typedef struct {
    UInt8 id;
    UInt32 options;
    UInt8 length;
    UInt8 data[MAX_LENGTH];
} gpTestData_t;

// Structure representing an NVM case
typedef struct {
    gpNvm_AttrId attrId;
    UInt8 length;
    UInt8 value[MAX_VALUE_LENGTH];  // Store up to MAX_VALUE_LENGTH bytes for any type
} NvmEntry;

#endif // NVM_TYPES_H 