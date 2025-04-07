#include "ClapTrap.hpp"
#include <iostream>
#include <climits>
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
    ClapTrap default_trap;            // default constructor
    ClapTrap warrior("Warrior");      // constructor with name
    ClapTrap warrior_copy(warrior);   // copy constructor

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
    warrior.attack("Enemy");      //warrior attacks enemy
    warrior.takeDamage(5);        //warrior receives 5 damage
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
    for (int i = 0; i < 9; ++i)
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
    std::cout << "               TESTING OVERFLOW                 " << std::endl;
    std::cout << "===============================================" << std::endl;

    // Testing overflow mechanics with unsigned int
    std::cout << ">>> Creating new ClapTrap for overflow test:" << std::endl;
    ClapTrap overflow_trap("OverflowTester");
    overflow_trap.displayInfo();

    std::cout << "\n>>> Attempting repair with maximum unsigned int value:" << std::endl;
    overflow_trap.beRepaired(UINT_MAX);  // Should handle overflow gracefully
    std::cout << "\n>>> Stats after attempting overflow repair:" << std::endl;
    overflow_trap.displayInfo();

    std::cout << "\n>>> Attempting repair with another large value:" << std::endl;
    overflow_trap.beRepaired(UINT_MAX - 5);  // Should handle overflow gracefully
    std::cout << "\n>>> Final stats after second overflow attempt:" << std::endl;
    overflow_trap.displayInfo();

    // Testing with a value that would cause addition overflow
    std::cout << "\n>>> Attempting repair after taking some damage:" << std::endl;
    overflow_trap.takeDamage(5);  // Reduce HP first
    overflow_trap.beRepaired(UINT_MAX);  // Try to repair with UINT_MAX
    std::cout << "\n>>> Final stats after attempting repair with UINT_MAX:" << std::endl;
    overflow_trap.displayInfo();

    std::cout << "\n===============================================" << std::endl;
    std::cout << "                  END OF TESTS                  " << std::endl;
    std::cout << "===============================================" << std::endl;

    return 0;
}