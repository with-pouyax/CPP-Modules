#ifndef FORDJOHNSONDEQUESORTER_HPP
#define FORDJOHNSONDEQUESORTER_HPP

#include <deque>
#include <cstddef>

class FordJohnsonDequeSorter
{
public:
    FordJohnsonDequeSorter();
    ~FordJohnsonDequeSorter();

    // Orthodox Canonical Form
    FordJohnsonDequeSorter(const FordJohnsonDequeSorter& other);
    FordJohnsonDequeSorter& operator=(const FordJohnsonDequeSorter& rhs);

    // Perform the sort using provided values; stores input/output internally
    void performSort(const std::deque<int>& valuesDeque);

    // Output and stats (match previous behavior)
    void printResults() const;
    int getTotalComparisons() const;
    size_t getInputSize() const;

private:
    struct Impl;
    Impl* _p;
};

#endif


