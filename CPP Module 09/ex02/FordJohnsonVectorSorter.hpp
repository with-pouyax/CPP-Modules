#ifndef FORDJOHNSONVECTORSORTER_HPP
#define FORDJOHNSONVECTORSORTER_HPP

#include <vector>
#include <cstddef>

class FordJohnsonVectorSorter
{
public:
    FordJohnsonVectorSorter(); // constructor
    ~FordJohnsonVectorSorter(); // destructor

    // Orthodox Canonical Form
    FordJohnsonVectorSorter(const FordJohnsonVectorSorter& other);
    FordJohnsonVectorSorter& operator=(const FordJohnsonVectorSorter& rhs);

    // Perform the sort using provided values; stores input/output internally
    void performSort(const std::vector<int>& valuesVector);             // perform the sort using the provided values

    // Output and stats (match previous behavior)
    void printResults() const;                                        // print the results
    int getTotalComparisons() const;                                  // get the total number of comparisons
    size_t getInputSize() const;                                      // get the input size

private:
    struct Impl;                                      // a struct that contains the values
    Impl* _p;
};

#endif


