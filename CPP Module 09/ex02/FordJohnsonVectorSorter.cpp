#include "FordJohnsonVectorSorter.hpp"

#include <iostream>
#include <vector>
#include <stdexcept>
#include <map>
#include <algorithm>

// Internal vector types
typedef std::vector<int> VBlock;
typedef std::vector<VBlock> VBlocks;
typedef VBlocks::iterator VBlocksIt;
struct VPair { VBlock left; VBlock right; };
typedef std::vector<VPair> VPairs;
typedef VPairs::iterator VPairsIt;

// Comparator for VBlock using first element; optionally counts comparisons via external counter
struct VBlockLess
{
    int* counter;
    VBlockLess(): counter(0) {}
    explicit VBlockLess(int* c): counter(c) {}
    bool operator()(const VBlock& a, const VBlock& b) const
    {
        if (counter) ++(*counter);
        return a[0] < b[0];
    }
};

class InsertionScheduleVec
{
public:
    std::vector<int> forVector(int n)
    {
        // Direct generator of insertion order equivalent to previous Jacobsthal expansion
        const int limit = n + 1;
        std::vector<int> order;
        int a = 0, b = 1;
        while (b < limit)
        {
            for (int k = b; k > a; --k) order.push_back(k - 1);
            int next = b + 2 * a; a = b; b = next;
        }
        for (int k = limit - 1; k > a; --k) order.push_back(k - 1);
        return order;
    }
};

class VectorPipeline
{
public:
    VectorPipeline(): _comparisons(0) {} // constructor

    VBlocks& input() { return _in; }
    VBlocks& output() { return _out; }
    void resetCounter() { _comparisons = 0; }
    int count() const { return _comparisons; }

    VBlocks sort(VBlocks& seq) { return doSort(seq); }

    void dump(const VBlocks& data) const
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

private:
    struct PairRec { VBlock left; VBlock right; int leftId; int rightId; };

    // New helper that carries element IDs alongside blocks to keep metadata external
    VBlocks doSortWithIds(VBlocks& elements, const std::vector<int>& elementIds, std::vector<int>& outIds)
    {
        if (elements.size() < 2)
        {
            outIds = elementIds; // identity mapping at leaf
            return elements;
        }

        // Handle odd tail
        VBlock odd; int oddId = -1;
        const bool hasOdd = (elements.size() % 2 != 0);
        if (hasOdd)
        {
            odd = elements.back(); // keep as pure number block
            oddId = elementIds.back();
        }

        // Pairing with inline swap and record pair metadata
        std::vector<PairRec> grouped;
        VBlocksIt it = elements.begin();
        VBlocksIt end = elements.end();
        std::vector<int>::const_iterator idIt = elementIds.begin();
        while (it != end && (it + 1) != end)
        {
            PairRec pr; pr.left = *it; pr.right = *(it + 1); pr.leftId = *idIt; pr.rightId = *(idIt + 1);
            if (pr.left[0] > pr.right[0]) { VBlock tmp = pr.left; pr.left = pr.right; pr.right = tmp; int tid = pr.leftId; pr.leftId = pr.rightId; pr.rightId = tid; }
            _comparisons++;
            grouped.push_back(pr);
            it += 2; idIt += 2;
        }

        // Extract right-hand chain and recurse
        VBlocks biggersBlocks; std::vector<int> biggersIds;
        for (size_t gi = 0; gi < grouped.size(); ++gi) { biggersBlocks.push_back(grouped[gi].right); biggersIds.push_back(grouped[gi].rightId); }
        std::vector<int> sortedBiggersIds;
        biggersBlocks = doSortWithIds(biggersBlocks, biggersIds, sortedBiggersIds);

        // Build mapping from rightId to pair index for O(1) partner lookup
        std::map<int, size_t> rightIdToPairIdx;
        for (size_t idx = 0; idx < grouped.size(); ++idx) rightIdToPairIdx[grouped[idx].rightId] = idx;

        // Insertion order plan
        const int chainSize = static_cast<int>(biggersBlocks.size());
        InsertionScheduleVec schedule; std::vector<int> plan = schedule.forVector(hasOdd ? chainSize + 1 : chainSize);

        // Perform binary insertion using indices and ids kept in parallel
        // Maintain ids vector aligned with biggersBlocks
        std::vector<int> chainIds = sortedBiggersIds;
        for (size_t pi = 0; pi < plan.size(); ++pi)
        {
            VBlocksIt limit; VBlock target; int targetId;
            if (plan[pi] == chainSize)
            {
                target = odd; targetId = oddId; limit = biggersBlocks.end();
            }
            else
            {
                limit = biggersBlocks.begin() + plan[pi];
                int upperId = chainIds[plan[pi]];
                std::map<int, size_t>::iterator found = rightIdToPairIdx.find(upperId);
                if (found == rightIdToPairIdx.end()) throw std::invalid_argument("Invalid state: missing unsorted partner");
                const PairRec& pr = grouped[found->second];
                target = pr.left; targetId = pr.leftId;
            }
            VBlockLess comp(&_comparisons);
            VBlocksIt lo = std::lower_bound(biggersBlocks.begin(), limit, target, comp);
            // Insert block and its id at the same position
            size_t insertPos = static_cast<size_t>(lo - biggersBlocks.begin());
            biggersBlocks.insert(lo, target);
            chainIds.insert(chainIds.begin() + insertPos, targetId);
        }

        outIds = chainIds;
        return biggersBlocks;
    }

    // tagPairs, mateOf, and tagPositions were previously separate; logic moved to doSort/doSortWithIds

    VBlocks doSort(VBlocks& elements)
    {
        // Build initial element IDs aligned with input blocks
        std::vector<int> initialIds;
        initialIds.reserve(elements.size());
        for (size_t i = 0; i < elements.size(); ++i) initialIds.push_back(static_cast<int>(i));
        std::vector<int> outIds;
        return doSortWithIds(elements, initialIds, outIds);
    }

private:
    VBlocks _in;
    VBlocks _out;
    int _comparisons;
};

struct FordJohnsonVectorSorter::Impl
{
    VectorPipeline vec; // 

    static void ingestVector(const std::vector<int>& values, VectorPipeline& vectorPipeline)
    {
        for (size_t i = 0; i < values.size(); ++i)
        {
            VBlock valueBlock; valueBlock.push_back(values[i]);
            vectorPipeline.input().push_back(valueBlock);
        }
    }

    void runVector()
    {
        vec.resetCounter();
        vec.output() = vec.sort(vec.input());
    }

    void print()
    {
        std::cout << "Before: "; vec.dump(vec.input());
        std::cout << "After: ";  vec.dump(vec.output());
    }
};

FordJohnsonVectorSorter::FordJohnsonVectorSorter(): _p(new Impl) {}

FordJohnsonVectorSorter::~FordJohnsonVectorSorter() { delete _p; }

FordJohnsonVectorSorter::FordJohnsonVectorSorter(const FordJohnsonVectorSorter& other)
    : _p(new Impl)
{
    // Deep copy: re-ingest other input to replicate state
    _p->vec.input().clear();
    _p->vec.output().clear();
    VBlocks srcIn = const_cast<FordJohnsonVectorSorter&>(other)._p->vec.input();
    for (VBlocksIt it = srcIn.begin(); it != srcIn.end(); ++it) _p->vec.input().push_back(*it);
    VBlocks srcOut = const_cast<FordJohnsonVectorSorter&>(other)._p->vec.output();
    for (VBlocksIt it = srcOut.begin(); it != srcOut.end(); ++it) _p->vec.output().push_back(*it);
}

FordJohnsonVectorSorter& FordJohnsonVectorSorter::operator=(const FordJohnsonVectorSorter& rhs)
{
    if (this != &rhs)
    {
        VBlocks srcIn = const_cast<FordJohnsonVectorSorter&>(rhs)._p->vec.input();
        VBlocks srcOut = const_cast<FordJohnsonVectorSorter&>(rhs)._p->vec.output();
        _p->vec.input().clear();
        _p->vec.output().clear();
        for (VBlocksIt it = srcIn.begin(); it != srcIn.end(); ++it) _p->vec.input().push_back(*it);
        for (VBlocksIt it = srcOut.begin(); it != srcOut.end(); ++it) _p->vec.output().push_back(*it);
    }
    return *this;
}

void FordJohnsonVectorSorter::performSort(const std::vector<int>& valuesVector)
{
    _p->vec.input().clear();
    _p->vec.output().clear();
    Impl::ingestVector(valuesVector, _p->vec);
    _p->runVector();
}

void FordJohnsonVectorSorter::printResults() const
{
    const_cast<FordJohnsonVectorSorter::Impl*>(_p)->print();
}

int FordJohnsonVectorSorter::getTotalComparisons() const
{
    return _p->vec.count();
}

size_t FordJohnsonVectorSorter::getInputSize() const
{
    return _p->vec.input().size();
}


