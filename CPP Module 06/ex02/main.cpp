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
        try {
            identify(*ptr);
        } catch (const std::exception& e) {
            std::cerr << "Error during reference identification: " << e.what() << std::endl;
        }
        delete ptr;
        ptr = NULL;  // Good practice to set pointer to NULL after deletion
    }

    return 0;
} 