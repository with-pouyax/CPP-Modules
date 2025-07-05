#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP

#include <stack>                          // for std::stack
#include <deque>                          // for std::deque

template<typename T>
class MutantStack : public std::stack<T>  // so we defined a class called MutantStack
                                          // : public std::stack<T> means, our class inherits all public and protected of stack class
{
public:
    // This is made of 3 parts:
    // 1- typedef 2- typename std::stack<T>::container_type::iterator 3- iterator
        // 1- typedef is a keyword that defines a new name (alias) for an existing type.
        // 2- the existing type (e.g., int, std::vector<T>::iterator, etc.),
        // 3- and the new name (alias) you want to use instead.
    // "Here we make an alias (typedef),
    // called iterator,
    // which refers to an iterator type (::iterator),
    // of the internal container (container_type),
    // which is used inside std::stack<T>."
    // the keyword typename is used to tell the compiler that the following identifier is a type.
    // imagine we have std::stack<int>::container_type::iterator it;
    // it means we have an iterator of the container type of the stack that holds ints
    // so in our case we have an iterator of the container type of the stack that holds type T
    typedef typename std::stack<T>::container_type::iterator iterator;

    // Constructor and destructor (using default)
    MutantStack() : std::stack<T>() {} // our class inherits from std::stack<T>
    MutantStack(const MutantStack& other) : std::stack<T>(other) {}
    virtual ~MutantStack() {}

    // Assignment operator
    MutantStack& operator=(const MutantStack& other)
    {
        if (this != &other)
            std::stack<T>::operator=(other);
        return *this;
    }

    // Iterator methods
    iterator begin() { return this->c.begin(); }
    iterator end() { return this->c.end(); }
};

#endif // MUTANTSTACK_HPP 