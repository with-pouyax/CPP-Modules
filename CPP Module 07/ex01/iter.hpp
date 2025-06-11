#ifndef ITER_HPP
#define ITER_HPP

#include <cstddef> // for size_t

// For non-const arrays
// T* array means that we can receive an array of any type
// we dont need to template the length because we can only receive an array and array length is always size_t
// F func means that we can receive a function that takes
template <typename T, typename F>
void iter(T* array, size_t length, F func) {
    for (size_t i = 0; i < length; ++i) //we iterate over the array and apply the function to each element
        func(array[i]);
}

// For const arrays
// we need also a template for const because as the subject we need to be able to receive any type of array
template <typename T, typename F>
void iter(const T* array, size_t length, F func) {
    for (size_t i = 0; i < length; ++i)
        func(array[i]);
}

#endif // ITER_HPP 