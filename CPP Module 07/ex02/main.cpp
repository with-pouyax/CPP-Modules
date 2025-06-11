#include <iostream>
#include "Array.hpp"

void printTitle(const std::string& title) {
    std::cout << "\n\033[1;36m" << std::string(50, '=') << "\033[0m" << std::endl;
    std::cout << "\033[1;36m" << title << "\033[0m" << std::endl;
    std::cout << "\033[1;36m" << std::string(50, '=') << "\033[0m" << std::endl;
}

void printSubtitle(const std::string& subtitle) {
    std::cout << "\n\033[1;33m" << subtitle << "\033[0m" << std::endl;
    std::cout << "\033[1;33m" << std::string(subtitle.length(), '-') << "\033[0m" << std::endl;
}

void testIntArray() {
    printTitle("TESTING INTEGER ARRAY");
    
    printSubtitle("Default Constructor Test");
    Array<int> empty;
    try {
        std::cout << "Attempting to print empty 1st element (should fail):" << std::endl;
        std::cout << "empty[0] = " << empty[0] << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "\033[1;31mError: " << e.what() << "\033[0m" << std::endl;
    }
    std::cout << "Empty array size: " << empty.size() << std::endl;
    
    //------------------------------------------------------

    printSubtitle("Size Constructor Test");
    Array<int> numbers(5);
    std::cout << "Array size: " << numbers.size() << std::endl;
    try {
        std::cout << "Attempting to print all elements of numbers array:" << std::endl;
        for (unsigned int i = 0; i < numbers.size(); i++) {
            std::cout << "numbers[" << i << "] = " << numbers[i] << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "\033[1;31mError: " << e.what() << "\033[0m" << std::endl;
    }

   //-------------------------------------------------------

    printSubtitle("Element Assignment Test");
    for (unsigned int i = 0; i < 5; i++) {
        numbers[i] = i * 10; // Assign values 0, 10, 20, 30, 40
        std::cout << "numbers[" << i << "] = " << numbers[i] << std::endl;
    }
    
    //-------------------------------------------------------

    printSubtitle("Copy Constructor Test");
    Array<int> copy(numbers);
    for (unsigned int i = 0; i < copy.size(); i++) {
        std::cout << "copy[" << i << "] = " << copy[i] << std::endl;
    }
    
    //-------------------------------------------------------

    printSubtitle("Assignment Operator Test");
    Array<int> assigned;
    assigned = numbers;
    for (unsigned int i = 0; i < assigned.size(); i++) {
        std::cout << "assigned[" << i << "] = " << assigned[i] << std::endl;
    }
    
    //-------------------------------------------------------

    printSubtitle("Out of Bounds Test");
    try {
        std::cout << "Attempting to access index 5 (should fail):" << std::endl;
        numbers[5] = 50;
    } catch (const std::exception& e) {
        std::cerr << "\033[1;31mError: " << e.what() << "\033[0m" << std::endl;
    }
    //-------------------------------------------------------
    try {
        std::cout << "Attempting to access index -1 (should fail):" << std::endl;
        numbers[-1] = 50;
    } catch (const std::exception& e) {
        std::cerr << "\033[1;31mError: " << e.what() << "\033[0m" << std::endl;
    }
}

void testStringArray() {
    printTitle("TESTING STRING ARRAY");
    
    printSubtitle("Size Constructor Test");
    Array<std::string> emptyStrings(3);
    std::cout << "String array size: " << emptyStrings.size() << std::endl;
    try {
        std::cout << "Attempting to print empty 1st element:" << std::endl;
        std::cout << "emptyStrings[0] = \"" << emptyStrings[0] << "\"" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "\033[1;31mError: " << e.what() << "\033[0m" << std::endl;
    }
    //-------------------------------------------------------

    printSubtitle("String Array Creation and Assignment");
    Array<std::string> strings(3);
    strings[0] = "Hello";
    strings[1] = "42";
    strings[2] = "School";
    
    std::cout << "String array contents:" << std::endl;
    for (unsigned int i = 0; i < strings.size(); i++) {
        std::cout << "strings[" << i << "] = " << strings[i] << std::endl;
    }
    
    //-------------------------------------------------------

    printSubtitle("String Array Copy Test");
    Array<std::string> stringCopy(strings);
    for (unsigned int i = 0; i < stringCopy.size(); i++) {
        std::cout << "stringCopy[" << i << "] = " << stringCopy[i] << std::endl;
    }
}

void testFloatArray() {
    printTitle("TESTING FLOAT ARRAY");
    
    printSubtitle("Size Constructor Test");
    Array<float> emptyFloats(4);
    std::cout << "Float array size: " << emptyFloats.size() << std::endl;
    try {
        std::cout << "Attempting to print empty 1st element:" << std::endl;
        std::cout << "emptyFloats[0] = " << emptyFloats[0] << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "\033[1;31mError: " << e.what() << "\033[0m" << std::endl;
    }

    //-------------------------------------------------------
    
    printSubtitle("Float Array Creation and Assignment");
    Array<float> floats(4);
    floats[0] = 3.14f;
    floats[1] = 2.718f;
    floats[2] = 1.414f;
    floats[3] = 1.732f;
    
    std::cout << "Float array contents:" << std::endl;
    for (unsigned int i = 0; i < floats.size(); i++) {
        std::cout << "floats[" << i << "] = " << floats[i] << std::endl;
    }
}

void testConstArray() {
    printTitle("TESTING CONST ARRAY");
    
    printSubtitle("Const Array Creation");
    
    const Array<int> constArray(4);
    std::cout << "Const array size: " << constArray.size() << std::endl;
    
    try {
        std::cout << "Attempting to print all elements of constArray:" << std::endl;
        for (unsigned int i = 0; i < constArray.size(); i++) {
            std::cout << "constArray[" << i << "] = " << constArray[i] << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "\033[1;31mError: " << e.what() << "\033[0m" << std::endl;
    }
    
    //-------------------------------------------------------
    
    printSubtitle("Const Array Modification Test");
    try {
        std::cout << "Attempting to modify const array (should fail):" << std::endl;
        //constArray[0] = 42;  // This should fail to compile
        std::cout << "constArray[0] = " << constArray[0] << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "\033[1;31mError: " << e.what() << "\033[0m" << std::endl;
    }
    
    //-------------------------------------------------------
    
    printSubtitle("Const Array Copy Test");
    Array<int> nonConstArray(constArray);
    for (unsigned int i = 0; i < nonConstArray.size(); i++) {
        std::cout << "nonConstArray[" << i << "] = " << nonConstArray[i] << std::endl;
    }
}

void testMemoryManagement() {
    printTitle("TESTING MEMORY MANAGEMENT");
    
    printSubtitle("Large Array Allocation Test");
    try {
        std::cout << "Attempting to create a large array (1,000,000 elements)..." << std::endl;
        Array<int> large(1000000000);
        std::cout << "\033[1;32mSuccess: Large array created successfully\033[0m" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "\033[1;31mError creating large array: " << e.what() << "\033[0m" << std::endl;
    }
    
    printSubtitle("Multiple Allocations/Deallocations Test");
    {
        Array<int> a(5);
        Array<int> b(5);
        a = b;  // Test assignment
        Array<int> c(a);  // Test copy
    }  // Test destructors
    std::cout << "\033[1;32mSuccess: Multiple allocations and deallocations completed\033[0m" << std::endl;
}

int main() {
    try {
        testIntArray();
        testStringArray();
        testFloatArray();
        testConstArray();
        testMemoryManagement();
        
        printTitle("TEST RESULTS");
        std::cout << "\033[1;32mAll tests completed successfully!\033[0m" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "\033[1;31mUnexpected error: " << e.what() << "\033[0m" << std::endl;
        return 1;
    }
    
    return 0;
} 