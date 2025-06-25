#include <iostream>
#include "Serializer.hpp"

int main() {
    // Test 1: Normal case
    std::cout << "Test 1: Normal case" << std::endl;
    std::cout << "------------------" << std::endl;
    Data data = {42, "Hello, World!", 3.14};

    // Print original data
    std::cout << "Original Data:" << std::endl;
    std::cout << "Number: " << data.number << std::endl;
    std::cout << "Text: " << data.text << std::endl;
    std::cout << "Value: " << data.value << std::endl;
    std::cout << std::endl;

    // Serialize the pointer
    uintptr_t raw = Serializer::serialize(&data);
    std::cout << "Serialized value: " << raw << std::endl;
    std::cout << std::endl;

    // Deserialize back to a pointer
    Data* ptr = Serializer::deserialize(raw);

    // Verify the pointer is the same
    if (ptr == &data) {
        std::cout << "Pointer comparison successful!" << std::endl;
    } else {
        std::cout << "Pointer comparison failed!" << std::endl;
    }

    // Print data through the deserialized pointer
    std::cout << "\nData through deserialized pointer:" << std::endl;
    std::cout << "Number: " << ptr->number << std::endl;
    std::cout << "Text: " << ptr->text << std::endl;
    std::cout << "Value: " << ptr->value << std::endl;
    std::cout << std::endl;

    //modify the ptr to see if data is modifiable or not
    ptr->number = 100;
    ptr->text = "Hello from 42";
    ptr->value = 1.1;

    //print the modified data
    std::cout << "Modified Data:" << std::endl;
    std::cout << "Number: " << ptr->number << std::endl;
    std::cout << "Text: " << ptr->text << std::endl;
    std::cout << "Value: " << ptr->value << std::endl;
    std::cout << std::endl;

    // Test 2: Null pointer case
    std::cout << "Test 2: Null pointer case" << std::endl;
    std::cout << "----------------------" << std::endl;
    Data* nullPtr = NULL;
    uintptr_t nullRaw = Serializer::serialize(nullPtr);
    std::cout << "Serialized null pointer value: " << nullRaw << std::endl;
    
    Data* deserializedNull = Serializer::deserialize(nullRaw);
    if (deserializedNull == NULL) {
        std::cout << "Successfully handled null pointer case!" << std::endl;
    } else {
        std::cout << "Failed to handle null pointer case!" << std::endl;
    }
    std::cout << std::endl;

    // Test 3: Zero value case
    std::cout << "Test 3: Zero value case" << std::endl;
    std::cout << "---------------------" << std::endl;
    Data* zeroPtr = Serializer::deserialize(0); //we test here if the pointer is NULL means that the pointer is not valid, so -1 is also not valid
    //so we need to handle this case
    if (zeroPtr == NULL) {
        std::cout << "Successfully handled zero value case!" << std::endl;
    } else {
        std::cout << "Failed to handle zero value case!" << std::endl;
    }

    return 0;
} 