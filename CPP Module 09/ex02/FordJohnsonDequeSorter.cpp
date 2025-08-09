#include "FordJohnsonDequeSorter.hpp"

#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <map>

// Internal deque types
typedef std::deque<int> DBlock;
typedef std::deque<DBlock> DBlocks;
typedef DBlocks::iterator DBlocksIt;
struct DPair { DBlock left; DBlock right; };
typedef std::deque<DPair> DPairs;
typedef DPairs::iterator DPairsIt;

class InsertionScheduleDeq
{
public:
    std::deque<int> forDeque(int n)
    {
        const int limit = n + 1;
        std::deque<int> order;
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

class DequePipeline
{
public:
    DBlocks& input() { return _in; }
    DBlocks& output() { return _out; }

    DBlocks sort(DBlocks& seq) { return doSort(seq); }

    void dump(const DBlocks& data) const
    {
        DBlocks::const_iterator a = data.begin(); DBlocks::const_iterator b = data.end();
        for (DBlocks::const_iterator it = a; it != b; ++it)
        {
            for (size_t i = 0; i < it->size(); ++i) std::cout << (*it)[i];
            if (it + 1 != b) std::cout << ", ";
        }
        std::cout << std::endl;
    }

private:
    struct LessDBlock { bool operator()(const DBlock& a, const DBlock& b) const { return a[0] < b[0]; } };
    struct PairRec { DBlock left; DBlock right; int leftId; int rightId; };

    // New helper mirroring vector version: keep metadata (IDs) out of blocks
    DBlocks doSortWithIds(DBlocks& elements, const std::vector<int>& elementIds, std::vector<int>& outIds)
    {
        if (elements.size() < 2)
        {
            outIds = elementIds;
            return elements;
        }

        // Handle odd tail
        DBlock odd; int oddId = -1; const bool hasOdd = (elements.size() % 2 != 0);
        if (hasOdd) { odd = elements.back(); oddId = elementIds.back(); }

        // Pairing with inline swap; record ids
        std::deque<PairRec> grouped;
        DBlocksIt it = elements.begin(); DBlocksIt end = elements.end();
        std::vector<int>::const_iterator idIt = elementIds.begin();
        while (it != end && (it + 1) != end)
        {
            PairRec pr; pr.left = *it; pr.right = *(it + 1); pr.leftId = *idIt; pr.rightId = *(idIt + 1);
            if (pr.left[0] > pr.right[0]) { DBlock t = pr.left; pr.left = pr.right; pr.right = t; int tid = pr.leftId; pr.leftId = pr.rightId; pr.rightId = tid; }
            grouped.push_back(pr);
            it += 2; idIt += 2;
        }

        // Recurse on right-hand chain
        DBlocks biggersBlocks; std::vector<int> biggersIds;
        for (size_t gi = 0; gi < grouped.size(); ++gi) { biggersBlocks.push_back(grouped[gi].right); biggersIds.push_back(grouped[gi].rightId); }
        std::vector<int> sortedBiggersIds;
        biggersBlocks = doSortWithIds(biggersBlocks, biggersIds, sortedBiggersIds);

        // Map for partner lookup
        std::map<int, size_t> rightIdToPairIdx;
        for (size_t idx = 0; idx < grouped.size(); ++idx) rightIdToPairIdx[grouped[idx].rightId] = idx;

        // Build insertion plan
        const int chainSize = static_cast<int>(biggersBlocks.size());
        InsertionScheduleDeq schedule; std::deque<int> plan = schedule.forDeque(hasOdd ? chainSize + 1 : chainSize);

        // Keep ids in parallel with blocks
        std::vector<int> chainIds = sortedBiggersIds;
        for (size_t pi = 0; pi < plan.size(); ++pi)
        {
            DBlocksIt limit; DBlock target; int targetId;
            if (plan[pi] == chainSize)
            { target = odd; targetId = oddId; limit = biggersBlocks.end(); }
            else
            {
                limit = biggersBlocks.begin() + plan[pi];
                int upperId = chainIds[plan[pi]];
                std::map<int, size_t>::iterator found = rightIdToPairIdx.find(upperId);
                if (found == rightIdToPairIdx.end()) throw std::invalid_argument("Invalid state: missing unsorted partner");
                const PairRec& pr = grouped[found->second]; target = pr.left; targetId = pr.leftId;
            }
            LessDBlock less;
            DBlocksIt lo = std::lower_bound(biggersBlocks.begin(), limit, target, less);
            size_t insertPos = static_cast<size_t>(lo - biggersBlocks.begin());
            biggersBlocks.insert(lo, target);
            chainIds.insert(chainIds.begin() + insertPos, targetId);
        }

        outIds = chainIds;
        return biggersBlocks;
    }

    DBlocks doSort(DBlocks& elements)
    {
        std::vector<int> initialIds; initialIds.reserve(elements.size());
        for (size_t i = 0; i < elements.size(); ++i) initialIds.push_back(static_cast<int>(i));
        std::vector<int> outIds; return doSortWithIds(elements, initialIds, outIds);
    }

private:
    DBlocks _in;
    DBlocks _out;
};

struct FordJohnsonDequeSorter::Impl
{
    DequePipeline deq;

    static void ingestDeque(const std::deque<int>& values, DequePipeline& dequePipeline)
    {
        for (size_t i = 0; i < values.size(); ++i)
        {
            DBlock valueBlock; valueBlock.push_back(values[i]);
            dequePipeline.input().push_back(valueBlock);
        }
    }

    void runDeque()
    {
        deq.output() = deq.sort(deq.input());
    }

    void print()
    {
        std::cout << "Before: "; deq.dump(deq.input());
        std::cout << "After: ";  deq.dump(deq.output());
    }
};

FordJohnsonDequeSorter::FordJohnsonDequeSorter(): _p(new Impl) {}

FordJohnsonDequeSorter::~FordJohnsonDequeSorter() { delete _p; }

FordJohnsonDequeSorter::FordJohnsonDequeSorter(const FordJohnsonDequeSorter& other)
    : _p(new Impl)
{
    _p->deq.input().clear();
    _p->deq.output().clear();
    DBlocks srcIn = const_cast<FordJohnsonDequeSorter&>(other)._p->deq.input();
    for (DBlocksIt it = srcIn.begin(); it != srcIn.end(); ++it) _p->deq.input().push_back(*it);
    DBlocks srcOut = const_cast<FordJohnsonDequeSorter&>(other)._p->deq.output();
    for (DBlocksIt it = srcOut.begin(); it != srcOut.end(); ++it) _p->deq.output().push_back(*it);
}

FordJohnsonDequeSorter& FordJohnsonDequeSorter::operator=(const FordJohnsonDequeSorter& rhs)
{
    if (this != &rhs)
    {
        DBlocks srcIn = const_cast<FordJohnsonDequeSorter&>(rhs)._p->deq.input();
        DBlocks srcOut = const_cast<FordJohnsonDequeSorter&>(rhs)._p->deq.output();
        _p->deq.input().clear();
        _p->deq.output().clear();
        for (DBlocksIt it = srcIn.begin(); it != srcIn.end(); ++it) _p->deq.input().push_back(*it);
        for (DBlocksIt it = srcOut.begin(); it != srcOut.end(); ++it) _p->deq.output().push_back(*it);
    }
    return *this;
}

void FordJohnsonDequeSorter::performSort(const std::deque<int>& valuesDeque)
{
    _p->deq.input().clear();
    _p->deq.output().clear();
    Impl::ingestDeque(valuesDeque, _p->deq);
    _p->runDeque();
}

void FordJohnsonDequeSorter::printResults() const
{
    const_cast<FordJohnsonDequeSorter::Impl*>(_p)->print();
}

int FordJohnsonDequeSorter::getTotalComparisons() const
{
    return 0; // Deque pipeline didn’t track comparisons in original split; keep parity with previous class usage
}

size_t FordJohnsonDequeSorter::getInputSize() const
{
    return _p->deq.input().size();
}


