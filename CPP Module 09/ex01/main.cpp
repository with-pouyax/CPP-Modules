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
        RPN calculator;                                    // Create a RPN calculator object
        int result = calculator.evaluate(expression);      // pass the expression to the evaluate method of the RPN calculator and store the result in the result variable
        std::cout << result << std::endl;                  // print the result
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
} 