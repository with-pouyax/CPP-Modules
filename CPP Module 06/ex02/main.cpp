#include "Base.hpp"
#include <iostream>

int main() {

    // Test with pointer
    std::cout << "Testing with pointer:" << std::endl;
    for (int i = 0; i < 5; i++) { // we generate 5 objects
        Base* ptr = generate();
        if (ptr == NULL) {
            std::cerr << "Failed to generate object in pointer test" << std::endl;
            continue; // this continue means that we skip the rest of the loop and go to the next iteration
                      // if we had a break, we would exit the loop and go to the next code block
                      //so in last iteration, if we reach this continue, we will not delete the pointer and we just break the loop
        }
        std::cout << "Generated type: ";
        identify(ptr); // we identify the type of the object
        delete ptr; 
        ptr = NULL;  // Good practice to set pointer to NULL after deletion
    }

    // Test with reference
    std::cout << "\nTesting with reference:" << std::endl;
    for (int i = 0; i < 5; i++) {
        Base* ptr = generate();
        if (ptr == NULL) {
            std::cerr << "Failed to generate object in reference test" << std::endl;
            continue;
        }
        std::cout << "Generated type: ";
        identify(*ptr); //ptr is a pointer to a Base object, so we dereference it to get the object
        delete ptr;
        ptr = NULL;  // Good practice to set pointer to NULL after deletion
    }

    // Test case 1: NULL pointer handling
    std::cout << "\nTest case 1: NULL pointer handling:" << std::endl;
    Base* nullPtr = NULL;
    std::cout << "Testing identify() with NULL pointer: ";
    identify(nullPtr); // This should print "Error: NULL pointer passed to identify"

    // Test case 2: Invalid reference handling (using a pointer that points to wrong type)
    std::cout << "\nTest case 2: Invalid reference handling:" << std::endl;
    Base* ptr = generate();
    if (ptr != NULL) {
        std::cout << "Testing identify() with valid object: ";
        identify(*ptr);
        delete ptr;
    }

    // Test case 3: Memory allocation failure simulation
    std::cout << "\nTest case 3: Memory allocation failure simulation:" << std::endl;
    // Simulate what happens when generate() returns NULL multiple times
    std::cout << "Simulating multiple generation failures:" << std::endl;
    for (int i = 0; i < 3; i++) {
        Base* ptr = generate();
        if (ptr == NULL) {
            std::cout << "Generation attempt " << (i+1) << " failed" << std::endl;
            continue;
        }
        std::cout << "Generation attempt " << (i+1) << " succeeded: ";
        identify(ptr);
        delete ptr;
    }

    return 0;
} 