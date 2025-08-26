#ifndef RPN_HPP
#define RPN_HPP

#include <list>
#include <iostream>

template<typename T>
class Stack {
private:
    std::list<T> _container;

public:
    Stack() {}
    ~Stack() {}
    
    void push(const T& value) {
        _container.push_back(value);
    }
    
    T pop() {
        if (_container.empty()) {
            throw std::runtime_error("Stack is empty");
        }
        T value = _container.back();
        _container.pop_back();
        return value;
    }
    
    T top() const {
        if (_container.empty()) {
            throw std::runtime_error("Stack is empty");
        }
        return _container.back();
    }
    
    bool empty() const {
        return _container.empty();
    }
    
    size_t size() const {
        return _container.size();
    }
};

class RPN {
private:
    Stack<int> _stack;                                               // stack of integers
    
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