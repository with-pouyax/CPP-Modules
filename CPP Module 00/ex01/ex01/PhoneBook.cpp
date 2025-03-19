#include "PhoneBook.hpp"

// Constructor and destructor
PhoneBook::PhoneBook() : index(0) {}
PhoneBook::~PhoneBook() {}

// setters methods
void PhoneBook::addContact(const Contact& contact)
{
    if (index < 8)
    {
        contacts[index] = contact;
        index++;
    }
    else
    {
        index = 0;
        contacts[index] = contact;
        index++;
    }
}