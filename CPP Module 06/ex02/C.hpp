#ifndef C_HPP
#define C_HPP

#include "Base.hpp"

class C : public Base {
public:
    C();                    // Default constructor
    C(const C& other);      // Copy constructor
    C& operator=(const C& other); // Copy assignment operator
    ~C();                   // Destructor
};

#endif 