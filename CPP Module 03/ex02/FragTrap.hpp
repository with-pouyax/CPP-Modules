#ifndef FRAGTRAP_HPP
#define FRAGTRAP_HPP

#include "ClapTrap.hpp"

class FragTrap : public ClapTrap {
    public:
        // Orthodox Canonical Form
        FragTrap();
        FragTrap(const FragTrap &other);
        FragTrap &operator=(const FragTrap &other);
        ~FragTrap();

        // Constructor with name
        FragTrap(std::string name);

        // Override attack function
        void attack(const std::string& target);

        // Special ability
        void highFivesGuys(void);
};

#endif 