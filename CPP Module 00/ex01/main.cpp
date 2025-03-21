#include "PhoneBook.hpp"

#include <iostream>


enum Command {
    ADD,
    EXIT,
    SEARCH,
    INVALID
};

Command getCommand(std::string input)
{
    if (input == "ADD")
        return ADD;
    else if (input == "EXIT")
        return EXIT;
    else if (input == "SEARCH")
        return SEARCH;
    return INVALID;
}

int main ()
{
    PhoneBook phoneBook;
    std::string input;

    while (true)
    {
        std::cout << "press ADD, EXIT or SEARCH" << "\n";
        std::getline(std::cin, input);

        switch(getCommand(input))
        {
            case ADD:
            {
                Contact newContact;
                std::string firstName;

                std::cout << "Enter First Name: ";
                std::getline(std::cin, firstName);
                if(!firstName.empty())
                {
                    newContact.setFirstName(firstName);
                    phoneBook.saveContact(newContact);
                }
                break;
            }
            case EXIT:
                return 0;
            case SEARCH:
                return 0;
            default:
                std::cout << "Invalid command!" << std::endl;
                break;
        }
    }
    return (0);
}