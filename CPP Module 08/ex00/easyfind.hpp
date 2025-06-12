#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <algorithm>
#include <stdexcept>

template<typename T>
typename T::iterator easyfind(T& container, int value) {     // we have a function called easyfind that returns an iterator (a pointer to an element in the container) to a T type container
    
    // find receives the range we are looking for as 1st and 2nd parameters, and the value we are looking for as the 3rd parameter
    // if the value is not found, it returns an iterator to the end of the container
    typename T::iterator it = std::find(container.begin(), container.end(), value);
    if (it == container.end())
        throw std::runtime_error("Value not found in container");
    return it;
}

#endif // EASYFIND_HPP 