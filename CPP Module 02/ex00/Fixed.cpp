#include "Fixed.hpp"
#include <iostream>

// Initialize static member
const int Fixed::_fractionalBits = 8;

//default constructor is responsible for initializing the object with a default value
Fixed::Fixed(void) : _fixedPointValue(0) {
    std::cout << "Default constructor called" << std::endl;
}

//copy constructor
Fixed::Fixed(const Fixed& other) : _fixedPointValue(other._fixedPointValue) {
    std::cout << "Copy constructor called" << std::endl;
}

// we define the behavior of = operator to copy the value of the other object to the current object
// it will receive a const reference to the other object and it will return a reference to the current object
Fixed& Fixed::operator=(const Fixed& other) {
    std::cout << "Copy assignment operator called" << std::endl;
    //'this' is a pointer to the current object
    // so we copy the value of the other object to the current object only if they are not the same object
    if (this != &other) {
        this->_fixedPointValue = other._fixedPointValue;
    }
    //'this' is a pointer to the current object
    // so '*this' is the current object
    return *this;
}

//destructor
//it will destroy the current object
Fixed::~Fixed(void) {
    std::cout << "Destructor called" << std::endl;
}

//it will return the raw value of the fixed point value from the current object
int Fixed::getRawBits(void) const {
    std::cout << "getRawBits member function called" << std::endl;
    return this->_fixedPointValue;
}

//it will set the raw value of the fixed point value from the current object
void Fixed::setRawBits(int const raw) {
    this->_fixedPointValue = raw;
} 