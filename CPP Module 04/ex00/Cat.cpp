#include "Cat.hpp"

// in our default constructor, our default type is "Cat"
Cat::Cat() {
    this->type = "Cat";
    std::cout << "Cat constructor called" << std::endl;
}

// in our copy constructor, we call the parent class's
Cat::Cat(const Cat& other) : Animal(other) {
    std::cout << "Cat copy constructor called" << std::endl;
}

Cat::~Cat() {
    std::cout << "Cat destructor called" << std::endl;
}

Cat& Cat::operator=(const Cat& other) {
    std::cout << "Cat assignment operator called" << std::endl;
    if (this != &other)
        Animal::operator=(other);
    return *this;
}

void Cat::makeSound() const {
    std::cout << "Meow!" << std::endl;
} 