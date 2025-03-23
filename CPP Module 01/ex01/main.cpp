#include "Zombie.hpp"

int main(int ac, char **av) {

    if (ac != 1)
    {
        std::cerr << "Usage: " << av[0] << " <number of zombies>" << std::endl;
        return 1;
    }

    // Test parameters
    int numZombies = 5;
    std::string zombieName = "Horde Zombie";
    
    // Create a horde of zombies
    std::cout << "Creating a horde of " << numZombies << " zombies named '" << zombieName << "'..." << std::endl;
    Zombie* horde = zombieHorde(numZombies, zombieName);
    if (!horde) {
        std::cerr << "Failed to create zombie horde!" << std::endl;
        return 1;
    }
    
    // Test the announce function for each zombie
    std::cout << "\nTesting announce() for each zombie:" << std::endl;
    for (int i = 0; i < numZombies; i++) {
        std::cout << "Zombie #" << i + 1 << " announces: ";
        horde[i].announce();
    }
    
    // Clean up the horde properly
    std::cout << "\nDestroying the horde..." << std::endl;
    delete[] horde;
    
    // Additional test with a different name
    std::cout << "\n\n\nCreating another horde with a different name..." << std::endl;
    int numZombies2 = 3;
    std::string zombieName2 = "Brain Eater";
    Zombie* horde2 = zombieHorde(numZombies2, zombieName2);
    if (!horde2) {
        std::cerr << "Failed to create second zombie horde!" << std::endl;
        return 1;
    }
    
    // Test announce for the second horde
    for (int i = 0; i < numZombies2; i++) {
        horde2[i].announce();
    }

    std::cout << "\n\n\nDestroying the second horde..." << std::endl;
    
    // Clean up the second horde
    delete[] horde2;
    
    return 0;
} 