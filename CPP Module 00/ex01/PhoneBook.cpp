#include "PhoneBook.hpp"

PhoneBook::PhoneBook() : _index(0) {};
PhoneBook::~PhoneBook() {};

//setter
void PhoneBook::saveContact(const Contact& newContact)
{
    if (this->_index < 8)
    {
        this->_contact[_index] = newContact;
        this->_index++;
    }
    else
    {
        this->_index = 0;
        this->_contact[_index] = newContact;
        this->_index++;
    }

}