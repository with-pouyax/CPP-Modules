#include "ClapTrap.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    if (argc != 1)
    {
        std::cout << "Usage: " << argv[0] << std::endl;
        return 1;
    }

    std::cout << "\n===============================================" << std::endl;
    std::cout << "          TESTING CLAPTRAP CONSTRUCTORS         " << std::endl;
    std::cout << "===============================================" << std::endl;
    
    // Testing all types of constructors
    ClapTrap default_trap;     // default constructor
    ClapTrap warrior("Warrior");     // constructor with name
    ClapTrap warrior_copy(warrior);  // copy constructor

    std::cout << "\n===============================================" << std::endl;
    std::cout << "            DISPLAYING INITIAL STATS            " << std::endl;
    std::cout << "===============================================" << std::endl;
    
    // Show initial values for all ClapTraps
    std::cout << "\n>>> Default ClapTrap stats:" << std::endl;
    default_trap.displayInfo();
    std::cout << "\n>>> Warrior ClapTrap stats:" << std::endl;
    warrior.displayInfo();
    std::cout << "\n>>> Copied Warrior stats:" << std::endl;
    warrior_copy.displayInfo();

    std::cout << "\n===============================================" << std::endl;
    std::cout << "         TESTING ATTACK AND TAKE DAMAGE         " << std::endl;
    std::cout << "===============================================" << std::endl;
    
    // Testing combat functionality
    warrior.attack("Enemy");
    warrior.takeDamage(5);
    std::cout << "\n>>> Warrior stats after combat:" << std::endl;
    warrior.displayInfo();

    std::cout << "\n===============================================" << std::endl;
    std::cout << "              TESTING REPAIR ABILITY            " << std::endl;
    std::cout << "===============================================" << std::endl;
    
    // Testing healing mechanics
    warrior.beRepaired(3);
    std::cout << "\n>>> Warrior stats after repair:" << std::endl;
    warrior.displayInfo();

    std::cout << "\n===============================================" << std::endl;
    std::cout << "         TESTING ENERGY POINTS DEPLETION        " << std::endl;
    std::cout << "===============================================" << std::endl;
    
    // Testing energy consumption
    std::cout << ">>> Performing multiple attacks until energy depletes..." << std::endl;
    for (int i = 0; i < 9; ++i)  // Already used 1 energy point
    {
        warrior.attack("Enemy");
    }
    std::cout << "\n>>> Attempting actions with no energy:" << std::endl;
    warrior.attack("Enemy");    // Should fail - no energy
    warrior.beRepaired(1);      // Should fail - no energy
    std::cout << "\n>>> Warrior stats after energy depletion:" << std::endl;
    warrior.displayInfo();

    std::cout << "\n===============================================" << std::endl;
    std::cout << "               TESTING DEATH STATE              " << std::endl;
    std::cout << "===============================================" << std::endl;
    
    // Testing death mechanics
    std::cout << ">>> Dealing fatal damage..." << std::endl;
    warrior.takeDamage(10);     // This should kill the ClapTrap
    std::cout << "\n>>> Attempting actions while dead:" << std::endl;
    warrior.attack("Enemy");    // Should fail - dead
    warrior.beRepaired(5);      // Should fail - dead
    std::cout << "\n>>> Warrior stats after death:" << std::endl;
    warrior.displayInfo();

    std::cout << "\n===============================================" << std::endl;
    std::cout << "                  END OF TESTS                  " << std::endl;
    std::cout << "===============================================" << std::endl;

    return 0;
}