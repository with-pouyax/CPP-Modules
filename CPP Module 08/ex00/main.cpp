#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include "easyfind.hpp"

int main() {
    try {
        // Test with vector
        std::vector<int> vec;
        for (int i = 0; i < 5; i++)
            vec.push_back(i * 2);
        
        std::cout << "Vector test:" << std::endl;
        std::vector<int>::iterator it = easyfind(vec, 4);
        std::cout << "Found value: " << *it << std::endl;
        
        // Test with list
        std::list<int> lst;
        for (int i = 0; i < 5; i++)
            lst.push_back(i * 3);
        
        std::cout << "\nList test:" << std::endl;
        std::list<int>::iterator it2 = easyfind(lst, 6);
        std::cout << "Found value: " << *it2 << std::endl;
        
        // Test with deque
        std::deque<int> dq;
        for (int i = 0; i < 5; i++)
            dq.push_back(i * 4);
        
        std::cout << "\nDeque test:" << std::endl;
        std::deque<int>::iterator it3 = easyfind(dq, 8);
        std::cout << "Found value: " << *it3 << std::endl;
        
        // Test not found case
        std::cout << "\nTesting not found case:" << std::endl;
        easyfind(vec, 999);
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    return 0;
} 