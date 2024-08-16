#ifndef NVM_H
#define NVM_H

#include "nvm_types.h"
// Result codes for operations
#define SUCCESS 0
#define FAILURE 1
#define NOT_FOUND 2


//API
void nvm_init(void);
gpNvm_Result nvm_save(void);
gpNvm_Result gpNvm_GetAttribute(gpNvm_AttrId attrId, UInt8* pLength, void* pValue);
gpNvm_Result gpNvm_SetAttribute(gpNvm_AttrId attrId, UInt8 length, const void* pValue);

#endif // NVM_H