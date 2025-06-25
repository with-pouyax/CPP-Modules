#ifndef A_HPP
#define A_HPP

#include "Base.hpp"

class A : public Base {
public:
    A();                    // Default constructor
    A(const A& other);      // Copy constructor
    A& operator=(const A& other); // Copy assignment operator
    ~A();                   // Destructor
};

#endif 