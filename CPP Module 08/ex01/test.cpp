#include "Span.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <cstdlib>
#include <ctime>

void printHeader(const std::string& title) {
    std::cout << "\n\033[1;36m" << "=== " << title << " ===\033[0m" << std::endl;
}

void printSeparator() {
    std::cout << "\033[1;33m" << "----------------------------------------\033[0m" << std::endl;
}

void testBasicExample() {
    printHeader("Test 1: Basic Example");
    try {
        Span sp = Span(5);
        sp.addNumber(6);
        sp.addNumber(3);
        sp.addNumber(17);
        sp.addNumber(9);
        sp.addNumber(11);
        std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
        std::cout << "Longest span: " << sp.longestSpan() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    printSeparator();
}

void testEmptySpan() {
    printHeader("Test 2: Empty Span");
    try {
        Span sp = Span(5);
        std::cout << "Shortest span: ";
        std::cout << sp.shortestSpan() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Expected error: " << e.what() << std::endl;
    }
    printSeparator();
}

void testFullSpan() {
    printHeader("Test 3: Full Span");
    try {
        Span sp = Span(3);
        sp.addNumber(1);
        sp.addNumber(2);
        sp.addNumber(3);
        sp.addNumber(4); // Should throw
    } catch (const std::exception& e) {
        std::cout << "Expected error: " << e.what() << std::endl;
    }
    printSeparator();
}

void testLargeSpan() {
    printHeader("Test 4: Large Span with Random Numbers");
    try {
        Span sp = Span(10000);
        srand(time(NULL));
        for (int i = 0; i < 10000; ++i) {
            sp.addNumber(rand());
        }
        std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
        std::cout << "Longest span: " << sp.longestSpan() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    printSeparator();
}

void testRangeIterator() {
    printHeader("Test 5: Range Iterator Test");
    try {
        Span sp = Span(5);
        std::vector<int> v;
        v.push_back(1);
        v.push_back(2);
        v.push_back(3);
        v.push_back(4);
        v.push_back(5);
        sp.addRange(v.begin(), v.end());
        std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
        std::cout << "Longest span: " << sp.longestSpan() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    printSeparator();
}

void testOneElement() {
    printHeader("Test 6: One Element Span");
    try {
        Span sp = Span(1);
        sp.addNumber(1);
        std::cout << "Shortest span: ";
        std::cout << sp.shortestSpan() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Expected error: " << e.what() << std::endl;
    }
    printSeparator();
}

void testDefaultConstructor() {
    printHeader("Test 7: Default Constructor");
    try {
        Span sp = Span();
        std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Expected error: " << e.what() << std::endl;
    }
    printSeparator();
}

void testNegativeNumbers() {
    printHeader("Test 8: Adding Negative Numbers");
    try {
        Span sp = Span(5);
        sp.addNumber(-10);
        sp.addNumber(-5);
        sp.addNumber(0);
        sp.addNumber(5);
        sp.addNumber(10);
        std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
        std::cout << "Longest span: " << sp.longestSpan() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    printSeparator();
}

void testRangeBiggerThanSize() {
    printHeader("Test 9: Range Bigger Than Span Size");
    try {
        Span sp = Span(3);
        std::vector<int> v;
        v.push_back(1);
        v.push_back(2);
        v.push_back(3);
        v.push_back(4);
        sp.addRange(v.begin(), v.end());
    } catch (const std::exception& e) {
        std::cout << "Expected error: " << e.what() << std::endl;
    }
    printSeparator();
}

void testDifferentContainers() {
    printHeader("Test 10: Different Container Types");
    
    std::cout << "Testing with list:" << std::endl;
    try {
        Span sp = Span(5);
        std::list<int> l;
        l.push_back(1);
        l.push_back(2);
        l.push_back(3);
        l.push_back(4);
        l.push_back(5);
        sp.addRange(l.begin(), l.end());
        std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
        std::cout << "Longest span: " << sp.longestSpan() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    std::cout << "\nTesting with deque:" << std::endl;
    try {
        Span sp = Span(5);
        std::deque<int> d;
        d.push_back(1);
        d.push_back(2);
        d.push_back(3);
        d.push_back(4);
        d.push_back(5);
        sp.addRange(d.begin(), d.end());
        std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
        std::cout << "Longest span: " << sp.longestSpan() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    printSeparator();
}

void testInvalidIterators() {
    printHeader("Test 11: Invalid Iterators");
    try {
        Span sp = Span(5);
        std::vector<int> v;
        v.push_back(1);
        v.push_back(2);
        sp.addRange(v.end(), v.begin()); // Invalid range
    } catch (const std::exception& e) {
        std::cout << "Expected error: " << e.what() << std::endl;
    }
    printSeparator();
}

void testInvalidPointers() {
    printHeader("Test 12: NULL-like Iterators");
    try {
        Span sp = Span(5);
        std::vector<int> v;
        v.push_back(1);
        v.push_back(2);
        
        // Test with null-like iterators
        std::vector<int>::iterator null_it = std::vector<int>::iterator(); // it is like a NULL
        sp.addRange(null_it, v.end()); // This should throw InvalidRangeException
    } catch (const std::exception& e) {
        std::cout << "Expected error: " << e.what() << std::endl;
    }

    try {
        Span sp = Span(5);
        std::vector<int> v;
        v.push_back(1);
        v.push_back(2);
        
        // Test with empty range (begin == end)
        sp.addRange(v.begin(), v.begin()); // This should throw InvalidRangeException
    } catch (const std::exception& e) {
        std::cout << "Expected error: " << e.what() << std::endl;
    }
    printSeparator();
}

void testDuplicateNumbers() {
    printHeader("Test 13: Duplicate Numbers");
    try {
        Span sp = Span(5);
        sp.addNumber(1);
        sp.addNumber(1);
        sp.addNumber(2);
        sp.addNumber(2);
        sp.addNumber(3);
        std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
        std::cout << "Longest span: " << sp.longestSpan() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    printSeparator();
}

void testVeryLargeNumbers() {
    printHeader("Test 14: Very Large Numbers");
    try {
        Span sp = Span(3);
        sp.addNumber(2147483647);
        sp.addNumber(0);
        sp.addNumber(-2147483648);
        std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
        std::cout << "Longest span: " << sp.longestSpan() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    printSeparator();
}

void testSizeZero() {
    printHeader("Test 15: Size Zero");
    try {
        Span sp = Span(0);
        sp.addNumber(1);
    } catch (const std::exception& e) {
        std::cout << "Expected error: " << e.what() << std::endl;
    }
    printSeparator();
}

