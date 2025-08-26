#include "RPN.hpp"
#include <sstream>
#include <stdexcept>
#include <limits>

RPN::RPN() {}

RPN::~RPN() {}

RPN::RPN(const RPN& other) : _stack(other._stack) {}

RPN& RPN::operator=(const RPN& other) {
    if (this != &other) {
        _stack = other._stack;
    }
    return *this;
}

bool RPN::isOperator(const std::string& token) {
    return token == "+" || token == "-" || token == "*" || token == "/";
}

bool RPN::isValidToken(const std::string& token) {
    if (token.length() == 1) {
        if (token[0] >= '0' && token[0] <= '9') {
            return true;
        }
        if (isOperator(token)) {
            return true;
        }
    }
    return false;
}

int RPN::performOperation(int a, int b, const std::string& op) {
    //=========Debugging=========
#ifdef DEBUG
    std::cout << "inside performOperation" << " " << a << " " << op << " " << b << std::endl;
#endif
    //===========================
    if (op == "+") {
        // Check for overflow in addition
        if ((b > 0 && a > std::numeric_limits<int>::max() - b) || 
            (b < 0 && a < std::numeric_limits<int>::min() - b)) {
            throw std::runtime_error("Integer overflow");
        }
        return a + b;
    } else if (op == "-") {
        // Check for overflow in subtraction
        if ((b < 0 && a > std::numeric_limits<int>::max() + b) || 
            (b > 0 && a < std::numeric_limits<int>::min() + b)) {
            throw std::runtime_error("Integer overflow");
        }
        return a - b;
    } else if (op == "*") {
        // Check for overflow in multiplication
        if (a != 0 && b != 0) {
            if (a > 0 && b > 0 && a > std::numeric_limits<int>::max() / b) {
                throw std::runtime_error("Integer overflow");
            }
            if (a < 0 && b < 0 && a < std::numeric_limits<int>::max() / b) {
                throw std::runtime_error("Integer overflow");
            }
            if (a > 0 && b < 0 && b < std::numeric_limits<int>::min() / a) {
                throw std::runtime_error("Integer overflow");
            }
            if (a < 0 && b > 0 && a < std::numeric_limits<int>::min() / b) {
                throw std::runtime_error("Integer overflow");
            }
        }
        return a * b;
    } else if (op == "/") {
        if (b == 0) {
            throw std::runtime_error("Division by zero");
        }
        return a / b;
    }
    throw std::runtime_error("Invalid operator");
}

int RPN::evaluate(const std::string& expression) {
    
    //=========Debugging=========
#ifdef DEBUG
    std::cout << "inside evaluate" << "expression: " << expression << std::endl;
#endif
    //===========================
    
    std::istringstream iss(expression);                  // we make object of type istringstream called iss
                                                              // it store the expression stream of characters
                                                              // th same thing happens in cout, but here we still did not used the stream and it just store in object's buffer
    std::string token;
    
    while (iss >> token) {   // like cout, >> operator meant to extract the stream of characters, but with one difference
                             // it does not extract  whole stream of characters, but it extract until it find a whitespace
                             // and it does not print the extracted characters, it just store in a string object, here called token
                             //and when it reach the end of the stream, it return false
            //=========Debugging=========
#ifdef DEBUG
            std::cout << "TOKEN IS: " << token << std::endl;
#endif
            //===========================    
            if (!isValidToken(token)) {
            throw std::runtime_error("Invalid token: " + token);
        }
        
        if (isOperator(token)) 
        {
            //=========Debugging=========
#ifdef DEBUG
            std::cout << "Our token is an operator => " << token << std::endl;
#endif
            //===========================
            if (_stack.size() < 2) { // if we have we only have an operator in our stack,  RPN will not work
                throw std::runtime_error("Not enough operands for operator: " + token);
            }
            // we take first two elements from stack and store in a and b
            int b = _stack.pop();
            int a = _stack.pop();
            //=========Debugging=========
#ifdef DEBUG
            std::cout << "POPPING " << b << " b = " << b << std::endl;
            std::cout << "POPPING " << a << " a = " << a << std::endl;
#endif
            //===========================

            int result = performOperation(a, b, token);
            //=========Debugging=========
#ifdef DEBUG
            std::cout << " = " << result << std::endl;
            std::cout << std::endl;
            std::cout << "PUSHING " << result << " to the stack" << std::endl;
#endif
            //===========================

            _stack.push(result);
        } 
        else // if it is a number
          {
            int num = token[0] - '0'; // convert the first character of the token to an integer and store in num
            //=========Debugging=========
#ifdef DEBUG
            std::cout << "PUSHING " << num << " to the stack" << std::endl;
#endif
            //===========================
            _stack.push(num);   // push the number to the stack
          }
    }
    
    if (_stack.size() != 1) {
        throw std::runtime_error("Invalid expression: too many operands");
    }

    //=========Debugging=========
#ifdef DEBUG
    std::cout << "our stack contains only one element: " << _stack.top() << std::endl;
#endif
    
    return _stack.top();
} 