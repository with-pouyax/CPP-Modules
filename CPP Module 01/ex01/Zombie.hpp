#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <string>
#include <iostream>

class Zombie {
private:
    std::string _name;

public:
    // Constructors and destructor
    Zombie(); // Default constructor for the horde
    ~Zombie();
    Zombie(std::string name);

    // Member functions
    void announce(void);
    void setName(std::string name);
};

// Function prototypes
Zombie* zombieHorde(int N, std::string name);

#endif 