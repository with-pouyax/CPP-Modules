#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include "easyfind.hpp"

int main() {
    // Test with vector
    std::vector<int> vec;           // Create a vector of integers
    for (int i = 0; i < 5; i++)     //loop to fill the vector with values
        vec.push_back(i * 2);
    
    std::cout << "\n\nVector test:" << std::endl;
    std::vector<int>::iterator it = easyFind(vec, 4);  // Call easyFind to search for the value 4 in the vector
    std::cout << "Found value: " << *it << std::endl;  // 
    
    std::cout << "-------------------------" << std::endl;

    // Test with list
    std::list<int> lst;
    for (int i = 0; i < 5; i++)
        lst.push_back(i * 3);
    
    std::cout << "\nList test:" << std::endl;
    std::list<int>::iterator it2 = easyFind(lst, 6);
    std::cout << "Found value: " << *it2 << std::endl;
    
    std::cout << "-------------------------" << std::endl;

    // Test with deque
    std::deque<int> dq;
    for (int i = 0; i < 5; i++)
        dq.push_back(i * 4);
    
    std::cout << "\nDeque test:" << std::endl;
    std::deque<int>::iterator it3 = easyFind(dq, 8);
    std::cout << "Found value: " << *it3 << std::endl;
    
    std::cout << "-------------------------" << std::endl;

    // Test not found case
    std::cout << "\nTesting not found case:" << std::endl;
    try {
        easyFind(vec, 999);
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    std::cout << "-------------------------" << std::endl;
    
    // Test empty container case
    std::cout << "\nTesting empty container case:" << std::endl;
    std::vector<int> emptyVec;
    try {
        easyFind(emptyVec, 1);
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    std::cout << "-------------------------" << std::endl;
    
    return 0;
} 