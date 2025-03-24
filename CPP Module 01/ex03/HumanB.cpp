    #include "HumanB.hpp"
    #include <iostream>

    HumanB::HumanB(const std::string& name) : _name(name), _weapon(NULL) {
}

void HumanB::setWeapon(Weapon& weapon) {
    this->_weapon = &weapon;
}

//destructor
HumanB::~HumanB() {
}

void HumanB::attack() const {
    if (this->_weapon)
        std::cout << this->_name << " attacks with their " << this->_weapon->getType() << std::endl;
    else
        std::cout << this->_name << " has no weapon to attack with" << std::endl;
} 