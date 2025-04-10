#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <string>
#include <iostream>

class Animal {
protected:
    std::string type;

public:
    // Orthodox Canonical Form
    Animal();
    Animal(const Animal& other);
    virtual ~Animal(); // we need to make our destructor virtual because we used already virtual functions in our class
    Animal& operator=(const Animal& other);

    // Member functions
    virtual void makeSound() const; // we need to make it virtual because we want to override it in derived classes
    std::string getType() const;
};

#endif // ANIMAL_HPP 