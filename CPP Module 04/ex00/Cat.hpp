#ifndef CAT_HPP
#define CAT_HPP

#include "Animal.hpp"

class Cat : public Animal {
public:
    // Orthodox Canonical Form
    Cat();
    Cat(const Cat& other);
    virtual ~Cat();
    Cat& operator=(const Cat& other);

    // Member functions
    virtual void makeSound() const;
};

#endif // CAT_HPP 