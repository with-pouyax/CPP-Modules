#include "PhoneBook.hpp"
#include <iostream>

enum command {
    ADD,
    EXIT,
    SEARCH,
    INVALID
};

command getCommand(const std::string& input)
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
    PhoneBook phonebook;
    std::string input;

    while (true)
    {
        std::cout << "ENTER ADD or SEARCH or EXIT" << "\n";
        getline(std::cin, input);
        
        switch (getCommand(input))
        {
            case ADD:
            {
                
            }
        }
        
    }
}