#ifndef ITER_HPP
#define ITER_HPP

#include <cstddef> // for size_t

// For non-const arrays
template <typename T, typename F>
void iter(T* array, size_t length, F func) {
    for (size_t i = 0; i < length; ++i)
        func(array[i]);
}

// For const arrays
template <typename T, typename F>
void iter(const T* array, size_t length, F func) {
    for (size_t i = 0; i < length; ++i)
        func(array[i]);
}

#endif // ITER_HPP 