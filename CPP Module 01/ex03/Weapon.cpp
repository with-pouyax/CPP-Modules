#include "Weapon.hpp"

//constructor
Weapon::Weapon(const std::string& type) {
    if (type.empty())
        this->_type = "Unknown type of weapon";
    else
        this->_type = type;
}

//destructor
Weapon::~Weapon() {
}

//getter
// the return type is a reference because _type value is a reference
const std::string& Weapon::getType() const {
    return this->_type;
}

//setter
void Weapon::setType(const std::string& type) {
    this->_type = type;
} 