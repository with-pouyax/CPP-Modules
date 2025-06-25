#ifndef B_HPP
#define B_HPP

#include "Base.hpp"

class B : public Base {
public:
    B();                    // Default constructor
    B(const B& other);      // Copy constructor
    B& operator=(const B& other); // Copy assignment operator
    ~B();                   // Destructor
};

#endif 