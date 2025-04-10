#include "Dog.hpp"
#include <iostream>

Dog::Dog() : Animal() {
    std::cout << "Dog default constructor called" << std::endl;
    this->type = "Dog";
    this->brain = NULL; // Initialize to NULL first
    try {
        this->brain = new Brain();
    }
    catch (const std::bad_alloc& e) {
        std::cerr << "Memory allocation failed for Brain: " << e.what() << std::endl;
        throw; // Re-throw to let the caller handle it
    }
}

Dog::Dog(const Dog& other) : Animal(other) {
    std::cout << "Dog copy constructor called" << std::endl;
    this->brain = NULL; // Initialize to NULL first
    try {
        this->brain = new Brain(*other.brain); // Deep copy
    }
    catch (const std::bad_alloc& e) {
        std::cerr << "Memory allocation failed for Brain copy: " << e.what() << std::endl;
        throw; // Re-throw to let the caller handle it
    }
}

Dog& Dog::operator=(const Dog& other) {
    std::cout << "Dog copy assignment operator called" << std::endl;
    if (this != &other) {
        Animal::operator=(other);
        Brain* temp = NULL;
        try {
            temp = new Brain(*other.brain); // Create new Brain first
            delete brain; // Only delete old brain if new allocation succeeded
            brain = temp;
        }
        catch (const std::bad_alloc& e) {
            std::cerr << "Memory allocation failed in assignment: " << e.what() << std::endl;
            delete temp; // Clean up if allocation failed
            temp = NULL;
            throw; // Re-throw to let the caller handle it
        }
    }
    return *this;
}

Dog::~Dog() {
    std::cout << "Dog destructor called" << std::endl;
    delete brain; // delete NULL is safe in C++
}

void Dog::makeSound() const {
    std::cout << "Woof! Woof!" << std::endl;
}

Brain* Dog::getBrain() const {
    return brain;
} 