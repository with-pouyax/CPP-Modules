#include "Fixed.hpp"
#include <cmath>
#include <climits>

const int Fixed::_fractionalBits = 8;

// default constructor
Fixed::Fixed(void) : _fixedPointValue(0) {
    std::cout << "Default constructor called" << std::endl;
}

//---------------------------------------------------------------------------------

// copy constructor
Fixed::Fixed(const Fixed& other) : _fixedPointValue(other._fixedPointValue) {
    std::cout << "Copy constructor called" << std::endl;
}
//---------------------------------------------------------------------------------


Fixed& Fixed::operator=(const Fixed& other) {
    std::cout << "Copy assignment operator called" << std::endl;
    if (this != &other) {
        this->_fixedPointValue = other._fixedPointValue;
    }
    return *this;
}

//---------------------------------------------------------------------------------

// destructor
Fixed::~Fixed(void) {
    std::cout << "Destructor called" << std::endl;
}

//---------------------------------------------------------------------------------

// int constructor
Fixed::Fixed(const int value) {
    std::cout << "Int constructor called" << std::endl;
    // Check for overflow
    if (value > INT_MAX >> _fractionalBits) {
        std::cerr << "Warning: Integer overflow detected. Value capped at INT_MAX." << std::endl;
        _fixedPointValue = INT_MAX;
    }
    // Check for underflow
    else if (value < INT_MIN >> _fractionalBits) {
        std::cerr << "Warning: Integer underflow detected. Value capped at INT_MIN." << std::endl;
        _fixedPointValue = INT_MIN;
    }
    else {
        _fixedPointValue = value << _fractionalBits;
    }
}

//---------------------------------------------------------------------------------

// float constructor
Fixed::Fixed(const float value) {
    std::cout << "Float constructor called" << std::endl;
    // Check for overflow
    if (value >= static_cast<float>(INT_MAX) / (1 << _fractionalBits)) {
        std::cerr << "Warning: Float overflow detected. Value capped at maximum." << std::endl;
        _fixedPointValue = INT_MAX;
    }
    // Check for underflow
    else if (value <= static_cast<float>(INT_MIN) / (1 << _fractionalBits)) {
        std::cerr << "Warning: Float underflow detected. Value capped at minimum." << std::endl;
        _fixedPointValue = INT_MIN;
    }
    else {
        _fixedPointValue = roundf(value * (1 << _fractionalBits));
    }
}

//---------------------------------------------------------------------------------

// toFloat member function
float Fixed::toFloat(void) const {
    return static_cast<float>(this->_fixedPointValue) / (1 << this->_fractionalBits);
}

//---------------------------------------------------------------------------------

// toInt member function
int Fixed::toInt(void) const {
    return this->_fixedPointValue >> this->_fractionalBits;
}

//---------------------------------------------------------------------------------

// getRawBits member function
int Fixed::getRawBits(void) const {
    return this->_fixedPointValue;
}

//---------------------------------------------------------------------------------

// setRawBits member function
void Fixed::setRawBits(int const raw) {
    this->_fixedPointValue = raw;
}

//---------------------------------------------------------------------------------

// Comparison operators

// greater than operator
bool Fixed::operator>(const Fixed& rhs) const {
    return this->_fixedPointValue > rhs._fixedPointValue;
}

//---------------------------------------------------------------------------------

// less than operator
bool Fixed::operator<(const Fixed& rhs) const {
    return this->_fixedPointValue < rhs._fixedPointValue;
}

//---------------------------------------------------------------------------------

// greater than or equal to operator
bool Fixed::operator>=(const Fixed& rhs) const {
    return this->_fixedPointValue >= rhs._fixedPointValue;
}

//---------------------------------------------------------------------------------

// less than or equal to operator
bool Fixed::operator<=(const Fixed& rhs) const {
    return this->_fixedPointValue <= rhs._fixedPointValue;
}

//---------------------------------------------------------------------------------

// equal to operator
bool Fixed::operator==(const Fixed& rhs) const {
    return this->_fixedPointValue == rhs._fixedPointValue;
}

//---------------------------------------------------------------------------------

// not equal to operator
bool Fixed::operator!=(const Fixed& rhs) const {
    return this->_fixedPointValue != rhs._fixedPointValue;
}

//---------------------------------------------------------------------------------

// Arithmetic operators

// addition operator
// it will add the fixed point values of the two objects and return the result as a new Fixed object
Fixed Fixed::operator+(const Fixed& rhs) const {
    Fixed result; // we create a new Fixed object called result

    // we set the sum of the fixed point values of the two objects to the raw bits of the result object
    // and we return the result object
    result.setRawBits(this->_fixedPointValue + rhs._fixedPointValue);
    return result;
}

//---------------------------------------------------------------------------------

// subtraction operator
Fixed Fixed::operator-(const Fixed& rhs) const {
    Fixed result;

    result.setRawBits(this->_fixedPointValue - rhs._fixedPointValue);
    return result;
}

//---------------------------------------------------------------------------------

// multiplication operator
Fixed Fixed::operator*(const Fixed& rhs) const {
    Fixed result;
    
    long long temp = static_cast<long long>(this->_fixedPointValue) * static_cast<long long>(rhs._fixedPointValue);
    result.setRawBits(temp >> this->_fractionalBits);
    return result;
}

//---------------------------------------------------------------------------------

// division operator
Fixed Fixed::operator/(const Fixed& rhs) const {
    if (rhs._fixedPointValue == 0) { // if the rhs object is 0
        std::cerr << "Error: Division by zero" << std::endl; // we print an error message
        return Fixed(); // we return a Fixed object with a raw bit value of 0
    }
    Fixed result;

    // we shift the fixed point value of the lhs object to the left by the number of fractional bits
    // because we want to convert the fixed point value to an integer because rhs is an int
    long long temp = static_cast<long long>(this->_fixedPointValue) << this->_fractionalBits; 
    result.setRawBits(temp / rhs._fixedPointValue);
    return result;
}

//---------------------------------------------------------------------------------
// Increment/Decrement operators

// pre increment operator
Fixed& Fixed::operator++() {
    this->_fixedPointValue++;
    return *this; // we return the incremented object
}

//---------------------------------------------------------------------------------

// post increment operator
Fixed Fixed::operator++(int) {
    Fixed temp(*this); // we create a new Fixed object using copy constructor
    ++(*this); // we increment the current object
    return temp; // we return the temporary object
}

//---------------------------------------------------------------------------------

// pre decrement operator
Fixed& Fixed::operator--() {
    this->_fixedPointValue--;
    return *this;
}

//---------------------------------------------------------------------------------

// post decrement operator
Fixed Fixed::operator--(int) {
    Fixed temp(*this); // we create a new Fixed object using copy constructor

    --(*this); // we decrement the current object
    return temp; // we return the temporary object
}

//---------------------------------------------------------------------------------

// Static member functions

// min function
Fixed& Fixed::min(Fixed& a, Fixed& b) {
    return (a < b) ? a : b; // if a is less than b, return a, otherwise return b
}

//---------------------------------------------------------------------------------

// min function for const objects
const Fixed& Fixed::min(const Fixed& a, const Fixed& b) {
    return (a < b) ? a : b; // if a is less than b, return a, otherwise return b
}

//---------------------------------------------------------------------------------

// max function
Fixed& Fixed::max(Fixed& a, Fixed& b) {
    return (a > b) ? a : b; // if a is greater than b, return a, otherwise return b
}

//---------------------------------------------------------------------------------

// max function for const objects
const Fixed& Fixed::max(const Fixed& a, const Fixed& b) {
    return (a > b) ? a : b; // if a is greater than b, return a, otherwise return b
}

//---------------------------------------------------------------------------------

// Stream operator overload
std::ostream& operator<<(std::ostream& os, const Fixed& fixed) {
    os << fixed.toFloat();
    return os;
} 