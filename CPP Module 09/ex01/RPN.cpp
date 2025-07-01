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
    std::istringstream iss(expression);
    std::string token;
    
    while (iss >> token) {
        if (!isValidToken(token)) {
            throw std::runtime_error("Invalid token: " + token);
        }
        
        if (isOperator(token)) {
            if (_stack.size() < 2) {
                throw std::runtime_error("Not enough operands for operator: " + token);
            }
            
            int b = _stack.pop();
            int a = _stack.pop();
            int result = performOperation(a, b, token);
            _stack.push(result);
        } else {
            int num = token[0] - '0';
            _stack.push(num);
        }
    }
    
    if (_stack.size() != 1) {
        throw std::runtime_error("Invalid expression: too many operands");
    }
    
    return _stack.top();
} 