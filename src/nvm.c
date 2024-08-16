#include "../include/nvm.h"

static NvmEntry nvmEntries[NVM_MAX_ATTRIBUTES];

/**
 * @brief Initializes the NVM storage by loading data from the file.
 *        If the file doesn't exist, initializes the storage with empty values.
 */
void nvm_init() {
    FILE *file = fopen(NVM_STORAGE_FILE, "rb");
    if (file) {
        fread(nvmEntries, sizeof(NvmEntry), NVM_MAX_ATTRIBUTES, file);
        fclose(file);
    } else {
        memset(nvmEntries, 0, sizeof(nvmEntries));
    }
}

/**
 * @brief Saves the current NVM state to the storage file.
 * 
 * @return GP_NVM_SUCCESS on success, GP_NVM_FAILURE on failure to save.
 */
gpNvm_Result nvm_save() {
    FILE *file = fopen(NVM_STORAGE_FILE, "wb");
    if (!file) {
        return FAILURE;
    }
    fwrite(nvmEntries, sizeof(NvmEntry), NVM_MAX_ATTRIBUTES, file);
    fclose(file);
    return SUCCESS;
}

/**
 * @brief Get an attribute's value by its ID from the NVM storage.
 * 
 * @param attrId  Attribute ID .
 * @param pLength Pointer to store the length of the retrieved value.
 * @param pValue Pointer to store the retrieved value.
 * 
 * @return SUCCESS if the attribute is found, NOT_FOUND otherwise.
 */
gpNvm_Result gpNvm_GetAttribute(gpNvm_AttrId attrId, UInt8* pLength, void* pValue) {
    for (int i = 0; i < NVM_MAX_ATTRIBUTES; i++) {
        if (nvmEntries[i].attrId == attrId && nvmEntries[i].length > 0) {
            *pLength = nvmEntries[i].length;
            memcpy(pValue, nvmEntries[i].value, nvmEntries[i].length);
            return SUCCESS;
        }
    }
    return NOT_FOUND;
}

/**
 * @brief Sets an attribute's value by its ID in the NVM storage.
 *        If the attribute ID already exists, it update the value.
 * 
 * @param attrId Attribute ID.
 * @param length The length of the value being set.
 * @param pValue Pointer to the value to be stored.
 * 
 * @return SUCCESS on success, FAILURE on failure.
 */
gpNvm_Result gpNvm_SetAttribute(gpNvm_AttrId attrId, UInt8 length, const void* pValue) {
    if (length > MAX_VALUE_LENGTH) {
        return FAILURE;
    }

    for (int i = 0; i < NVM_MAX_ATTRIBUTES; i++) {
        if (nvmEntries[i].attrId == attrId || nvmEntries[i].length == 0) {
            nvmEntries[i].attrId = attrId;
            nvmEntries[i].length = length;
            memcpy(nvmEntries[i].value, pValue, length);
            return nvm_save();
        }
    }
    return FAILURE;
}