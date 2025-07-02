#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <algorithm>
#include <stdexcept>

// c++ compiler first run a parser to check if the code is correct.
// so parser dont know what T is
// it will then compile the code
//parser sees T::iterator and asks: “Is iterator a type inside T? Or is it a static variable? Or a nested constant?”
//using typename keyword we tell the compiler that iterator is a type inside T like begin()

template<typename T>
typename T::iterator easyFind(T& container, int value) { 
    if (container.empty())
        throw std::runtime_error(std::string("Container is empty")); // in c++11, we can write throw std::runtime_error("Container is empty");
                                                                     // runtime_error because it is a conditions that can only be detected during program execution.
        
        
    typename T::iterator it = std::find(container.begin(), container.end(), value);
    if (it == container.end())
        throw std::runtime_error(std::string("Value not found in container"));
    return it;
}

#endif // EASYFIND_HPP