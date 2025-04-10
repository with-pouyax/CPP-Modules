#ifndef DOG_HPP
#define DOG_HPP

#include "Animal.hpp"
#include "Brain.hpp"

class Dog : public Animal {
private:
    Brain* brain;

public:
    Dog(); // Default constructor
    Dog(const Dog& other); // Copy constructor
    Dog& operator=(const Dog& other); // Copy assignment operator
    virtual ~Dog(); // Virtual destructor

    virtual void makeSound() const;
    Brain* getBrain() const;
};

#endif // DOG_HPP 