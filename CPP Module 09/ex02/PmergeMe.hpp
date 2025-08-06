/* ************************************************************************** */
/*                          PmergeMe.hpp (refactored)                          */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <cstddef>
#include <ctime>
#include <string>
#include <iostream>

class PmergeMe
{
public:
    // ==================== CANONICAL FORM ====================
    PmergeMe();
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);
    ~PmergeMe();

    // ==================== PUBLIC API ====================
    void sortVector(std::vector<int>& v);

    static std::size_t comparisons();
    static void resetComparisons();
    static double us(clock_t s, clock_t e);
    
    // ==================== DEBUG CONTROL ====================
    static void enableDebug(bool enable = true);
    static bool isDebugEnabled();

private:
    // ==================== STATIC STATE ====================
    static std::size_t _cmp;       // Global comparison counter
    static bool _debug_enabled;    // Debug output control
};

#endif /* PMERGEME_HPP */
