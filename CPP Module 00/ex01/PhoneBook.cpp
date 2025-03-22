#include "PhoneBook.hpp"
#include <iostream>
#include <iomanip>

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

//display
void PhoneBook::displayAllContacts() const
{
    // Print header row with divider
    std::cout << "┌──────────┬──────────┬──────────┬──────────┐" << std::endl;
    std::cout << "|" << std::setw(10) << "Index" << "|"; 
    std::cout << std::setw(10) << "First Name" << "|";
    std::cout << std::setw(10) << "Last Name" << "|";
    std::cout << std::setw(10) << "Nickname" << "|" << std::endl;
    std::cout << "├──────────┼──────────┼──────────┼──────────┤" << std::endl;

    // Check if phonebook is empty
    bool isEmpty = true;
    for (int i = 0; i < 8; i++)
    {
        if (!this->_contact[i].isEmpty())
        {
            isEmpty = false;
            this->_contact[i].displaySummary(i);
        }
    }
    
    // Bottom border
    std::cout << "└──────────┴──────────┴──────────┴──────────┘" << std::endl;
    
    // Display message if empty
    if (isEmpty)
    {
        std::cout << "\n📭 The phonebook is empty. Add contacts first!" << std::endl;
    }
}

void PhoneBook::displayContact(int index) const
{
    if (index >= 0 && index < 8 && !this->_contact[index].isEmpty())
    {
        this->_contact[index].displayDetails();
    }
    else
    {
        std::cout << "⚠️  Invalid index or empty contact!" << std::endl;
        std::cout << "   Please select an index from the displayed contacts." << std::endl;
    }
}