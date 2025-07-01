#include "RPN.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Error: Invalid number of arguments" << std::endl;
        std::cerr << "Usage: " << argv[0] << " \"<RPN expression>\"" << std::endl;
        return 1;
    }
    
    std::string expression = argv[1];
    
    try {
        RPN calculator;
        int result = calculator.evaluate(expression);
        std::cout << result << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
} 