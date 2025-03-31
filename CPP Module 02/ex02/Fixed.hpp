#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

class Fixed {
private:
    int _fixedPointValue;
    static const int _fractionalBits;

public:
    // Orthodox Canonical Form
    Fixed(void);                          // Default constructor
    Fixed(const Fixed& other);            // Copy constructor
    Fixed& operator=(const Fixed& other); // Copy assignment operator
    ~Fixed(void);                         // Destructor

    // Additional constructors
    Fixed(const int value);               // Int constructor
    Fixed(const float value);             // Float constructor

    // Member functions
    float toFloat(void) const;
    int toInt(void) const;
    int getRawBits(void) const;
    void setRawBits(int const raw);

    // Comparison operators
    // rhs stands for right hand side
    bool operator>(const Fixed& rhs) const;
    bool operator<(const Fixed& rhs) const;
    bool operator>=(const Fixed& rhs) const;
    bool operator<=(const Fixed& rhs) const;
    bool operator==(const Fixed& rhs) const;
    bool operator!=(const Fixed& rhs) const;

    // Arithmetic operators
    Fixed operator+(const Fixed& rhs) const;
    Fixed operator-(const Fixed& rhs) const;
    Fixed operator*(const Fixed& rhs) const;
    Fixed operator/(const Fixed& rhs) const;

    // Increment/Decrement operators
    Fixed& operator++();    // Pre-increment
    Fixed operator++(int); // Post-increment
    Fixed& operator--();    // Pre-decrement
    Fixed operator--(int); // Post-decrement

    // Static member functions
    static Fixed& min(Fixed& a, Fixed& b);
    static const Fixed& min(const Fixed& a, const Fixed& b);
    static Fixed& max(Fixed& a, Fixed& b);
    static const Fixed& max(const Fixed& a, const Fixed& b);
};

// Stream operator overload
std::ostream& operator<<(std::ostream& os, const Fixed& fixed);

#endif // FIXED_HPP 