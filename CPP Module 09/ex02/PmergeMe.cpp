/* ************************************************************************** */
/*                          PmergeMe.cpp (refactored)                          */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <algorithm>   // std::swap
#include <iostream>

// ==================== STATIC DATA ====================
std::size_t PmergeMe::_cmp = 0;
std::size_t PmergeMe::_idSource = 0;

// ==================== UTILITY FUNCTIONS ====================
bool PmergeMe::less(const Node& a, const Node& b)
{
    std::cout << "Comparing: " << a.value << " vs " << b.value << '\n';

    ++_cmp;  // Count every comparison
    if (a.value != b.value)
        return a.value < b.value;
    return a.id < b.id;              // Tie-break
}

std::size_t PmergeMe::comparisons()
{
    return _cmp;
}

void PmergeMe::resetComparisons()
{
    _cmp = 0;
}

double PmergeMe::us(clock_t s, clock_t e)
{
    return static_cast<double>(e - s) * 1e6 / CLOCKS_PER_SEC;
}

// ==================== CANONICAL FORM ====================
PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe&) {}

PmergeMe& PmergeMe::operator=(const PmergeMe&)
{
    return *this;
}

PmergeMe::~PmergeMe() {}

// ==================== PUBLIC API ====================
void PmergeMe::sortVector(std::vector<int>& v)
{
    NodeVec nodes;
    nodes.reserve(v.size());
    
    for (std::size_t i = 0; i < v.size(); ++i)
        nodes.push_back(Node(v[i], _idSource++));
    
    fordJohnsonVec(nodes);
    
    for (std::size_t i = 0; i < v.size(); ++i)
        v[i] = nodes[i].value;
}

void PmergeMe::sortDeque(std::deque<int>& d)
{
    NodeDeq nodes;
    
    for (std::size_t i = 0; i < d.size(); ++i)
        nodes.push_back(Node(d[i], _idSource++));
    
    fordJohnsonDeq(nodes);
    
    for (std::size_t i = 0; i < d.size(); ++i)
        d[i] = nodes[i].value;
}

// ==================== FORD-JOHNSON ALGORITHM (VECTOR) ====================
// - first we get the size of the sequence and store it in n
// - if the size is less than or equal to 1, we return
// - if the size is equal to 2, we compare the two elements and swap them if the second element is less than the first
// - we create two vectors, smaller and larger, and a vector of pairs
// - we call the pairAndSplit function to split the sequence into smaller and larger vectors and pairs
// - so after the pairAndSplit function call, smaller will be [1, 3, 5, 7] and larger will be [2, 4, 6, 8] and smaller will be [1, 2, 3, 4] and larger will be [5, 6, 7, 8]
// - and pairs will be [(1, 2), (3, 4), (5, 6), (7, 8)].
// - we call the fordJohnsonVec function recursively on the larger vector until we get to the base case, which is when the size is less than or equal to 1
// - then first we create a vector called chain
// - now we initialize a variable called firstSmallId to 0.
// - this variable will be used to store the id of the first element of the smaller vector.
// - now we call buildMainChain function to build the main chain
// - by building the main chain
void PmergeMe::fordJohnsonVec(NodeVec& seq)
{
    const std::size_t n = seq.size();
    
    if (n <= 1) return;
    if (n == 2)
    {
        if (less(seq[1], seq[0]))
            std::swap(seq[0], seq[1]);
        return;
    }

    NodeVec smaller, larger;
    PairVec pairs;
    pairAndSplit(seq, smaller, larger, pairs);

    // so now we have
    // seq = [1, 2, 3, 4, 5, 6, 7, 8]
    // smaller = [1, 3, 5, 7]
    // larger = [2, 4, 6, 8]
    // pairs = [(1, 2), (3, 4), (5, 6), (7, 8)]

    fordJohnsonVec(larger);           // Recursion on larger half

    NodeVec chain;
    std::size_t firstSmallId = 0;
    buildMainChain(chain, smaller, larger, pairs, firstSmallId);
    insertRemaining(chain, smaller, pairs, firstSmallId);

    seq.swap(chain);
}

// ==================== FORD-JOHNSON ALGORITHM (DEQUE) ====================
void PmergeMe::fordJohnsonDeq(NodeDeq& seq)
{
    const std::size_t n = seq.size();
    
    if (n <= 1) return;
    if (n == 2)
    {
        if (less(seq[1], seq[0]))
            std::swap(seq[0], seq[1]);
        return;
    }

    NodeDeq smaller, larger;
    PairVec pairs;
    pairAndSplit(seq, smaller, larger, pairs);

    fordJohnsonDeq(larger);           // Recursion on larger half

    NodeDeq chain;
    std::size_t firstSmallId = 0;
    buildMainChain(chain, smaller, larger, pairs, firstSmallId);
    insertRemaining(chain, smaller, pairs, firstSmallId);

    seq.swap(chain);
}

// ==================== PHASE 1: PAIR & SPLIT ====================
void PmergeMe::pairAndSplit(const NodeVec& input,
                            NodeVec& smaller, NodeVec& larger, PairVec& pairs)
{
    const std::size_t pairCount = input.size() / 2; // we get the pair count by dividing the size of the input vector by 2
    smaller.reserve(pairCount); // we reserve the size of the smaller vector to the pair count
    larger.reserve(pairCount); // we reserve the size of the larger vector to the pair count

    for (std::size_t i = 0; i < pairCount; ++i) // we loop the size of the pair count
    {
        Node a = input[2 * i], b = input[2 * i + 1]; // in each iteration, we make two nodes a and b
                                                     // we store the values of the input vector at index 2 * i and 2 * i + 1 
                                                     // if i = 0, a = input[0] and b = input[1]
                                                     // if i = 1, a = input[2] and b = input[3]
        if (less(b, a))                         // we compare the values of the two nodes
            std::swap(a, b);
        smaller.push_back(a);                     // we push the smaller node to the smaller vector
        larger.push_back(b);                      // we push the larger node to the larger vector
        // so we push the smaller node to the smaller vector and the larger node to the larger vector

        pairs.push_back(std::make_pair(a.id, b.id));
        // so here we push the id of the smaller node and the id of the larger node to the pairs vector
        // so pairs = [(1, 2), (3, 4), (5, 6), (7, 8)]
    }
    
    if (input.size() % 2) // if input size is odd, we push the last element to the smaller vector
        smaller.push_back(input.back());
}

void PmergeMe::pairAndSplit(const NodeDeq& input,
                            NodeDeq& smaller, NodeDeq& larger, PairVec& pairs)
{
    const std::size_t pairCount = input.size() / 2;
    
    for (std::size_t i = 0; i < pairCount; ++i)
    {
        Node a = input[2 * i], b = input[2 * i + 1];
        if (less(b, a))
            std::swap(a, b);
        smaller.push_back(a);
        larger.push_back(b);
        pairs.push_back(std::make_pair(a.id, b.id));
    }
    
    if (input.size() % 2)
        smaller.push_back(input.back());
}

// ==================== PHASE 2: MAIN CHAIN ====================
void PmergeMe::buildMainChain(NodeVec& chain,
                              const NodeVec& smaller, const NodeVec& larger,
                              const PairVec& pairs,
                              std::size_t& firstSmallId)
{
    // Find smaller paired with minimum larger (= larger[0])
    const std::size_t firstLargeId = larger[0].id; // we get the id of the first element of the larger vector
    for (std::size_t i = 0; i < pairs.size(); ++i) // we loop the size of the pairs vector
    {
        if (pairs[i].second == firstLargeId) // we check if the second element of the pair is equal to the first element of the larger vector
        {
            firstSmallId = pairs[i].first;
            break; // we break the loop if we find the first element of the larger vector
        }
    }

    // Push that smaller first
    for (std::size_t i = 0; i < smaller.size(); ++i) // we loop the size of the smaller vector
    {
        if (smaller[i].id == firstSmallId) // we check if the id of the smaller vector is equal to the first element of the smaller vector
        {
            chain.push_back(smaller[i]); // we push the smaller vector to the end of the chain vector
            break;
        }
    }

    // Then the entire sorted larger list
    chain.insert(chain.end(), larger.begin(), larger.end());
}

void PmergeMe::buildMainChain(NodeDeq& chain,
                              const NodeDeq& smaller, const NodeDeq& larger,
                              const PairVec& pairs,
                              std::size_t& firstSmallId)
{
    const std::size_t firstLargeId = larger[0].id;
    for (std::size_t i = 0; i < pairs.size(); ++i)
    {
        if (pairs[i].second == firstLargeId)
        {
            firstSmallId = pairs[i].first;
            break;
        }
    }

    for (std::size_t i = 0; i < smaller.size(); ++i)
    {
        if (smaller[i].id == firstSmallId)
        {
            chain.push_back(smaller[i]);
            break;
        }
    }

    chain.insert(chain.end(), larger.begin(), larger.end());
}

// ==================== PHASE 3: REMAINING INSERTS ====================
void PmergeMe::insertRemaining(NodeVec& chain,
                               const NodeVec& smaller, const PairVec& pairs,
                               std::size_t firstSmallId)
{
    // Gather the smalls that still need to be inserted
    NodeVec remaining;
    remaining.reserve(smaller.size());
    
    for (std::size_t i = 0; i < smaller.size(); ++i)
    {
        if (smaller[i].id != firstSmallId)
            remaining.push_back(smaller[i]);
    }

    if (remaining.empty())
        return;

    // Ford-Johnson insertion order
    std::vector<std::size_t> order = generateJacobsthalOrder(remaining.size());

    for (std::size_t k = 0; k < order.size(); ++k)
    {
        std::size_t idx = order[k];
        if (idx >= remaining.size())
            continue;
            
        const Node& elem = remaining[idx];

        // Find the paired larger element to determine optimal search bounds
        std::size_t pairedPos = chain.size();
        for (std::size_t p = 0; p < pairs.size(); ++p)
        {
            if (pairs[p].first == elem.id)
            {
                pairedPos = findId(chain, pairs[p].second);
                break;
            }
        }

        // Ford-Johnson optimal insertion: use the position of paired element as upper bound
        std::size_t high = (pairedPos != chain.size()) ? pairedPos : chain.size();
        binaryInsert(chain, elem, 0, high);
    }
}

void PmergeMe::insertRemaining(NodeDeq& chain,
                               const NodeDeq& smaller, const PairVec& pairs,
                               std::size_t firstSmallId)
{
    NodeDeq remaining;
    for (std::size_t i = 0; i < smaller.size(); ++i)
    {
        if (smaller[i].id != firstSmallId)
            remaining.push_back(smaller[i]);
    }

    if (remaining.empty())
        return;

    std::vector<std::size_t> order = generateJacobsthalOrder(remaining.size());

    for (std::size_t k = 0; k < order.size(); ++k)
    {
        std::size_t idx = order[k];
        if (idx >= remaining.size())
            continue;
            
        const Node& elem = remaining[idx];

        // Find the paired larger element to determine optimal search bounds
        std::size_t pairedPos = chain.size();
        for (std::size_t p = 0; p < pairs.size(); ++p)
        {
            if (pairs[p].first == elem.id)
            {
                pairedPos = findId(chain, pairs[p].second);
                break;
            }
        }

        // Ford-Johnson optimal insertion: use the position of paired element as upper bound
        std::size_t high = (pairedPos != chain.size()) ? pairedPos : chain.size();
        binaryInsert(chain, elem, 0, high);
    }
}

// ==================== UTILITY FUNCTIONS ====================
std::size_t PmergeMe::findId(const NodeVec& chain, std::size_t id) const
{
    for (std::size_t i = 0; i < chain.size(); ++i)
    {
        if (chain[i].id == id)
            return i;
    }
    return chain.size();
}

std::size_t PmergeMe::findId(const NodeDeq& chain, std::size_t id) const
{
    for (std::size_t i = 0; i < chain.size(); ++i)
    {
        if (chain[i].id == id)
            return i;
    }
    return chain.size();
}

std::size_t PmergeMe::binaryInsert(NodeVec& chain, const Node& elem,
                                   std::size_t low, std::size_t high)
{
    while (low < high)
    {
        std::size_t mid = (low + high) / 2;
        if (less(elem, chain[mid]))
            high = mid;
        else
            low = mid + 1;
    }
    chain.insert(chain.begin() + low, elem);
    return low;
}

std::size_t PmergeMe::binaryInsert(NodeDeq& chain, const Node& elem,
                                   std::size_t low, std::size_t high)
{
    while (low < high)
    {
        std::size_t mid = (low + high) / 2;
        if (less(elem, chain[mid]))
            high = mid;
        else
            low = mid + 1;
    }
    chain.insert(chain.begin() + low, elem);
    return low;
}

std::vector<std::size_t> PmergeMe::generateJacobsthalOrder(std::size_t n) const
{
    std::vector<std::size_t> order;
    if (n == 0)
        return order;

    // Generate Jacobsthal numbers: J(n) = J(n-1) + 2*J(n-2)
    std::vector<std::size_t> jacobsthal;
    jacobsthal.push_back(0);  // J(0) = 0
    jacobsthal.push_back(1);  // J(1) = 1
    
    while (jacobsthal.back() < n)
        jacobsthal.push_back(jacobsthal.back() + 2 * jacobsthal[jacobsthal.size() - 2]);

    // Ford-Johnson insertion order: use Jacobsthal numbers as insertion points
    std::vector<bool> used(n, false);
    
    // Start with the largest Jacobsthal number that fits
    for (std::size_t i = jacobsthal.size() - 1; i > 0; --i)
    {
        std::size_t idx = jacobsthal[i] - 1;  // Convert to 0-based index
        if (idx < n && !used[idx])
        {
            order.push_back(idx);
            used[idx] = true;
        }
    }
    
    // Add remaining indices in order
    for (std::size_t i = 0; i < n; ++i)
    {
        if (!used[i])
            order.push_back(i);
    }

    return order;
}


