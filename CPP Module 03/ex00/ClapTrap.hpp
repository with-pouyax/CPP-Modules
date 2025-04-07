#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

#include <string>

class ClapTrap {
    private:
        std::string _name;
        int _hitPoints;         //health
        int _energyPoints;
        int _attackDamage;
    
    public:
        
        //Orthodox Canonical Form
        //--------------------------------
        ClapTrap();
        ClapTrap(const ClapTrap &other);
        ClapTrap &operator=(const ClapTrap &other);
        ~ClapTrap();
        //--------------------------------

        //constructor with name
        ClapTrap(std::string name);

        //public member functions
        void attack(const std::string& target);  //attack a target
        void takeDamage(unsigned int amount);    //take damage myself
        void beRepaired(unsigned int amount);   //repair myself

        //getters
        void displayInfo() const;
        std::string getName() const;
};

        
        
        
        


#endif
