#ifndef CAT_HPP
#define CAT_HPP

#include "Animal.hpp"
#include "Brain.hpp"

class Cat : public Animal {
private:
    Brain* brain;

public:
    Cat(); // Default constructor
    Cat(const Cat& other); // Copy constructor
    Cat& operator=(const Cat& other); // Copy assignment operator
    virtual ~Cat(); // Virtual destructor

    virtual void makeSound() const;
    Brain* getBrain() const;
};

#endif // CAT_HPP 