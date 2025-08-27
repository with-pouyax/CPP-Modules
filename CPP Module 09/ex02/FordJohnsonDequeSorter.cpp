#include "FordJohnsonDequeSorter.hpp"

#include <iostream>
#include <map>
#include <algorithm>

FordJohnsonDequeSorter::FordJohnsonDequeSorter()
    : _in(), _out(), _comparisons(0)
{}
FordJohnsonDequeSorter::~FordJohnsonDequeSorter() {}

FordJohnsonDequeSorter::FordJohnsonDequeSorter(const FordJohnsonDequeSorter& other)
    : _in(other._in), _out(other._out), _comparisons(other._comparisons)
{
}

FordJohnsonDequeSorter& FordJohnsonDequeSorter::operator=(const FordJohnsonDequeSorter& rhs)
{
    if (this != &rhs)
    {
        _in = rhs._in;
        _out = rhs._out;
        _comparisons = rhs._comparisons;
    }
    return *this;
}

void FordJohnsonDequeSorter::ingestDeque(const std::deque<int>& values)
{
    _in.clear();
    for (size_t i = 0; i < values.size(); ++i)
    {
        DBlock valueBlock; valueBlock.push_back(values[i]);
        _in.push_back(valueBlock);
    }
}

void FordJohnsonDequeSorter::runDeque()
{
    _comparisons = 0;
    _out.clear();
    DBlocks tmp = _in;
    _out = doSort(tmp);
}

void FordJohnsonDequeSorter::dump(const DBlocks& data) const
{
    DBlocks::const_iterator a = data.begin(); DBlocks::const_iterator b = data.end();
    for (DBlocks::const_iterator it = a; it != b; ++it)
    {
        for (size_t i = 0; i < it->size(); ++i) std::cout << (*it)[i];
        if (it + 1 != b) std::cout << " ";
    }
    std::cout << std::endl;
}

std::vector<int> FordJohnsonDequeSorter::buildJacobsthalInsertionOrder(int n)
{
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

FordJohnsonDequeSorter::DBlocksIt FordJohnsonDequeSorter::lowerBound(DBlocksIt first, DBlocksIt last, const DBlock& value)
{
    typedef std::iterator_traits<DBlocksIt>::difference_type Diff;
    Diff count = last - first;
    while (count > 0)
    {
        Diff step = count / 2;
        DBlocksIt mid = first + step;
        if (isLessFirst(*mid, value))
        {
            first = ++mid;
            count -= step + 1;
        }
        else
        {
            count = step;
        }
    }
    return first;
}

bool FordJohnsonDequeSorter::isLessFirst(const DBlock& a, const DBlock& b)
{
    ++_comparisons;
    return a[0] < b[0];
}

FordJohnsonDequeSorter::DBlocks FordJohnsonDequeSorter::doSortWithIds(DBlocks& elements, const std::vector<int>& elementIds, std::vector<int>& outIds)
{
    return doSortWithIds(elements, elementIds, outIds, 0);
}

FordJohnsonDequeSorter::DBlocks FordJohnsonDequeSorter::doSortWithIds(DBlocks& elements, const std::vector<int>& elementIds, std::vector<int>& outIds, int /*depth*/)
{
    if (elements.size() < 2)
    {
        outIds = elementIds;
        return elements;
    }

    DBlock odd; int oddId = -1; const bool hasOdd = (elements.size() % 2 != 0);
    if (hasOdd) { odd = elements.back(); oddId = elementIds.back(); }

    DBlocks smallBlocks; std::vector<int> smallIds;
    DBlocks biggersBlocks; std::vector<int> biggersIds;
    for (size_t i = 0; i + 1 < elements.size(); i += 2)
    {
        DBlock left = elements[i]; int leftId = elementIds[i];
        DBlock right = elements[i + 1]; int rightId = elementIds[i + 1];
        bool leftLessRight = isLessFirst(left, right);
        if (!leftLessRight) { std::swap(left, right); std::swap(leftId, rightId); }
        smallBlocks.push_back(left); smallIds.push_back(leftId);
        biggersBlocks.push_back(right); biggersIds.push_back(rightId);
    }

    std::vector<int> sortedBiggersIds;
    biggersBlocks = doSortWithIds(biggersBlocks, biggersIds, sortedBiggersIds, 1);

    std::map<int, size_t> rightIdToIdx;
    for (size_t idx = 0; idx < biggersIds.size(); ++idx) rightIdToIdx[biggersIds[idx]] = idx;

    const int chainSize = static_cast<int>(biggersBlocks.size());
    std::vector<int> jSeq = buildJacobsthalInsertionOrder(hasOdd ? chainSize + 1 : chainSize);

    std::vector<int> chainIds = sortedBiggersIds;

    for (size_t pi = 0; pi < jSeq.size(); ++pi)
    {
        DBlocksIt limit; DBlock target; int targetId;
        if (jSeq[pi] == chainSize)
        { target = odd; targetId = oddId; limit = biggersBlocks.end(); }
        else
        {
            int upperIdStable = sortedBiggersIds[jSeq[pi]];
            size_t upperPos = 0; while (upperPos < chainIds.size() && chainIds[upperPos] != upperIdStable) ++upperPos;
            if (upperPos >= chainIds.size()) throw std::invalid_argument("Invalid state: missing sorted partner");
            limit = biggersBlocks.begin() + static_cast<std::ptrdiff_t>(upperPos);
            std::map<int, size_t>::iterator found = rightIdToIdx.find(upperIdStable);
            if (found == rightIdToIdx.end()) throw std::invalid_argument("Invalid state: missing unsorted partner");
            size_t idx = found->second; target = smallBlocks[idx]; targetId = smallIds[idx];
        }

        DBlocksIt lo = lowerBound(biggersBlocks.begin(), limit, target);
        size_t insertPos = static_cast<size_t>(lo - biggersBlocks.begin());
        biggersBlocks.insert(lo, target);
        chainIds.insert(chainIds.begin() + insertPos, targetId);
    }

    outIds = chainIds;
    return biggersBlocks;
}

FordJohnsonDequeSorter::DBlocks FordJohnsonDequeSorter::doSort(DBlocks& elements)
{
    std::vector<int> initialIds; initialIds.reserve(elements.size());
    for (size_t i = 0; i < elements.size(); ++i) initialIds.push_back(static_cast<int>(i));
    std::vector<int> outIds; return doSortWithIds(elements, initialIds, outIds);
}

void FordJohnsonDequeSorter::performSort(const std::deque<int>& valuesDeque)
{
    ingestDeque(valuesDeque);
    runDeque();
}

void FordJohnsonDequeSorter::printResults() const
{
    std::cout << "Before: "; dump(_in);
    std::cout << "After: ";  dump(_out);
}

int FordJohnsonDequeSorter::getTotalComparisons() const
{
    return _comparisons;
}

size_t FordJohnsonDequeSorter::getInputSize() const
{
    return _in.size();
}


