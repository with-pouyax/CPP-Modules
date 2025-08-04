/* ************************************************************************** */
/*                                                                            */
/*                               main.cpp                                     */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>     // std::cout, std::cerr
#include <sstream>      // std::istringstream
#include <iomanip>      // std::setprecision

/* ---------- main.cpp : replace parseInt ---------- */
static bool parseInt(const char *s, int &out)
{
    std::istringstream iss(s);
    long long tmp;

    /* must read a number */
    if (!(iss >> tmp))
        return false;
    /* range check (positive 32-bit int) */
    if (tmp <= 0 || tmp > 2147483647LL)
        return false;
    /* ensure nothing but optional trailing WS */
    char c;
    if (iss >> c)                  // any extra char? -> error
        return false;

    out = static_cast<int>(tmp);
    return true;
}


int main(int ac, char **av)
{
    if (ac < 2)
    {
        std::cerr << "Error: need at least one positive integer\n";
        return 1;
    }

    std::vector<int> v;
    std::deque<int>  d;

    for (int i = 1; i < ac; ++i)
    {
        int val;
        if (!parseInt(av[i], val))
        {
            std::cerr << "Error\n";
            return 1;
        }
        v.push_back(val);
        d.push_back(val);
    }

    std::cout << "Before:";
    for (std::size_t i = 0; i < v.size(); ++i)
        std::cout << ' ' << v[i];
    std::cout << '\n';

    PmergeMe sorter;

    /* ---- vector ---- */
    PmergeMe::resetComparisons();
    clock_t vStart = std::clock();
    sorter.sortVector(v);
    clock_t vEnd   = std::clock();
    double vTimeUs = PmergeMe::us(vStart, vEnd);
    std::size_t vCmp = PmergeMe::comparisons();

    /* ---- deque ---- */
    PmergeMe::resetComparisons();
    clock_t dStart = std::clock();
    sorter.sortDeque(d);
    clock_t dEnd   = std::clock();
    double dTimeUs = PmergeMe::us(dStart, dEnd);
    std::size_t dCmp = PmergeMe::comparisons();

    std::cout << "After:";
    for (std::size_t i = 0; i < v.size(); ++i)
        std::cout << ' ' << v[i];
    std::cout << '\n';

    std::cout << "Time to process a range of " << v.size()
              << " elements with std::vector : "
              << std::fixed << std::setprecision(6) << vTimeUs << " us"
              << " | comparisons: " << vCmp << '\n';

    std::cout << "Time to process a range of " << d.size()
              << " elements with std::deque  : "
              << std::fixed << std::setprecision(6) << dTimeUs << " us"
              << " | comparisons: " << dCmp << '\n';

    return 0;
}
