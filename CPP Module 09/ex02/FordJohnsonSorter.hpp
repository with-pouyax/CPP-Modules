#ifndef FORDJOHNSONSORTER_HPP
#define FORDJOHNSONSORTER_HPP

#include <vector>
#include <deque>
#include <string>

class FordJohnsonSorter
{
private:
    struct Impl;
    Impl* _p;
    FordJohnsonSorter(const FordJohnsonSorter& other);
    FordJohnsonSorter& operator=(const FordJohnsonSorter& rhs);

public:
    FordJohnsonSorter();
    ~FordJohnsonSorter();

    // Load pre-parsed input values; parsing is handled outside this class.
    void loadInputData(const std::vector<int>& valuesVector, const std::deque<int>& valuesDeque);
    void performSortOperations();
    void performVectorSort();
    void performDequeSort();
    void performVectorSort(const std::vector<int>& valuesVector);
    void performDequeSort(const std::deque<int>& valuesDeque);
    void printResults();
    int getTotalComparisons() const;
    size_t getInputSize() const;
};

#endif
