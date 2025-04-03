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

    std::cout << "--------------------------------" << std::endl;
    std::cout << "Testing overflow/underflow cases:" << std::endl;
    
    // Testing integer overflow
    Fixed hugeInt(8388608);  // 2^23 (max value + 1)
    std::cout << "Huge integer (should overflow): " << hugeInt << std::endl;
    std::cout << std::endl;
    
    // Testing integer underflow
    Fixed smallInt(-8388609);  // -2^23 - 1 (min value - 1)
    std::cout << "Small integer (should underflow): " << smallInt << std::endl;
    std::cout << std::endl;
    
    // Testing float overflow
    Fixed hugeFloat(8388608.0f);  // 2^23 (max value + 1)
    std::cout << "Huge float (should overflow): " << hugeFloat << std::endl;
    std::cout << std::endl;

    // Testing float underflow
    Fixed smallFloat(-8388609.0f);  // -2^23 - 1 (min value - 1)
    std::cout << "Small float (should underflow): " << smallFloat << std::endl;
    std::cout << std::endl;

    // Testing conversion overflow
    Fixed maxValue(8388607);  // 2^23 - 1 (max value)
    std::cout << "Max value to int: " << maxValue.toInt() << std::endl;
    std::cout << std::endl;

    // Testing conversion underflow
    Fixed minValue(-8388608);  // -2^23 (min value)
    std::cout << "Min value to int: " << minValue.toInt() << std::endl;
    std::cout << std::endl;
    
    return 0;
} 