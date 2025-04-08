#include "ScavTrap.hpp"
#include <iostream>

void printSeparator(const std::string& message) {
    std::cout << "\n╔════════════════════════════════════════════════════════════════" << std::endl;
    std::cout << "║                     " << message << "                     " << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════════════" << std::endl;
}

int main() {
    printSeparator("Testing ScavTrap Construction");
    {
        ScavTrap scav1("Scavvy"); //make a ScavTrap object with the name
        ScavTrap scav2; //make a ScavTrap object with default name
        
        //display the info of the two objects
        scav1.displayInfo();
        scav2.displayInfo();
    }
    
    printSeparator("Testing ScavTrap Copy");
    {
        ScavTrap scav1("Scavvy");
        ScavTrap scav2(scav1);

        //display the info of the two objects
        scav1.displayInfo();
        scav2.displayInfo();
    }
    
    printSeparator("Testing ScavTrap Assignment");
    {
        ScavTrap scav1("Scavvy"); //make a ScavTrap object with the name
        ScavTrap scav2; //make a ScavTrap object with default name
        scav2 = scav1; //assign the first object to the second object

        //display the info of the two objects
        scav1.displayInfo();
        scav2.displayInfo();
    }
    
    printSeparator("Testing ScavTrap Functions");
    {
        ScavTrap scav1("Scavvy");
        scav1.attack("target");
        scav1.takeDamage(30);
        scav1.beRepaired(20);
        scav1.guardGate();

        //display the info of the object
        scav1.displayInfo();
    }
    
    printSeparator("Testing ScavTrap Info");
    {
        ScavTrap scav1("Scavvy");
        ScavTrap scav2(scav1);
        ScavTrap scav3;
        scav3 = scav1;
        
        std::cout << "\nScavTrap 1 Info:" << std::endl;
        scav1.displayInfo();
        std::cout << "\nScavTrap 2 Info:" << std::endl;
        scav2.displayInfo();
        std::cout << "\nScavTrap 3 Info:" << std::endl;
        scav3.displayInfo();
    }
    
    printSeparator("Testing ScavTrap Destruction");
    return 0;
} 