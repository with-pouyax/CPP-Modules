#ifndef DOG_HPP
#define DOG_HPP

#include "Animal.hpp"

class Dog : public Animal {
public:
    // Orthodox Canonical Form
    Dog();
    Dog(const Dog& other);
    virtual ~Dog();
    Dog& operator=(const Dog& other);

    // Member functions
    virtual void makeSound() const;
};

#endif // DOG_HPP 