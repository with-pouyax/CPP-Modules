#ifndef WHATEVER_HPP
#define WHATEVER_HPP


// These are global templates because they are defined outside of any class or namespace

template<typename T>
void swap(T& a, T& b) { // we receive a reference to a and b, so we can modify them
    T temp = a;
    a = b;
    b = temp;
}

template<typename T>
const T& min(const T& a, const T& b) {
    return (a < b) ? a : b;
}

template<typename T>
const T& max(const T& a, const T& b) {
    return (a > b) ? a : b;
}

#endif