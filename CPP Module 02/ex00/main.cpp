#include "Fixed.hpp"
#include <iostream>

int main(void) {
    Fixed a; //made a default constructor called a
    Fixed b(a); //made a copy constructor a called b
    Fixed c; //made a default constructor called c
    c = b; //it will copy all the values of b to c
    std::cout << a.getRawBits() << std::endl; //we print _fixedPointValue from object a
    std::cout << b.getRawBits() << std::endl; //we print _fixedPointValue from object b
    std::cout << c.getRawBits() << std::endl; //we print _fixedPointValue from object c
    return 0;
} 