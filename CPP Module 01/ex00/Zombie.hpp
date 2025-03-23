#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <string>
#include <iostream>

class Zombie {
private:
    std::string _name;

public:
    // Constructor and destructor
    Zombie(std::string name); // our constructor receive a string parameter
    ~Zombie();

    // Member functions
    void announce(void);
};

// Function prototypes
Zombie* newZombie(std::string name);
void randomChump(std::string name);

#endif 