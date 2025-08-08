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

    void loadInputData(int argumentCount, char* argumentValues[]);
    void performSortOperations();
    void printResults();
    int getTotalComparisons() const;
    size_t getInputSize() const;
};

#endif
