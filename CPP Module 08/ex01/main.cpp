#include "Span.hpp"
#include "test.hpp"
#include <iostream>

int main() {
    std::cout << "\033[1;32m" << "=== SPAN CLASS TEST SUITE ===\033[0m" << std::endl;

    // Run all tests
    testBasicExample();           //1- ok
    testEmptySpan();              //2- ok
    testFullSpan();               //3- ok
    testLargeSpan();              //4- ok
    testRangeIterator();          //5- ok
    testOneElement();             //6- ok
    testDefaultConstructor();     //7- ok
    testNegativeNumbers();        //8- ok
    testRangeBiggerThanSize();    //9- ok
    testDifferentContainers();    //10- ok
    testInvalidIterators();      //11- ok
    testInvalidPointers();       //12- ok
    testDuplicateNumbers();      //13- ok
    testVeryLargeNumbers();      //14- ok
    testSizeZero();              //15- ok

    std::cout << "\033[1;32m" << "\n=== TEST SUITE COMPLETED ===\033[0m" << std::endl;
    return 0;
}