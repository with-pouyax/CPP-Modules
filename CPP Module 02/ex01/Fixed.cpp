#include "Fixed.hpp"
#include <cmath>

const int Fixed::_fractionalBits = 8;
//---------------------------------------------------------------------------------
// Default constructor
Fixed::Fixed(void) : _fixedPointValue(0) {
    std::cout << "Default constructor called" << std::endl;
}
//---------------------------------------------------------------------------------
// Copy constructor
Fixed::Fixed(const Fixed& other) : _fixedPointValue(other._fixedPointValue) {
    std::cout << "Copy constructor called" << std::endl;
}
//---------------------------------------------------------------------------------
// Copy assignment operator
Fixed& Fixed::operator=(const Fixed& other) {
    std::cout << "Copy assignment operator called" << std::endl;
    if (this != &other) {
        this->_fixedPointValue = other._fixedPointValue;
    }
    return *this;
}
//---------------------------------------------------------------------------------
// Destructor
Fixed::~Fixed(void) {
    std::cout << "Destructor called" << std::endl;
}
//---------------------------------------------------------------------------------
// Int constructor
Fixed::Fixed(const int value) {
    std::cout << "Int constructor called" << std::endl;
    // if we shift 0001 one to the left, it will be 0010
    // 0001 = 1 and 0010 = 2 so we multiply 1 to 2^1
    // so if we want to shift 8 bits to the left, we multiply 1 to 2^8
    // this is happening here
    // so 00000001 << 8 = 0000000100000000
    // in fixed point, we have 8 bits for the integer part and 8 bits for the fractional part
    // so here 0000000100000000 = 1.0
    this->_fixedPointValue = value << this->_fractionalBits;
}
//---------------------------------------------------------------------------------
// Float constructor
//here we receive a float value and we convert it to a fixed point value
// imagine we received pi number
// so our fixed point value will be 3.14159f
// so we gonna have 3.14159f * 256 = 804.24704
// so after rounding it will be 804
//804 = 00000011 00100100 
//In fixed-point (8 fractional bits), this represents: 804 / 256 = 3.140625

Fixed::Fixed(const float value) {
    std::cout << "Float constructor called" << std::endl;
    
    this->_fixedPointValue = roundf(value * (1 << this->_fractionalBits));
}
//---------------------------------------------------------------------------------
//here we convert the fixed point value to a float
float Fixed::toFloat(void) const {
    //static_cast is a function that converts a value to a specific type
    //<float> is the type we want to convert the value to
    // here we get the converted the fixed point value to a float by dividing it by 256 but it is still in integer form
    // so using static_cast <float> we convert it to a float
    return static_cast<float>(this->_fixedPointValue) / (1 << this->_fractionalBits);
}
//---------------------------------------------------------------------------------
//here we convert the fixed point value to an int
int Fixed::toInt(void) const {
    //here we shift the fixed point value to the right by the number of fractional bits (8) to convert it to an int
    return this->_fixedPointValue >> this->_fractionalBits;
}
//---------------------------------------------------------------------------------
//here we get the raw value of the fixed point value
//this is a getter function that returns the raw value of the fixed point value
int Fixed::getRawBits(void) const {
    return this->_fixedPointValue;
}
//---------------------------------------------------------------------------------
//here we set the raw value of the fixed point value
//this is a setter function that sets the raw value of the fixed point value
void Fixed::setRawBits(int const raw) {
    this->_fixedPointValue = raw;
}
//---------------------------------------------------------------------------------
//here we overload the << operator to print the fixed point value as a float
// so we define a special behavior for the << operator when one side is a Fixed object and the other side is an ostream object
// by ostream we mean the output stream, like cout
std::ostream& operator<<(std::ostream& COUT, const Fixed& fixed) {
    COUT << fixed.toFloat();
    return COUT;
}