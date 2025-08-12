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
    FordJohnsonVectorSorter(const FordJohnsonVectorSorter& other);            // copy constructor
    FordJohnsonVectorSorter& operator=(const FordJohnsonVectorSorter& rhs);   // copy assignment operator

    void performSort(const std::vector<int>& valuesVector);             // perform the sort using the provided values

    // Output and stats (match previous behavior)
    void printResults() const;                                        // print the results
    int getTotalComparisons() const;                                  // get the total number of comparisons
    size_t getInputSize() const;                                      // get the input size

private:
    // Internal block types representing the Ford-Johnson grouping
    typedef std::vector<int> VBlock;            // from now instead of using std::vector<int> we use VBlock (vector of integers)
    typedef std::vector<VBlock> VBlocks;        // from now instead of using std::vector<std::vector<int>> we use VBlocks (vector of vectors of integers)
    typedef VBlocks::iterator VBlocksIt;        // from now instead of using std::vector<int>::iterator we use VBlocksIt (iterator for the vector of vectors of integers)

    // Data
    VBlocks _in;             // we store the input vector in _in
    VBlocks _out;            // we store the sorted vector in _out
    int _comparisons;        // number of comparisons


    void ingestVector(const std::vector<int>& values);      //int recieves a vector of integers and ingests (mean in farsi: بلعیدن) it in _in
    void runVector();
    void dump(const VBlocks& data) const;

    static std::vector<int> buildJacobsthalInsertionOrder(int n);

    VBlocks doSort(VBlocks& elements);
    VBlocks doSortWithIds(VBlocks& elements, const std::vector<int>& elementIds, std::vector<int>& outIds);
    VBlocks doSortWithIds(VBlocks& elements, const std::vector<int>& elementIds, std::vector<int>& outIds, int depth);
    VBlocksIt lowerBound(VBlocksIt first, VBlocksIt last, const VBlock& value);

    // Centralized comparison that also increments the comparison counter
    bool isLessFirst(const VBlock& a, const VBlock& b);
};

#endif


