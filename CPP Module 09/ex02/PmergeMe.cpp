/* ************************************************************************** */
/*                          PmergeMe.cpp (refactored)                          */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <algorithm>   // std::swap
#include <iostream>
#include <cstdio>      // sprintf

// ==================== STATIC DATA ====================
std::size_t PmergeMe::_cmp = 0;
bool PmergeMe::_debug_enabled = false;  // Debug output control

// ==================== DEBUG CONTROL ====================
void PmergeMe::enableDebug(bool enable) {
    _debug_enabled = enable;
}

bool PmergeMe::isDebugEnabled() {
    return _debug_enabled;
}

// ==================== UTILITY FUNCTIONS ====================
std::size_t PmergeMe::comparisons()
{
    return _cmp;
}

void PmergeMe::resetComparisons()
{
    _cmp = 0;
}

double PmergeMe::us(clock_t s, clock_t e)
{
    return static_cast<double>(e - s) * 1e6 / CLOCKS_PER_SEC;
}

// ==================== CANONICAL FORM ====================
PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe&) {}

PmergeMe& PmergeMe::operator=(const PmergeMe&)
{
    return *this;
}

PmergeMe::~PmergeMe() {}

// ==================== PUBLIC API ====================
void PmergeMe::sortVector(std::vector<int>& v)
{
    // TODO: Implement your sorting algorithm here
    // This function is now empty - add your sorting implementation
    
    if (_debug_enabled) {
        std::cout << "Debug: sortVector called with " << v.size() << " elements" << std::endl;
    }
    
    // Your sorting algorithm goes here
    // The vector v will remain unsorted until you implement your algorithm
}
