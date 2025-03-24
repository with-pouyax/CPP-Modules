#include "Weapon.hpp"
#include "HumanA.hpp"
#include "HumanB.hpp"
#include <iostream>
int main(int argc, char **argv)
{
    (void)argv;
    if (argc != 1)
    {
        std::cout << "Error: wrong number of arguments" << std::endl;
        return 1;
    }
    {
        Weapon club = Weapon("crude spiked club"); // we create a Weapon object called club with the type "crude spiked club"

        HumanA bob("Bob", club); // we create a HumanA object called bob a with the name "Bob" and the weapon club
        bob.attack(); // bob attacks 
        club.setType("some other type of club"); // we change the type of our club weapon to "some other type of club"
        bob.attack(); // bob attacks again
    }
    std::cout << "--------------------------------" << std::endl;
    {
        Weapon club = Weapon("crude spiked club"); // we create a Weapon object called club with the type "crude spiked club"
        
        HumanB jim("Jim"); // we create a HumanB object called jim with the name "Jim"
        jim.setWeapon(club); // we set the weapon of jim to club
        jim.attack(); // jim attacks
        club.setType("some other type of club"); // we change the type of our club weapon to "some other type of club"
        jim.attack(); // jim attacks again
    }

     std::cout << "--------------------------------" << std::endl;
    {
        Weapon club = Weapon("crude spiked club"); // we create a Weapon object called club with the type "crude spiked club"
        
        HumanB jim("Jim"); // we create a HumanB object called jim with the name "Jim"
        jim.attack(); // jim attacks
        jim.setWeapon(club); // we set the weapon of jim to club
        club.setType("some other type of club"); // we change the type of our club weapon to "some other type of club"
        jim.attack(); // jim attacks again
    }
    return 0;
} 