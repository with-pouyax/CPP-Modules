#include "Zombie.hpp"

Zombie* zombieHorde(int N, std::string name) {
    if (N <= 0)
        return NULL;
    
    Zombie* horde = NULL;
    
    if (name.empty())
        name = "Unnamed Zombie";
    try {
        // Allocate N zombies in a single allocation
        horde = new Zombie[N];
        
        // Initialize each zombie with the given name
        for (int i = 0; i < N; i++) {
            horde[i].setName(name);
        }
    } catch (const std::bad_alloc& error) {
        std::cerr << "Memory allocation failed: " << error.what() << std::endl;
        return NULL;
    }

    return horde;
} 