#include "Contact.hpp"

Contact::Contact() {};

Contact::~Contact() {};

//setter
void Contact::setContact(
    const std::string& firstName,
    const std::string& lastName,
    const std::string& nickName,
    const std::string& phoneNumber,
    const std::string& darkestSecret)
{
    this->_firstName = firstName;
    this->_lastName = lastName;
    this->_nickName = nickName;
    this->_phoneNumber = phoneNumber;
    this->_darkestSecret = darkestSecret;
}