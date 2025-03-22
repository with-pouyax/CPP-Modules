#include "Contact.hpp"
#include <iostream>
#include <iomanip>

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

//helper
std::string Contact::truncateTo10(const std::string& str) const
{
    if (str.length() <= 10)
        return str;
    return str.substr(0, 9) + "."; //substr(0, 9) means from the start of the string to the 9th character and + "." means add a dot to the end of the string
}

bool Contact::isEmpty() const
{
    return this->_firstName.empty();
}

//display methods
void Contact::displaySummary(int index) const
{
    std::cout << "|" << std::setw(10) << index << "|";
    std::cout << std::setw(10) << truncateTo10(this->_firstName) << "|";
    std::cout << std::setw(10) << truncateTo10(this->_lastName) << "|";
    std::cout << std::setw(10) << truncateTo10(this->_nickName) << "|" << std::endl;
}

void Contact::displayDetails() const
{


     std::cout << "┌──────────────────────────────────────────" << std::endl;
    std::cout << "│ 👤 Contact Information                   " << std::endl;
    std::cout << "├──────────────────────────────────────────" << std::endl;
    std::cout << "│ 📋 First Name:     " << this->_firstName << std::endl;
    std::cout << "│ 📋 Last Name:      " << this->_lastName << std::endl;
    std::cout << "│ 📋 Nickname:       " << this->_nickName << std::endl;
    std::cout << "│ 📞 Phone Number:   " << this->_phoneNumber << std::endl;
    std::cout << "│ 🔒 Darkest Secret: " << this->_darkestSecret << std::endl;
    std::cout << "└──────────────────────────────────────────" << std::endl;
}