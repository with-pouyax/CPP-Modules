#include "ScavTrap.hpp"
#include <iostream>

// Orthodox Canonical Form
//before calling we have to call our parent class constructor
//it will set all values to what we have in the parent class
ScavTrap::ScavTrap() : ClapTrap() {
    std::cout << "ScavTrap default constructor called" << std::endl;
    //here we change the values in the inherited class to what we want
    this->_hitPoints = 100;
    this->_energyPoints = 50;
    this->_attackDamage = 20;
}

//since we call our parent class constructor with its copy constructor and
//we gave it the other object, it will copy the other object's values to the new object
ScavTrap::ScavTrap(const ScavTrap &other) : ClapTrap(other) {
    std::cout << "ScavTrap copy constructor called" << std::endl;
}


ScavTrap &ScavTrap::operator=(const ScavTrap &other) {
    if (this != &other) {
        //instead setting the values to each attribute, we just call the parent class assignment operator
        ClapTrap::operator=(other);
    }
    std::cout << "ScavTrap assignment operator called" << std::endl;
    return *this;
}

//destructor
ScavTrap::~ScavTrap() {
    std::cout << "ScavTrap destructor called" << std::endl;
}

// Constructor with name
//we call the parent class constructor with the name first
ScavTrap::ScavTrap(std::string name) : ClapTrap(name) {
    std::cout << "ScavTrap constructor with name called" << std::endl;
    //here we change the values in the inherited class to what we want
    this->_hitPoints = 100;
    this->_energyPoints = 50;
    this->_attackDamage = 20;
}

// Special ability
void ScavTrap::guardGate() {
    std::cout << "ScavTrap " << this->_name << " is now in Gate keeper mode!" << std::endl;
} 