#include "PhoneBook.hpp"

#include <iostream>
#include <cctype>
#include <sstream>
#include <iomanip>

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

// Function to display a decorated welcome message
void displayWelcome()
{
    std::cout << "\n";
    std::cout << "╔══════════════════════════════════════════╗" << std::endl;
    std::cout << "║     📞  AWESOME PHONEBOOK v1.0  📞       ║" << std::endl;
    std::cout << "╚══════════════════════════════════════════╝" << std::endl;
    std::cout << "\n";
}

// Function to display the main menu
void displayMenu()
{
    std::cout << "\n";
    std::cout << "📋 MAIN MENU - Please select an option:" << std::endl;
    std::cout << "   ┌────────────────────────────────┐" << std::endl;
    std::cout << "   │  ADD    - Add a new contact    │" << std::endl;
    std::cout << "   │  SEARCH - Find a contact       │" << std::endl;
    std::cout << "   │  EXIT   - Quit the program     │" << std::endl;
    std::cout << "   └────────────────────────────────┘" << std::endl;
    std::cout << "➤ Enter your choice: ";
}

// Function to get contact information from user
Contact getContactFromUser()
{
    // we initialize the variables to store the contact information
    Contact newContact;
    std::string firstName;
    std::string lastName;
    std::string nickName;
    std::string phoneNumber;
    std::string darkestSecret;

    std::cout << "\n";
    std::cout << "╔══════════════════════════════════════════╗" << std::endl;
    std::cout << "║         ✨ ADDING NEW CONTACT ✨         ║" << std::endl;
    std::cout << "╚══════════════════════════════════════════╝" << std::endl;
    
    
    do
    {
        std::cout << "📝 Enter First Name: ";
        std::getline(std::cin, firstName);
        if (firstName.empty())
            std::cout << "⚠️  First name cannot be empty! Please try again." << std::endl;
    } while (firstName.empty());
    
    do
    {
        std::cout << "📝 Enter Last Name: ";
        std::getline(std::cin, lastName);
        if (lastName.empty())
            std::cout << "⚠️  Last name cannot be empty! Please try again." << std::endl;
    } while (lastName.empty());
    
    do
    {
        std::cout << "📝 Enter Nickname: ";
        std::getline(std::cin, nickName);
        if (nickName.empty())
            std::cout << "⚠️  Nickname cannot be empty! Please try again." << std::endl;
    } while (nickName.empty());
    
    do
    {
        std::cout << "📝 Enter Phone Number: ";
        std::getline(std::cin, phoneNumber);
        
        if (phoneNumber.empty())
            std::cout << "⚠️  Phone number cannot be empty! Please try again." << std::endl;
        else if (!isOnlyDigits(phoneNumber))
        {
            std::cout << "⚠️  Phone number must contain only digits! Please try again." << std::endl;
            phoneNumber = ""; // Reset to force re-entry
        }
    } while (phoneNumber.empty());
    
    do
    {
        std::cout << "📝 Enter Darkest Secret: ";
        std::getline(std::cin, darkestSecret);
        if (darkestSecret.empty())
            std::cout << "⚠️  Darkest secret cannot be empty! Please try again." << std::endl;
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
        std::cout << "Usage: " << argv[0] << std::endl;
        return 1;
    }

    displayWelcome();

    while (true)
    {
        displayMenu();
        if (!std::getline(std::cin, input)) // Check if input failed (EOF or error)
        {
            std::cout << "\n👋 EOF detected. Thank you for using Awesome PhoneBook! Goodbye!" << std::endl;
            return 0;
        }
        switch(getCommand(input))
        {
            case ADD:
            {
                Contact newContact = getContactFromUser(); // we get the contact from the user
                phoneBook.saveContact(newContact);         // we save the contact to the phonebook
                std::cout << "\n✅ Contact saved successfully!" << std::endl;
                break;
            }
            case SEARCH:
            {
                std::cout << "\n";
                std::cout << "🔍 SEARCH CONTACTS" << std::endl;
                std::cout << "----------------" << std::endl;
                
                phoneBook.displayAllContacts(); // we display all the contacts
                
                std::string indexStr; // this is the index of the contact that the user wants to view
                
                // we recieve the index of the contact that the user wants to view
                do
                {
                    std::cout << "\n📝 Enter index to view details (0-7): ";
                    std::getline(std::cin, indexStr); 
                    
                    if (!isOnlyDigits(indexStr) || indexStr.empty())
                        std::cout << "⚠️  Please enter a valid digit!" << std::endl;
                    else if (indexStr.length() > 1 || indexStr[0] > '7')
                        std::cout << "⚠️  Index must be between 0 and 7!" << std::endl;
                } while (!isOnlyDigits(indexStr) || indexStr.empty() || indexStr.length() > 1 || indexStr[0] > '7');
                
                std::stringstream ss(indexStr);  // we create a stringstream object to convert the string to an integer
                int index;
                ss >> index; // we convert the string to an integer
                
                std::cout << "\n";
                std::cout << "📇 CONTACT DETAILS" << std::endl;
                std::cout << "----------------" << std::endl;
                phoneBook.displayContact(index);
                break;
            }
            case EXIT:
                std::cout << "\n👋 Thank you for using Awesome PhoneBook! Goodbye!" << std::endl;
                return 0;
            default:
                std::cout << "\n⚠️  Invalid command! Please enter ADD, SEARCH, or EXIT." << std::endl;
                break;
        }
    }
    return (0);
}
