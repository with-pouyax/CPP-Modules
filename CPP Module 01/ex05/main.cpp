#include "Harl.hpp"
#include <iostream>

int main(void) {
    Harl harl;
    // Test all levels
    //test DEBUG
    std::cout << "Testing DEBUG level:" << std::endl;
    harl.complain("DEBUG");
    std::cout << std::endl;
    //test INFO
    std::cout << "Testing INFO level:" << std::endl;
    harl.complain("INFO");
    std::cout << std::endl;
    //test WARNING
    std::cout << "Testing WARNING level:" << std::endl;
    harl.complain("WARNING");
    std::cout << std::endl;
    //test ERROR
    std::cout << "Testing ERROR level:" << std::endl;
    harl.complain("ERROR");
    std::cout << std::endl;
    //test invalid
    std::cout << "Testing invalid level:" << std::endl;
    harl.complain("INVALID");
    
    return 0;
} 