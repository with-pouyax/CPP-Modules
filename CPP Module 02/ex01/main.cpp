#include <iostream>
#include "Fixed.hpp"

int main(void) {
    Fixed a;              //we create an instance of the Fixed class with default constructor
    Fixed const b(10);    //we create an instance of the Fixed class with a constant value of 10
    Fixed const c(42.42f); //we create an instance of the Fixed class with a constant value of 42.42f
    Fixed const d(b);     //we create an instance of the Fixed class called d and we copy the value of b into it
    
    a = Fixed(1234.4321f); //here we but the values of an instance, made like Fixed(1234.4321f), into a instance

    std::cout << "a is " << a << std::endl; //we print the value in float form
    std::cout << "b is " << b << std::endl;
    std::cout << "c is " << c << std::endl;
    std::cout << "d is " << d << std::endl;
    std::cout << "--------------------------------" << std::endl;
    std::cout << "a is " << a.toInt() << " as integer" << std::endl; //we print the value in integer form
    std::cout << "b is " << b.toInt() << " as integer" << std::endl;
    std::cout << "c is " << c.toInt() << " as integer" << std::endl;
    std::cout << "d is " << d.toInt() << " as integer" << std::endl;

    return 0;
} 