#include "PhoneBook.hpp"
#include <iostream>
#include <string>

enum Command {
    ADD,
    SEARCH,
    EXIT,
    INVALID
};

Command getCommand(const std::string& input)
{
    if (input == "ADD")
        return ADD;
    if (input == "SEARCH")
        return SEARCH;
    if (input == "EXIT")
        return EXIT;
    return INVALID;
}

int main()
{
    PhoneBook phoneBook;
    std::string input;

    while (true)
    {
        std::cout << "Enter command (ADD, SEARCH, EXIT): ";
        std::getline(std::cin, input);
        
        switch (getCommand(input))
        {
            case ADD:
            {
                Contact newContact;
                std::string firstName;
                
                std::cout << "Enter first name: ";
                std::getline(std::cin, firstName);
                if (!firstName.empty())
                {
                    newContact.setFirstName(firstName);
                    phoneBook.addContact(newContact);
                    std::cout << "Contact added successfully!" << std::endl;
                }
                else
                    std::cout << "First name cannot be empty!" << std::endl;
                break;
            }
            case SEARCH:
                std::cout << "Search functionality coming soon!" << std::endl;
                break;
            case EXIT:
                return 0;
            case INVALID:
                std::cout << "Invalid command!" << std::endl;
                break;
        }
    }
    return 0;
}