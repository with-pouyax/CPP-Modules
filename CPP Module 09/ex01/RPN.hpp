#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <string>
#include <stack>
#include <list>

// Custom stack using std::stack with std::list as container
typedef std::stack<int, std::list<int> > Stack; // std::stack<int, std::list<int> > means we are using a stack of integers with a list of integers as the container
                                                // typedef is used to give a new name to a type, which is Stack

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