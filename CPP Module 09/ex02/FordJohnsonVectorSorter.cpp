#include "FordJohnsonVectorSorter.hpp"

#include <iostream>
#include <vector>
#include <stdexcept>
#include <map>
#include <iterator>
#include <algorithm>

#ifdef PMERGEME_DEBUG
// ============================ DEBUG HELPERS =============================
// Pretty printers for nested containers using bracket notation
static void dbgPrintVBlock(const std::vector<int>& block)
{
    std::cout << "[";
    for (size_t i = 0; i < block.size(); ++i)
    {
        std::cout << block[i];
        if (i + 1 != block.size()) std::cout << ", ";
    }
    std::cout << "]";
}

static void dbgPrintVBlocks(const std::vector< std::vector<int> >& blocks, const char* label)
{
    if (label && *label) std::cout << label << ": ";
    std::cout << "[";
    for (size_t i = 0; i < blocks.size(); ++i)
    {
        dbgPrintVBlock(blocks[i]);
        if (i + 1 != blocks.size()) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}

static void dbgPrintIntVector(const std::vector<int>& v, const char* label)
{
    if (label && *label) std::cout << label << ": ";
    std::cout << "[";
    for (size_t i = 0; i < v.size(); ++i)
    {
        std::cout << v[i];
        if (i + 1 != v.size()) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}
// ============================= DEBUG END ===============================
#endif

FordJohnsonVectorSorter::FordJohnsonVectorSorter()
    : _in(), _out(), _comparisons(0)
{
}

FordJohnsonVectorSorter::~FordJohnsonVectorSorter() {}

FordJohnsonVectorSorter::FordJohnsonVectorSorter(const FordJohnsonVectorSorter& other)
    : _in(other._in), _out(other._out), _comparisons(other._comparisons)
{
}

FordJohnsonVectorSorter& FordJohnsonVectorSorter::operator=(const FordJohnsonVectorSorter& rhs)
{
    if (this != &rhs)
    {
        _in = rhs._in;
        _out = rhs._out;
        _comparisons = rhs._comparisons;
    }
    return *this;
}

void FordJohnsonVectorSorter::ingestVector(const std::vector<int>& values) // values is our input vector of integers
{
    _in.clear();
    for (size_t i = 0; i < values.size(); ++i) // we loop through the input vector
    {
        VBlock valueBlock;                     // we create a vector of integers
        valueBlock.push_back(values[i]);    // we push the value to the end of the vector
        _in.push_back(valueBlock);          // we push the vector of integers to the end of _in
    }
}

void FordJohnsonVectorSorter::runVector()
{
    _comparisons = 0;                   // we reset the number of comparisons
    _out.clear();                       // we clear the output vector
    VBlocks tmp = _in;                  // we create a temporary vector of vectors of integers and we store _in in it
    _out = doSort(tmp);      
}

void FordJohnsonVectorSorter::dump(const VBlocks& data) const
    {
        VBlocks::const_iterator a = data.begin();
        VBlocks::const_iterator b = data.end();
        for (VBlocks::const_iterator it = a; it != b; ++it)
        {
            for (size_t i = 0; i < it->size(); ++i) std::cout << (*it)[i];
            if (it + 1 != b) std::cout << " ";
        }
        std::cout << std::endl;
    }

std::vector<int> FordJohnsonVectorSorter::buildJacobsthalInsertionOrder(int n) // n is the size of the vector we want to create jacobsthal insertion order for
{
    const int limit = n + 1;            // + 1 because we want to include the last element in the vector because n is the size of the vector but the index starts from 0
    std::vector<int> order;             // we create a vector of integers called order
    int a = 0, b = 1;                   // we create two integers called a and b and we initialize them to 0 and 1
    while (b < limit)                   // as long as b is less than limit
    {
        for (int k = b; k > a; --k) order.push_back(k - 1);     // we loop through the vector and 
        int next = b + 2 * a; a = b; b = next;
    }
    for (int k = limit - 1; k > a; --k) order.push_back(k - 1);
    return order;
}

FordJohnsonVectorSorter::VBlocksIt FordJohnsonVectorSorter::lowerBound(VBlocksIt first, VBlocksIt last, const VBlock& value)
{
    // Binary search on first element of block
    typedef std::iterator_traits<VBlocksIt>::difference_type Diff; // std::iterator_traits<VBlocksIt>::difference_type is a type that is the difference between two iterators
                                                                   // now Diff is a type that is the difference between two iterators
    Diff count = last - first; // we store the difference between last and first in count
    while (count > 0) // we loop through the range from first to last
    {
        Diff step = count / 2; // we store the half of the count in step
        VBlocksIt mid = first + step; // we store the middle of the range in mid
        if (isLessFirst(*mid, value)) // if the first element of mid is less than value
        {
            first = ++mid; // we move the first iterator to the next element
            count -= step + 1; // we subtract the step and 1 from the count
        }
        else
        {
            count = step; // we find the half of the count and we store it in count
        }
    }
    return first;
}

bool FordJohnsonVectorSorter::isLessFirst(const VBlock& a, const VBlock& b)
{
    ++_comparisons;
    return a[0] < b[0];
}

//*****************************Continues from here*****************************
//*  - elements is a vector of vectors that contains input elements
//*  - elementIds is a vector of integers that contains the ids of the input elements
//*  - outIds is a vector of integers that contains the ids of the sorted elements
//*  - odd is a vector of integers that contains the odd (right) element of each pair
//*  - smallBlocks is a vector of vectors of integers that contains the smaller elements of each pair
//*  - biggersBlocks is a vector of vectors of integers that contains the bigger elements of each pair
//*  - smallIds is a vector of integers that contains the ids of the smaller elements
//*  - biggersIds is a vector of integers that contains the ids of the bigger elements
//*  - sortedBiggersIds is a vector of integers that contains the ids of the sorted bigger elements
//*  - rightIdToIdx is a map of integers to size_t that contains the index of the right element of each pair
//*  - jSeq is a vector of integers that contains the jacobsthal insertion order
//*  - chainIds is a vector of integers that contains the ids of the sorted elements
//*  

FordJohnsonVectorSorter::VBlocks FordJohnsonVectorSorter::doSortWithIds(VBlocks& elements, const std::vector<int>& elementIds, std::vector<int>& outIds)
{
    return doSortWithIds(elements, elementIds, outIds, 0);
}

FordJohnsonVectorSorter::VBlocks FordJohnsonVectorSorter::doSortWithIds(VBlocks& elements, const std::vector<int>& elementIds, std::vector<int>& outIds, int depth)
{
#ifdef PMERGEME_DEBUG
    // ============================ DEBUG BEGIN =============================
    // [DBG] ENTER doSortWithIds
    std::cout << "\n===== [Vector] doSortWithIds: ENTER (depth=" << depth << ") =====" << std::endl;
    dbgPrintVBlocks(elements, "elements");
    dbgPrintIntVector(elementIds, "elementIds");
    // ============================= DEBUG END ==============================
#endif
    //-------------------------- base case --------------------------
    if (elements.size() < 2) // if the size of the input vector is less than 2
    {
        outIds = elementIds; // outIds will be equal to elementIds
#ifdef PMERGEME_DEBUG
        // ============================ DEBUG BEGIN =============================
        // [DBG] BASE CASE
        std::cout << "Base case hit. Return elements as-is." << std::endl;
        std::cout << "===== [Vector] doSortWithIds: EXIT (base, depth=" << depth << ") =====\n" << std::endl;
        // ============================= DEBUG END ==============================
#endif
        return elements; // we return the input vector
    }
    // --------------------------------------------------------------

    //-------------------------- odd case --------------------------
    VBlock odd;                                             // we create a vector of integers called odd
    int oddId = -1;                                         // we create an integer called oddId and we initialize it to -1
    const bool hasOdd = (elements.size() % 2 != 0);         // we check if the size of the input vector is odd and if yes, we set hasOdd to true
    if (hasOdd) { odd = elements.back(); oddId = elementIds.back(); } // if we have an odd number of elements, we assign the last element of the input vector to odd variable
                                                                      // also we assign the last element of the elementIds vector to oddId variable
#ifdef PMERGEME_DEBUG
    // ============================ DEBUG BEGIN =============================
    // [DBG] ODD FLAG AND ODD BLOCK
    std::cout << "  [depth=" << depth << "] hasOdd=" << (hasOdd ? "true" : "false") << std::endl;
    if (hasOdd) { std::cout << "  [depth=" << depth << "] odd="; dbgPrintVBlock(odd); std::cout << " (id=" << oddId << ")" << std::endl; }
    // ============================= DEBUG END ==============================
#endif

    //-------------------------- pairing --------------------------
    // Pairing: build small and big arrays and id maps
    VBlocks smallBlocks;                                     // we create a vector of vectors of integers called smallBlocks to store the smaller elements
    std::vector<int> smallIds;                               // we create a vector of integers called smallIds to store the ids of the smaller elements
    VBlocks biggersBlocks;                                   // we create a vector of vectors of integers called biggersBlocks to store the bigger elements
    std::vector<int> biggersIds;                             // we create a vector of integers called biggersIds to store the ids of the bigger elements
    for (size_t i = 0; i + 1 < elements.size(); i += 2)      // we loop through the input vector
    {
        VBlock left = elements[i]; int leftId = elementIds[i];            // we assign the i-th element of the input vector to left variable and the i-th element of the elementIds vector to leftId variable
        VBlock right = elements[i + 1]; int rightId = elementIds[i + 1];  // we assign the i+1-th element of the input vector to right variable and the i+1-th element of the elementIds vector to rightId variable
#ifdef PMERGEME_DEBUG
        // ============================ DEBUG BEGIN =============================
        // [DBG] PAIR FORMATION BEFORE SORT
        std::cout << "  [depth=" << depth << "] Pair " << (i/2) << " before sort: left="; dbgPrintVBlock(left);
        std::cout << " (id=" << leftId << ")  right="; dbgPrintVBlock(right);
        std::cout << " (id=" << rightId << ")" << std::endl;
        // ============================= DEBUG END ==============================
#endif
        bool leftLessRight = isLessFirst(left, right);
        if (!leftLessRight) { std::swap(left, right); std::swap(leftId, rightId); } // if the first element of left is greater than the first element of right, we swap the elements
#ifdef PMERGEME_DEBUG
        // ============================ DEBUG BEGIN =============================
        // [DBG] PAIR AFTER POSSIBLE SWAP
        std::cout << "  [depth=" << depth << "] Pair " << (i/2) << (leftLessRight ? " sorted" : " (post-swap)") << ": left="; dbgPrintVBlock(left);
        std::cout << " (id=" << leftId << ")  right="; dbgPrintVBlock(right);
        std::cout << " (id=" << rightId << ")" << std::endl;
        // ============================= DEBUG END ==============================
#endif
        smallBlocks.push_back(left); smallIds.push_back(leftId);     // we push the left element to smallBlocks and the leftId to smallIds
        biggersBlocks.push_back(right); biggersIds.push_back(rightId); // we push the right element to biggersBlocks and the rightId to biggersIds
    }
#ifdef PMERGEME_DEBUG
    // ============================ DEBUG BEGIN =============================
    // [DBG] PAIRING RESULTS (SMALL/BIGGERS + IDS)
    dbgPrintVBlocks(smallBlocks,  "  [depth] smallBlocks");
    dbgPrintIntVector(smallIds,   "  [depth] smallIds");
    dbgPrintVBlocks(biggersBlocks,"  [depth] biggersBlocks (unsorted chain)");
    dbgPrintIntVector(biggersIds, "  [depth] biggersIds");
    if (hasOdd) { std::cout << "  [depth] leftoverOdd="; dbgPrintVBlock(odd); std::cout << " (id=" << oddId << ")" << std::endl; }
    else { std::cout << "  [depth] leftoverOdd=<none>" << std::endl; }
    // ============================= DEBUG END ==============================
#endif
    // --------------------------------------------------------------


    std::vector<int> sortedBiggersIds;       // we create a vector of integers called sortedBiggersIds to store the ids of the sorted bigger elements
    
    //--------------------------- recursive call --------------------------
    biggersBlocks = doSortWithIds(biggersBlocks, biggersIds, sortedBiggersIds, depth + 1); // we call doSortWithIds recursively


    #ifdef PMERGEME_DEBUG
    // ============================ DEBUG BEGIN =============================
    // [DBG] AFTER RECURSION
    std::cout << "After recursion (depth=" << depth << "):" << std::endl;
    dbgPrintIntVector(sortedBiggersIds, "  sortedBiggersIds");
    dbgPrintVBlocks(biggersBlocks, "  biggersBlocks");
    // ============================= DEBUG END ==============================
#endif
    // --------------------------------------------------------------
    
    // we first reach here when we reach the base case of the recursive call
    
    
    // Map rightId to index in smallBlocks/smallIds
    std::map<int, size_t> rightIdToIdx;           // we create a map of integers to size_t called rightIdToIdx
    for (size_t idx = 0; idx < biggersIds.size(); ++idx) rightIdToIdx[biggersIds[idx]] = idx; // we loop through biggersIds and we assign the index of the element to the map
                                                                                              // so now we have a map like this: {1: 0, 2: 1, 3: 2, 4: 3, 5: 4}
                                                                                              // so it shows which biggerId is related to which smallId

    const int chainSize = static_cast<int>(biggersBlocks.size());     // we make a constant integer called chainSize and we assign it the size of biggersBlocks


    #ifdef PMERGEME_DEBUG
    std::cout << "  [depth=" << depth << "] chainSize=" << chainSize << std::endl;
#endif
    

std::vector<int> jSeq = buildJacobsthalInsertionOrder(hasOdd ? chainSize + 1 : chainSize); // we store the jacobsthal insertion order in jSeq

    std::vector<int> chainIds = sortedBiggersIds; // we make a vector of integers called chainIds and we store sortedBiggersIds in it


    #ifdef PMERGEME_DEBUG
    // ============================ DEBUG BEGIN =============================
    // [DBG] JACOBSTHAL SEQUENCE
    std::cout << "Insertion sequence (Jacobsthal expanded) at depth " << depth << ": ";
    for (size_t i = 0; i < jSeq.size(); ++i) { std::cout << jSeq[i]; if (i + 1 != jSeq.size()) std::cout << " "; }
    std::cout << std::endl;
    dbgPrintIntVector(jSeq, "  [depth] jSeq");
    // ============================= DEBUG END ==============================
#endif
    

for (size_t pi = 0; pi < jSeq.size(); ++pi) // we loop through jSeq
    {

        VBlocksIt limit; // we create an iterator to vector of vectors of integers called limit
        VBlock target;   // we create a vector of integers called target
        int targetId;    // we create an integer called targetId
        
        //-------------------------- last element of the chain --------------------------
        if (jSeq[pi] == chainSize) {           // if the current jSeq element is equal to chainSize means we are at the last element of the chain
            target = odd; targetId = oddId;    // we assign the odd element to target and the oddId to targetId
            limit = biggersBlocks.end(); }     // we set iterator to the end of biggersBlocks (it is the last element of the chain)
        // ------------------------------------------------------------------------------
        
        else // if the current jSeq element is not equal to chainSize means we are not at the last element of the chain
        {
            // Find the right-hand block ("upper") by its stable id from the base sorted chain
            int idOfBiggerWhosePartnerIsNext = sortedBiggersIds[jSeq[pi]]; // we store the id of the value from sortedBiggersIds that we want to insert its partner from smallBlocks in biggersBlocks
            
            // Locate current position of that id in the evolving chain
            // chainIds = biggersIds
            size_t upperPos = 0;
            while (upperPos < chainIds.size() && chainIds[upperPos] != idOfBiggerWhosePartnerIsNext) ++upperPos; // we search for idOfBiggerWhosePartnerIsNext in chainIds
            // now upperPos = index of the idOfBiggerWhosePartnerIsNext in chainIds(biggersIds)
            if (upperPos >= chainIds.size()) throw std::invalid_argument("Invalid state: missing sorted partner"); // if we reach the end of chainIds, we throw an error
            
            // biggersBlocks.begin() = iterator to the first element of biggersBlocks
            // static_cast<std::ptrdiff_t>(upperPos) = index of the
            limit = biggersBlocks.begin() + static_cast<std::ptrdiff_t>(upperPos); // upperPos is a size_t, we jsut cast it to std::ptrdiff_t to be able to increment it
                                                                                   // so our range is always from begin to limit
                                                                                   
            
            std::map<int, size_t>::iterator found = rightIdToIdx.find(idOfBiggerWhosePartnerIsNext); // we find the index of the idOfBiggerWhosePartnerIsNext in rightIdToIdx and we store it in found
            if (found == rightIdToIdx.end()) throw std::invalid_argument("Invalid state: missing unsorted partner"); // if we don't find the id, we throw an error
            size_t idx = found->second; // we store the index of the idOfBiggerWhosePartnerIsNext in rightIdToIdx in idx
            target = smallBlocks[idx]; // we find the value of this index in smallBlocks and we store it in target
            targetId = smallIds[idx]; // we store the value of this index in smallIds in targetId
        }

#ifdef PMERGEME_DEBUG
        // ============================ DEBUG BEGIN =============================
        // [DBG] STEP REPORT
        std::cout << "  [depth=" << depth << "] Step " << pi << ": insert target=" << target[0] << " (id=" << targetId << ")";
        if (jSeq[pi] == chainSize) std::cout << " vs odd";
        std::cout << std::endl;
        // ============================= DEBUG END ==============================
#endif
        VBlocksIt lo = lowerBound(biggersBlocks.begin(), limit, target); // it will halve the range as much as we find the position of the target in the range
        size_t insertPos = static_cast<size_t>(lo - biggersBlocks.begin()); // we store the position of the target in biggersBlocks in insertPos
        biggersBlocks.insert(lo, target); // we insert the target in the position that we found in lo
        chainIds.insert(chainIds.begin() + insertPos, targetId); // we insert the targetId in the position of insertPos in chainIds
#ifdef PMERGEME_DEBUG
        // ============================ DEBUG BEGIN =============================
        // [DBG] POST-INSERT STATE
        dbgPrintIntVector(chainIds, "  [depth] chainIds after insert");
        dbgPrintVBlocks(biggersBlocks, "  [depth] biggersBlocks after insert");
        // ============================= DEBUG END ==============================
#endif
    }

    outIds = chainIds; // we store the chainIds in outIds

    #ifdef PMERGEME_DEBUG
    // ============================ DEBUG BEGIN =============================
    // [DBG] EXIT doSortWithIds
    std::cout << "===== [Vector] doSortWithIds: EXIT (depth=" << depth << ") =====\n" << std::endl;
    // ============================= DEBUG END ==============================
#endif
    return biggersBlocks;// we return the biggersBlocks which is the sorted chain
}

FordJohnsonVectorSorter::VBlocks FordJohnsonVectorSorter::doSort(VBlocks& elements)
{
    std::vector<int> initialIds;                // we create a vector of integers
    initialIds.reserve(elements.size());      // we reserve the size of our input for it
    for (size_t i = 0; i < elements.size(); ++i) initialIds.push_back(static_cast<int>(i)); // we loop through it and initialize IDs for each element
    std::vector<int> outIds;                     // we create a vector of integers called outIds
    // so now we have : elements (vector of vectors of our inputs) like [[1], [2], [3], [4], [5]]
    // initialIds (vector of integers) like [0, 1, 2, 3, 4]
    // outIds (it is empty for now)
    return doSortWithIds(elements, initialIds, outIds);
}

void FordJohnsonVectorSorter::performSort(const std::vector<int>& valuesVector)
{
    ingestVector(valuesVector);
    runVector();
}

void FordJohnsonVectorSorter::printResults() const
{
    std::cout << "Before: "; dump(_in);
    std::cout << "After: ";  dump(_out);
}

int FordJohnsonVectorSorter::getTotalComparisons() const
{
    return _comparisons;
}

size_t FordJohnsonVectorSorter::getInputSize() const
{
    return _in.size();
}


