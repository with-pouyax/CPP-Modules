#include "PhoneBook.hpp"

#include <iostream>
#include <cctype>

// Function to check if a string contains only digits using std::isdigit
bool isOnlyDigits(const std::string& str)
{
    for (size_t i = 0; i < str.length(); i++)
    {
        if (!std::isdigit(str[i]))
            return false;
    }
    return true;
}

// Function to get contact information from user
Contact getContactFromUser()
{
    Contact newContact;
    std::string firstName;
    std::string lastName;
    std::string nickName;
    std::string phoneNumber;
    std::string darkestSecret;

    do
    {
        std::cout << "Enter First Name: ";
        std::getline(std::cin, firstName);
    } while (firstName.empty());
    
    do
    {
        std::cout << "Enter Last Name: ";
        std::getline(std::cin, lastName);
    } while (lastName.empty());
    
    do
    {
        std::cout << "Enter Nick Name: ";
        std::getline(std::cin, nickName);
    } while (nickName.empty());
    
    do
    {
        std::cout << "Enter Phone Number: ";
        std::getline(std::cin, phoneNumber);
        
        if (!phoneNumber.empty() && !isOnlyDigits(phoneNumber))
        {
            std::cout << "Phone number must contain only digits. Try again." << std::endl;
            phoneNumber = ""; // Reset to force re-entry
        }
    } while (phoneNumber.empty());
    
    do
    {
        std::cout << "Enter Darkest Secret: ";
        std::getline(std::cin, darkestSecret);
    } while (darkestSecret.empty());

    newContact.setContact(firstName, lastName, nickName, phoneNumber, darkestSecret);
    return newContact;
}

enum Command {
    ADD,
    EXIT,
    SEARCH,
    INVALID
};

Command getCommand(const std::string& input)
{
    if (input == "ADD")
        return ADD;
    else if (input == "EXIT")
        return EXIT;
    else if (input == "SEARCH")
        return SEARCH;
    return INVALID;
}

int main (int argc, char **argv)
{
    PhoneBook phoneBook;
    std::string input;

    if (argc > 1)
    {
        std::cout << "Usage: " << argv[0] << " [phonebook_file]" << std::endl;
        return 1;
    }

    while (true)
    {
        std::cout << "press ADD, EXIT or SEARCH" << "\n";
        std::getline(std::cin, input);

        switch(getCommand(input))
        {
            case ADD:
            {
                Contact newContact = getContactFromUser();
                phoneBook.saveContact(newContact);
                std::cout << "Contact saved successfully!" << std::endl;
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
