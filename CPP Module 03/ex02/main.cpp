#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"
#include <iostream>

void printSeparator(const std::string& message) {
    std::cout << "\n╔════════════════════════════════════════════════════════════════" << std::endl;
    std::cout << "║                     " << message << "                     " << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════════════" << std::endl;
}

int main() {
    
    
    //total test

    printSeparator("Testing all classes");
    {
        ClapTrap clap1("Clapster");
        ScavTrap scav1("Scavster");
        FragTrap frag1("Fragster");

        clap1.attack("enemy");
        scav1.attack("enemy");
        frag1.attack("enemy");

        clap1.displayInfo();
        scav1.displayInfo();
        frag1.displayInfo();
    }

    // Test FragTrap
    printSeparator("Testing FragTrap Construction");
    {
        FragTrap frag1("Fragster");
        FragTrap frag2;

        frag1.displayInfo();
        frag2.displayInfo();
    }
    
    printSeparator("Testing FragTrap Copy");
    {
        FragTrap frag1("Fragster");
        FragTrap frag2(frag1);

        frag1.displayInfo();
        frag2.displayInfo();
    }
    
    printSeparator("Testing FragTrap Assignment");
    {
        FragTrap frag1("Fragster");
        FragTrap frag2;
        frag2 = frag1;

        frag1.displayInfo();
        frag2.displayInfo();
    }
    
    printSeparator("Testing FragTrap Functions");
    {
        FragTrap frag1("Fragster");
        frag1.displayInfo();
        frag1.attack("target");
        frag1.takeDamage(40);
        frag1.beRepaired(25);
        frag1.highFivesGuys();
        frag1.displayInfo();
    }
    
    
    
    printSeparator("Testing Destruction Chain");
    return 0;
} 