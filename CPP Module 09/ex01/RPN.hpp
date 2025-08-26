#ifndef RPN_HPP
#define RPN_HPP

#include <string>
#include <iostream>

// Custom stack implementation without STL containers
class Stack {
private:
    static const int MAX_SIZE = 1000;
    int _data[MAX_SIZE];
    int _top;

public:
    Stack() : _top(-1) {}
    ~Stack() {}
    
    void push(int value) {
        if (_top >= MAX_SIZE - 1) {
            throw std::runtime_error("Stack overflow");
        }
        _data[++_top] = value;
    }
    
    int pop() {
        if (empty()) {
            throw std::runtime_error("Stack is empty");
        }
        return _data[_top--];
    }
    
    int top() const {
        if (empty()) {
            throw std::runtime_error("Stack is empty");
        }
        return _data[_top];
    }
    
    bool empty() const {
        return _top == -1;
    }
    
    size_t size() const {
        return _top + 1;
    }
};

class RPN {
private:
    Stack _stack;                                               // stack of integers
    
    bool isOperator(const std::string& token);                       // check if the token is an operator
    int performOperation(int a, int b, const std::string& op);       // perform the operation
    bool isValidToken(const std::string& token);                     // check if the token is valid

public:
    // orthodox canonical form
    RPN();
    ~RPN();
    RPN(const RPN& other);
    RPN& operator=(const RPN& other);
    
    // evaluate the expression
    int evaluate(const std::string& expression);
};

#endif // RPN_HPP 