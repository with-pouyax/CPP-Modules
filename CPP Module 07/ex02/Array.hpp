#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <stdexcept>

// here we are defining a template class Array that can hold elements of any type (T).
template<typename T>
class Array {
private: 
    T* _array;           // _array is a pointer to dynamically allocated(with new) array that holds elements of type any type (T).
    unsigned int _size;  // _size holds the number of elements in the array.

public:
    // Default constructor
    Array();
    
    // Constructor with size
    Array(unsigned int n);
    
    // Copy constructor
    Array(const Array& other);
    
    // Assignment operator
    Array& operator=(const Array& other);
    
    // Destructor
    ~Array();
    
    // Subscript operator
    T& operator[](unsigned int index); // This operator allows access to the elements of the array by index.
    
    // Const subscript operator
    const T& operator[](unsigned int index) const; // This operator allows access to the elements of the array by index, but it does not allow modification of the elements.
    
    // Size function
    unsigned int size() const; // This function returns the number of elements in the array 
};

#include "Array.tpp"

#endif 