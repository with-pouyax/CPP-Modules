#include "Cat.hpp"
#include <iostream>

Cat::Cat() : Animal() {
    std::cout << "Cat default constructor called" << std::endl;
    this->type = "Cat";
    this->brain = NULL; // Initialize to NULL first
    try {
        this->brain = new Brain();
    }
    catch (const std::bad_alloc& e) {
        std::cerr << "Memory allocation failed for Brain: " << e.what() << std::endl;
        throw; // Re-throw to let the caller handle it
    }
}

Cat::Cat(const Cat& other) : Animal(other) {
   // other is a reference to the Cat object that we want to copy
   // *other is wrong because other is already an object, not a pointer so we can't dereference it
   // other.brain is the member inside the Cat object which is a pointer to a Brain object
   // *other.brain means we dereference the pointer inside the Cat object which is a Brain object
    std::cout << "Cat copy constructor called" << std::endl;
    this->brain = NULL; // Initialize the current object's brain pointer to NULL
    
   try {
    // this->brain mean pointer to the current object's brain
    // we call Brain constructor with brain object of other Cat object

        this->brain = new Brain(*other.brain); 
    }
    catch (const std::bad_alloc& e) {
        std::cerr << "Memory allocation failed for Brain copy: " << e.what() << std::endl;
        throw; // Re-throw to let the caller handle it
    }
}

Cat& Cat::operator=(const Cat& other) {
    std::cout << "Cat copy assignment operator called" << std::endl;

    if (this != &other) { // if the current object is not the same as the other object
        Animal::operator=(other); //we call the operator= of the Animal class with the other object as input means we copy the other object's Animal part to the current object
        // why ? because animal is the base class of Cat
        Brain* temp = NULL;
        try {
            temp = new Brain(*other.brain); // we call Brain copy constructor with brain object of other Cat object
            delete brain; // Only delete old brain if new allocation succeeded
            brain = temp; // now brain now brain point to the temp Brain object which is a copy of the other object's brain
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

Cat::~Cat() {
    std::cout << "Cat destructor called" << std::endl;
    delete brain; // delete NULL is safe in C++
}

void Cat::makeSound() const {
    std::cout << "Meow! Meow!" << std::endl;
}

// Getter for the brain
Brain* Cat::getBrain() const {
    return brain;
} 