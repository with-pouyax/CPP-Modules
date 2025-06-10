#include <iostream>
#include <string>
#include "iter.hpp"

// Function to print any type (by const reference)
template <typename T>
void print(const T& x) {
    std::cout << x << " ";
}

// Function to increment an int (by non-const reference)
void increment(int& x) {
    ++x;
}

// Function to uppercase a char (by non-const reference)
void to_upper(char& c) {
    if ('a' <= c && c <= 'z')
        c = c - 'a' + 'A';
}

int main() {
    // Test with int array (non-const)
    int arr[] = {1, 2, 3, 4, 5};
    size_t len = sizeof(arr) / sizeof(arr[0]);
    std::cout << "Original int array: ";
    iter(arr, len, print<int>);
    std::cout << std::endl;
    iter(arr, len, increment);
    std::cout << "Incremented int array: ";
    iter(arr, len, print<int>);
    std::cout << std::endl;

    // Test with const int array
    const int carr[] = {10, 20, 30};
    size_t clen = sizeof(carr) / sizeof(carr[0]);
    std::cout << "Const int array: ";
    iter(carr, clen, print<int>);
    std::cout << std::endl;

    // Test with std::string array
    std::string sarr[] = {"hello", "world", "iter"};
    size_t slen = sizeof(sarr) / sizeof(sarr[0]);
    std::cout << "String array: ";
    iter(sarr, slen, print<std::string>);
    std::cout << std::endl;

    // Test with char array (non-const, to_upper)
    char carr2[] = "iterTest";
    size_t clen2 = 8; // not including null terminator
    std::cout << "Original char array: ";
    iter(carr2, clen2, print<char>);
    std::cout << std::endl;
    iter(carr2, clen2, to_upper);
    std::cout << "Uppercased char array: ";
    iter(carr2, clen2, print<char>);
    std::cout << std::endl;

    return 0;
} 