#include "PhoneBook.hpp"

PhoneBook::PhoneBook() : _index(0) {};
PhoneBook::~PhoneBook() {};

//setter
void PhoneBook::saveContact(const Contact& newContact)
{
    _contact[_index] = newContact;
    _index++;

}