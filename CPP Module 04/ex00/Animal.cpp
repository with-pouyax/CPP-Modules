#include "Animal.hpp"

// in our default constructor, we the default type to "Animal"
Animal::Animal() : type("Animal") {
    std::cout << "Animal constructor called" << std::endl;
}

Animal::Animal(const Animal& other) : type(other.type) {
    std::cout << "Animal copy constructor called" << std::endl;
}

Animal::~Animal() {
    std::cout << "Animal destructor called" << std::endl;
}

Animal& Animal::operator=(const Animal& other) {
    std::cout << "Animal assignment operator called" << std::endl;
    if (this != &other)
        this->type = other.type;
    return *this;
}

void Animal::makeSound() const {
    std::cout << "Animal sound" << std::endl;
}

std::string Animal::getType() const {
    return this->type;
} 