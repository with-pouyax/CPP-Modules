#include "FragTrap.hpp"
#include <iostream>

// Orthodox Canonical Form
FragTrap::FragTrap() : ClapTrap() {
    std::cout << "FragTrap default constructor called" << std::endl;
    this->_hitPoints = 100;
    this->_energyPoints = 100;
    this->_attackDamage = 30;
}

FragTrap::FragTrap(const FragTrap &other) : ClapTrap(other) {
    std::cout << "FragTrap copy constructor called" << std::endl;
}

FragTrap &FragTrap::operator=(const FragTrap &other) {
    if (this != &other) {
        ClapTrap::operator=(other);
    }
    std::cout << "FragTrap assignment operator called" << std::endl;
    return *this;
}

FragTrap::~FragTrap() {
    std::cout << "FragTrap destructor called" << std::endl;
}

// Constructor with name
FragTrap::FragTrap(std::string name) : ClapTrap(name) {
    std::cout << "FragTrap constructor with name called" << std::endl;
    this->_hitPoints = 100;
    this->_energyPoints = 100;
    this->_attackDamage = 30;
}

// Override attack function
void FragTrap::attack(const std::string& target) {
    if (this->_hitPoints > 0 && this->_energyPoints > 0) {
        std::cout << "FragTrap " << this->_name << " attacks " << target 
                  << ", causing " << this->_attackDamage << " points of damage!" << std::endl;
        this->_energyPoints--;
    } else {
        if (this->_hitPoints <= 0)
            std::cout << "FragTrap " << this->_name << " is dead and cannot attack!" << std::endl;
        else if (this->_energyPoints <= 0)
            std::cout << "FragTrap " << this->_name << " has no energy to attack!" << std::endl;
    }
}

// Special ability
void FragTrap::highFivesGuys(void) {
    std::cout << "FragTrap " << this->_name << " requests a positive high-five! ✋" << std::endl;
} 