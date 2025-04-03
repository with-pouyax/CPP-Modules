#include "Fixed.hpp"
#include <cmath>
#include <limits>



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
    
    // Check for overflow/underflow
    // 23 because 32 - 8 = 24 and 24 - 1 = 23
    // -1 because we have 23 bits for the integer part and 1 bit for the sign
    const int maxValue = (1 << 23) - 1;  // Maximum positive value (2^23 - 1)
    const int minValue = -(1 << 23);     // Minimum negative value (-2^23)
    
    if (value > maxValue) {
        std::cerr << "Warning: Integer overflow detected. Value will be clamped to maximum." << std::endl;
        this->_fixedPointValue = maxValue << this->_fractionalBits;
    }
    else if (value < minValue) {
        std::cerr << "Warning: Integer underflow detected. Value will be clamped to minimum." << std::endl;
        this->_fixedPointValue = minValue << this->_fractionalBits;
    }
    else { // if value is between max and min
        // we shift 8 bits to the left
        this->_fixedPointValue = value << this->_fractionalBits;
    }
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
    
    // Calculate the maximum and minimum values that can be represented
    // 23 bits for integer part (32 - 8 - 1), 1 bit for sign
    const float maxValue = static_cast<float>((1 << 23) - 1);
    const float minValue = static_cast<float>(-(1 << 23));
    
    // Clamp the input value if it's too large or too small
    float clampedValue = value;
    if (value > maxValue) {
        std::cerr << "Warning: Float overflow detected. Value will be clamped to maximum." << std::endl;
        clampedValue = maxValue;
    }
    else if (value < minValue) {
        std::cerr << "Warning: Float underflow detected. Value will be clamped to minimum." << std::endl;
        clampedValue = minValue;
    }
    
    // by 1 << 8 we shift 8 bits to the left so we have 256 in fixed point form
    // so 256 = 00000000 00000000 00000001 00000000
    // so by multiplying our value by 256 in fixed point form we convert it to a fixed point value
    // imagine we have 3.12f * 256 = 800.32 by rounding it we get 800
    // so 800 = 00000011 00100100
    //In fixed-point (8 fractional bits), this represents: 800 / 256 = 3.125
    // it is accurate enough for our purposes
    this->_fixedPointValue = roundf(clampedValue * (1 << this->_fractionalBits));
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
    // shifting 8 bits to the right is like dividing by 2^8 = 256
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