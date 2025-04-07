#include "ScavTrap.hpp"
#include <iostream>

int main() {
    std::cout << "\n=== Testing ScavTrap Construction ===" << std::endl;
    ScavTrap scav1("Scavvy");
    ScavTrap scav2;
    
    std::cout << "\n=== Testing ScavTrap Copy ===" << std::endl;
    ScavTrap scav3(scav1);
    
    std::cout << "\n=== Testing ScavTrap Assignment ===" << std::endl;
    scav2 = scav1;
    
    std::cout << "\n=== Testing ScavTrap Functions ===" << std::endl;
    scav1.attack("target");
    scav1.takeDamage(30);
    scav1.beRepaired(20);
    scav1.guardGate();
    
    std::cout << "\n=== Testing ScavTrap Info ===" << std::endl;
    scav1.displayInfo();
    scav2.displayInfo();
    scav3.displayInfo();
    
    std::cout << "\n=== Testing ScavTrap Destruction ===" << std::endl;
    return 0;
} 