#include <iostream>
#include <string>
#include "whatever.hpp"


int main(void) {
    // Test with simple types
    int a = 2;
    int b = 3;
    ::swap(a, b);
    std::cout << "a = " << a << ", b = " << b << std::endl;
    std::cout << "min(a, b) = " << ::min(a, b) << std::endl;
    std::cout << "max(a, b) = " << ::max(a, b) << std::endl;

    std::string c = "chaine1";
    std::string d = "chaine2";
    ::swap(c, d);
    std::cout << "c = " << c << ", d = " << d << std::endl;
    std::cout << "min(c, d) = " << ::min(c, d) << std::endl;
    std::cout << "max(c, d) = " << ::max(c, d) << std::endl;

    
    // Edge cases
    std::cout << "\nEdge Cases:" << std::endl;
    
    // Test with equal values
    int x = 5, y = 5;
    std::cout << "Equal values test:" << std::endl;
    std::cout << "min(5, 5) = " << ::min(x, y) << std::endl;  // Should return second value (5)
    std::cout << "max(5, 5) = " << ::max(x, y) << std::endl;  // Should return second value (5)
    
    // Test with const values
    const int const_x = 10, const_y = 20;
    std::cout << "\nConst values test:" << std::endl;
    std::cout << "min(const_x, const_y) = " << ::min(const_x, const_y) << std::endl;
    std::cout << "max(const_x, const_y) = " << ::max(const_x, const_y) << std::endl;

    return 0;
} 