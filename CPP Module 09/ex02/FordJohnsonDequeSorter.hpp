#ifndef FORDJOHNSONDEQUESORTER_HPP
#define FORDJOHNSONDEQUESORTER_HPP

#include <deque>
#include <vector>
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
    typedef std::deque<int> DBlock;
    typedef std::deque<DBlock> DBlocks;
    typedef DBlocks::iterator DBlocksIt;

    DBlocks _in;
    DBlocks _out;
    int _comparisons;

    void ingestDeque(const std::deque<int>& values);
    void runDeque();
    void dump(const DBlocks& data) const;

    static std::vector<int> buildJacobsthalInsertionOrder(int n);

    DBlocks doSort(DBlocks& elements);
    DBlocks doSortWithIds(DBlocks& elements, const std::vector<int>& elementIds, std::vector<int>& outIds);
    DBlocks doSortWithIds(DBlocks& elements, const std::vector<int>& elementIds, std::vector<int>& outIds, int depth);
    DBlocksIt lowerBound(DBlocksIt first, DBlocksIt last, const DBlock& value);

    bool isLessFirst(const DBlock& a, const DBlock& b);
};

#endif


