#include "Span.hpp"
#include "test.hpp"
#include <iostream>

int main() {
    std::cout << "\033[1;32m" << "=== SPAN CLASS TEST SUITE ===\033[0m" << std::endl;
    
    // Run all tests
    testBasicExample();
    testEmptySpan();
    testFullSpan();
    testLargeSpan();
    testRangeIterator();
    testOneElement();
    testSameElements();
    testNegativeNumbers();
    testRangeBiggerThanSize();
    testDifferentContainers();
    testInvalidIterators();
    testIteratorEdgeCases();
    testDuplicateNumbers();
    testVeryLargeNumbers();
    testSizeZero();
    testSizeOne();

    std::cout << "\033[1;32m" << "\n=== TEST SUITE COMPLETED ===\033[0m" << std::endl;
    return 0;
} 