#ifndef HUMANA_HPP
# define HUMANA_HPP

# include <string>
# include "Weapon.hpp"

class HumanA {
private:
    std::string _name;  //name of the human
    Weapon& _weapon;    //reference to the weapon

public:
    HumanA(const std::string& name, Weapon& weapon);
    ~HumanA();
    void attack() const;
};

#endif 