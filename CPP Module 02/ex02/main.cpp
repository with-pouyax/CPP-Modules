#include <iostream>
#include <climits>
#include <cmath>
#include "Fixed.hpp"

// ANSI color codes
#define YELLOW "\033[33m"
#define RESET "\033[0m"

void printTitle(const std::string& title) {
    std::cout << "\n" << YELLOW << "=== " << title << " ===" << RESET << std::endl;
}

void testArithmeticOperators() {
    printTitle("Testing Arithmetic Operators");
    
    Fixed a(10.5f); // we create a Fixed object called a with a float value of 10.5
    Fixed b(2.25f); // we create a Fixed object called b with a float value of 2.25
    
    std::cout << "a = " << a << ", b = " << b << std::endl; // we print the values of a and b
    std::cout << "a + b = " << (a + b) << std::endl;
    std::cout << "a - b = " << (a - b) << std::endl;
    std::cout << "a * b = " << (a * b) << std::endl;
    std::cout << "a / b = " << (a / b) << std::endl;
    
    // Test division by zero
    Fixed zero;
    std::cout << "a / 0 = ";
    std::cout << (a / zero) << std::endl;
}

void testComparisonOperators() {
    printTitle("Testing Comparison Operators");
    
    Fixed a(42.42f);
    Fixed b(42.42f);
    Fixed c(10);
    
    std::cout << "a = " << a << ", b = " << b << ", c = " << c << std::endl;
    std::cout << "a == b: " << (a == b) << std::endl;
    std::cout << "a != c: " << (a != c) << std::endl;
    std::cout << "a > c: " << (a > c) << std::endl;
    std::cout << "c < b: " << (c < b) << std::endl;
    std::cout << "a >= b: " << (a >= b) << std::endl;
    std::cout << "c <= b: " << (c <= b) << std::endl;
}

void testIncrementDecrement() {
    printTitle("Testing Increment/Decrement");
    
    Fixed a(5.05f);
    std::cout << "Initial a = " << a << std::endl;
    
    std::cout << "++a = " << ++a << std::endl;
    std::cout << "a = " << a << std::endl;
    std::cout << "a++ = " << a++ << std::endl;
    std::cout << "a = " << a << std::endl;
    
    std::cout << "--a = " << --a << std::endl;
    std::cout << "a = " << a << std::endl;
    std::cout << "a-- = " << a-- << std::endl;
    std::cout << "a = " << a << std::endl;
}

void testMinMax() {
    printTitle("Testing Min/Max Functions");
    
    Fixed a(10.1f);
    Fixed b(10.2f);
    Fixed const c(42.42f);
    Fixed const d(-42.42f);
    
    std::cout << "a = " << a << ", b = " << b << std::endl;
    std::cout << "c = " << c << ", d = " << d << std::endl;
    
    std::cout << "min(a,b) = " << Fixed::min(a, b) << std::endl;
    std::cout << "max(a,b) = " << Fixed::max(a, b) << std::endl;
    std::cout << "min(c,d) = " << Fixed::min(c, d) << std::endl;
    std::cout << "max(c,d) = " << Fixed::max(c, d) << std::endl;
}

void testOverflowUnderflow() {
    printTitle("Testing Overflow/Underflow Protection");
    
    // Test integer constructor with extreme values
    std::cout << YELLOW << "\nTesting integer constructor limits:" << RESET << std::endl;
    Fixed maxInt(INT_MAX); // we create a Fixed object called maxInt with the maximum integer value
    Fixed minInt(INT_MIN);
    
    std::cout << "--------------------------------" << std::endl;
    std::cout << "MAX_INT: " << maxInt << std::endl; 
    std::cout << "MIN_INT: " << minInt << std::endl;
    std::cout << "--------------------------------" << std::endl;
    // Test float constructor with extreme values
    std::cout << YELLOW << "\nTesting float constructor limits:" << RESET << std::endl;
    Fixed normalFloat(42.42f);
    // Test overflow with large floats
    Fixed bigFloat1(INT_MAX * 1.5f); // we create a Fixed object called bigFloat1 with a value of INT_MAX * 1.5
    Fixed bigFloat2(1e20f); // 1e20f = 1 × 10^20
    Fixed bigFloat3(INFINITY); // INFINITY is a big constant usually used for overflow
    
    // Test underflow with small floats
    Fixed smallFloat1(INT_MIN * 1.5f);
    Fixed smallFloat2(-1e20f);
    Fixed smallFloat3(-INFINITY);
    
    std::cout << "--------------------------------" << std::endl;
    std::cout << "Normal float: " << normalFloat << std::endl; // we print the value of normalFloat
    std::cout << "Big float 1 (should be capped): " << bigFloat1 << std::endl;
    std::cout << "Big float 2 (should be capped): " << bigFloat2 << std::endl;
    std::cout << "Big float 3 (infinity, should be capped): " << bigFloat3 << std::endl;
    std::cout << "Small float 1 (should be capped): " << smallFloat1 << std::endl;
    std::cout << "Small float 2 (should be capped): " << smallFloat2 << std::endl;
    std::cout << "Small float 3 (-infinity, should be capped): " << smallFloat3 << std::endl;
    std::cout << "--------------------------------" << std::endl;
}

int main(void) {
    printTitle("Original Test from Subject");
    Fixed a;
    Fixed const b(Fixed(5.05f) * Fixed(2));

    std::cout << a << std::endl;
    std::cout << ++a << std::endl;
    std::cout << a << std::endl;
    std::cout << a++ << std::endl;
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << Fixed::max(a, b) << std::endl;

    // Additional comprehensive tests
    testArithmeticOperators(); 
    testComparisonOperators();
    testIncrementDecrement();
    testMinMax();
    testOverflowUnderflow();

    return 0;
}