#include "Contact.hpp"

Contact::Contact() : _firstName("") {};
Contact::~Contact() {};

//setter
void Contact::setFirstName(const std::string& firstName)
{
    this->_firstName = firstName;
}