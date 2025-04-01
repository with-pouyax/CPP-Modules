#include "Harl.hpp"
#include <iostream>
// constructor
Harl::Harl(void) {
}
// destructor
Harl::~Harl(void) {
}
// debug
void Harl::_debug(void) {
    std::cout << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-specialketchup burger. I really do!" << std::endl;
}

void Harl::_info(void) {
    std::cout << "I cannot believe adding extra bacon costs more money. You didn't put enough bacon in my burger! If you did, I wouldn't be asking for more!" << std::endl;
}

void Harl::_warning(void) {
    std::cout << "I think I deserve to have some extra bacon for free. I've been coming for years, whereas you started working here just last month." << std::endl;
}

void Harl::_error(void) {
    std::cout << "This is unacceptable! I want to speak to the manager now." << std::endl;
}

void Harl::complain(std::string level) {
    /* complaints[4] → This means:

“complaints is an array of 4 things”

*complaints[i] → This means:

“Each element is a pointer to something”

Harl::*complaints[i] → This now means:

“Each element is a pointer to a member of class Harl”

void (Harl::*)(void) → This whole thing means:

“A pointer to a member function of Harl, that takes no arguments and returns void” */
    void (Harl::*complaints[4])(void) = {
        &Harl::_debug,
        &Harl::_info,
        &Harl::_warning,
        &Harl::_error
    };
    // array of strings containing the levels
    std::string levels[4] = {
        "DEBUG",
        "INFO",
        "WARNING",
        "ERROR"
    };
    // loop through the array of strings and call the appropriate function
    for (int i = 0; i < 4; i++) {
        if (level == levels[i]) {
            (this->*complaints[i])();
            return;
        }
    }
    std::cout << "Probably complaining about insignificant problems" << std::endl;
} 