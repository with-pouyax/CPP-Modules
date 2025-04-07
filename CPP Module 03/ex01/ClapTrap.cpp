#include "ClapTrap.hpp"
#include <iostream>
#include <climits>

//-------------------Orthodox Canonical Form--------------------------------

//default constructor
ClapTrap::ClapTrap() 
    : _name("Default"),
    _hitPoints(10),
    _energyPoints(10),
    _attackDamage(0) 
{
    std::cout << "ClapTrap default constructor called" << std::endl;
}

//copy constructor
ClapTrap::ClapTrap(const ClapTrap &other) 
    : _name(other._name),
    _hitPoints(other._hitPoints),
    _energyPoints(other._energyPoints),
    _attackDamage(other._attackDamage) 
{
    std::cout << "ClapTrap copy constructor called" << std::endl;
}

//copy assignment operator
ClapTrap &ClapTrap::operator=(const ClapTrap &other) 
{
    if (this != &other) {
        this->_name = other._name;
        this->_hitPoints = other._hitPoints;
        this->_energyPoints = other._energyPoints;
        this->_attackDamage = other._attackDamage;
    }
    return *this;
}

//destructor
ClapTrap::~ClapTrap()
{
    std::cout << "ClapTrap destructor called" << std::endl;
}

//--------------------------------------------------------

//constructor with name
ClapTrap::ClapTrap(std::string name)
    : _name(name),
    _hitPoints(10),
    _energyPoints(10),
    _attackDamage(0)
{
    std::cout << "ClapTrap constructor with name called" << std::endl;
    if (name.empty())
    {
        this->_name = "Default";
    }
}

//--------------------------------------------------------

//public member functions

void ClapTrap::attack(const std::string& target)
{
    if (this->_hitPoints > 0 && this->_energyPoints > 0)
    {
        std::cout << "ClapTrap " << this->_name << " attacks " << target << ", causing " << this->_attackDamage << " points of damage!" << std::endl;
        this->_energyPoints--;
    }
    else
    {
        if (this->_hitPoints <= 0)
            std::cout << "ClapTrap " << this->_name << " is dead and cannot attack!" << std::endl;
        else if (this->_energyPoints <= 0)
            std::cout << "ClapTrap " << this->_name << " has no energy to attack!" << std::endl;
    }
}

void ClapTrap::takeDamage(unsigned int amount)
{
    if (this->_hitPoints > 0)
    {
        if (amount > static_cast<unsigned int>(this->_hitPoints))
            this->_hitPoints = 0;
        else
            this->_hitPoints -= amount;
        std::cout << "ClapTrap " << this->_name << " takes " << amount << " points of damage!" << std::endl;
    }
    else
    {
        std::cout << "ClapTrap " << this->_name << " is already dead!" << std::endl;
    }
}

void ClapTrap::beRepaired(unsigned int amount)
{
    if (this->_hitPoints > 0 && this->_energyPoints > 0)
    {
        if (static_cast<unsigned int>(INT_MAX - this->_hitPoints) < amount) //if amount is too big, set to max
            this->_hitPoints = INT_MAX;
        else
            this->_hitPoints += amount;
        this->_energyPoints--;
        std::cout << "ClapTrap " << this->_name << " is repaired by " << amount << " points!" << std::endl;
    }
    else
    {
        if (this->_hitPoints <= 0)
            std::cout << "ClapTrap " << this->_name << " is dead and cannot be repaired!" << std::endl;
        else if (this->_energyPoints <= 0)
            std::cout << "ClapTrap " << this->_name << " has no energy to repair!" << std::endl;
    }
}

//helper functions
void ClapTrap::displayInfo() const
{
    std::cout << "------" << this->_name << " info ------" << std::endl;
    std::cout << "Name: " << this->_name << std::endl;
    std::cout << "Hit points: " << this->_hitPoints << std::endl;
    std::cout << "Energy points: " << this->_energyPoints << std::endl;
    std::cout << "Attack damage: " << this->_attackDamage << std::endl;
    std::cout << "--------------------------------" << std::endl;
}

//getters
std::string ClapTrap::getName() const
{
    return this->_name;
} 