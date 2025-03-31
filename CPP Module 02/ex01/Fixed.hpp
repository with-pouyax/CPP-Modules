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
};

// Stream operator overload
std::ostream& operator<<(std::ostream& os, const Fixed& fixed);

#endif // FIXED_HPP 