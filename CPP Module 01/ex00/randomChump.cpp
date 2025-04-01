#include "Zombie.hpp"

void randomChump(std::string name) {
    if (name.empty()) {
        name = "Unnamed Zombie";
    }
    Zombie zombie(name);
    zombie.announce();
} 
