#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <string>

class Animal {
protected:
    std::string type;

public:
    Animal(); // Default constructor
    Animal(const Animal& other); // Copy constructor
    Animal& operator=(const Animal& other); // Copy assignment operator
    virtual ~Animal(); // Virtual destructor for proper cleanup

    virtual void makeSound() const;
    std::string getType() const;
};

#endif // ANIMAL_HPP 