#ifndef FIXED_HPP
#define FIXED_HPP

class Fixed {
private:
    int _fixedPointValue;
    static const int _fractionalBits;  // Declaration only, initialization in cpp

public:
    // Orthodox Canonical Form
    Fixed(void);                    // Default constructor
    Fixed(const Fixed& other);      // Copy constructor
    Fixed& operator=(const Fixed& other); // Copy assignment operator
    ~Fixed(void);                   // Destructor

    // Member functions
    int getRawBits(void) const;
    void setRawBits(int const raw);
};

#endif // FIXED_HPP 