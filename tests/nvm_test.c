#include "../include/nvm.h"
#include "../src/nvm.c"
#include <assert.h>

/**
 * @brief Unit test to validate basic attribute setting and retrieval.
 */
void test_basic_attribute() {
    UInt8 value = 42;
    assert(gpNvm_SetAttribute(1, sizeof(value), &value) == SUCCESS);

    UInt8 retrievedValue;
    UInt8 retrievedLength;
    assert(gpNvm_GetAttribute(1, &retrievedLength, &retrievedValue) == SUCCESS);
    assert(retrievedLength == sizeof(value));
    assert(retrievedValue == value);

    printf("test_basic_attribute passed\n");
}

/**
 * @brief Unit test to validate the storage and retrieval of a structure.
 */
void test_struct_attribute() {
    gpTestData_t testData = { .id = 1, .options = 00001, .length = 5, .data = {1, 2, 3, 4, 5} };
    assert(gpNvm_SetAttribute(2, sizeof(testData), &testData) == SUCCESS);

    gpTestData_t retrievedTestData;
    UInt8 retrievedLength;
    assert(gpNvm_GetAttribute(2, &retrievedLength, &retrievedTestData) == SUCCESS);
    assert(retrievedLength == sizeof(testData));
    assert(memcmp(&testData, &retrievedTestData, sizeof(testData)) == 0);

    printf("test_struct_attribute passed\n");
}

/**
 * @brief Tests setting and getting an array of UInt8.
 */
void test_SetAndGetArray() {
    UInt8 value[] = {10, 20, 30, 40, 50};
    gpNvm_AttrId attrId = 4;
    UInt8 retrievedValue[sizeof(value)];
    UInt8 length;

    assert(gpNvm_SetAttribute(attrId, sizeof(value), value) == SUCCESS);
    assert(gpNvm_GetAttribute(attrId, &length, retrievedValue) == SUCCESS);
    assert(length == sizeof(value));
    assert(memcmp(retrievedValue, value, sizeof(value)) == 0);

    printf("test_SetAndGetArray passed.\n");
}
/**
 * @brief Unit test to validate behavior when exceeding the maximum allowed value length.
 */
void test_boundary_conditions() {
    UInt8 longValue[MAX_VALUE_LENGTH + 1] = {0};

    gpNvm_Result result = gpNvm_SetAttribute(3, MAX_VALUE_LENGTH + 1, longValue);
    assert(result == FAILURE);

    printf("test_boundary_conditions passed\n");
}

/**
 * @brief Unit test to validate overwrite behavior for an attribute.
 */
void test_overwrite_behavior() {
    UInt8 value1 = 42;
    assert(gpNvm_SetAttribute(4, sizeof(value1), &value1) == SUCCESS);

    UInt8 value2 = 84;
    assert(gpNvm_SetAttribute(4, sizeof(value2), &value2) == SUCCESS);

    UInt8 retrievedValue;
    UInt8 retrievedLength;
    assert(gpNvm_GetAttribute(4, &retrievedLength, &retrievedValue) == SUCCESS);
    assert(retrievedLength == sizeof(value2));
    assert(retrievedValue == value2);

    printf("test_overwrite_behavior passed\n");
}

int main() {
    nvm_init();

    test_basic_attribute();
    test_struct_attribute();
    test_SetAndGetArray();
    test_boundary_conditions();
    test_overwrite_behavior();

    return 0;
}