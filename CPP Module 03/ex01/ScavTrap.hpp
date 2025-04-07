#ifndef SCAVTRAP_HPP
#define SCAVTRAP_HPP

#include "ClapTrap.hpp"

class ScavTrap : public ClapTrap {
    public:
        // Orthodox Canonical Form
        ScavTrap();
        ScavTrap(const ScavTrap &other);
        ScavTrap &operator=(const ScavTrap &other);
        ~ScavTrap();

        // Constructor with name
        ScavTrap(std::string name);

        // Special ability
        void guardGate();
};

#endif 