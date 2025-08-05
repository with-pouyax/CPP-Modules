/* ************************************************************************** */
/*                          PmergeMe.cpp (refactored)                          */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <algorithm>   // std::swap
#include <iostream>
#include <cstdio>      // sprintf

// ==================== STATIC DATA ====================
std::size_t PmergeMe::_cmp = 0;
std::size_t PmergeMe::_idSource = 0;
int PmergeMe::_debug_depth = 0;  // Track recursion depth
bool PmergeMe::_debug_enabled = false;  // Debug output control

// ==================== DEBUG CONTROL ====================
void PmergeMe::enableDebug(bool enable) {
    _debug_enabled = enable;
}

bool PmergeMe::isDebugEnabled() {
    return _debug_enabled;
}

// ==================== DEBUG UTILITY FUNCTIONS ====================
void PmergeMe::printIndent() {
    if (!_debug_enabled) return;
    for (int i = 0; i < _debug_depth; ++i)
        std::cout << "  ";
}

void PmergeMe::printSectionHeader(const std::string& title) {
    if (!_debug_enabled) return;
    printIndent();
    std::cout << "+==============================================================+" << std::endl;
    printIndent();
    std::cout << "| " << title << std::string(60 - title.length(), ' ') << "|" << std::endl;
    printIndent();
    std::cout << "+==============================================================+" << std::endl;
}

void PmergeMe::printSubHeader(const std::string& title) {
    if (!_debug_enabled) return;
    printIndent();
    std::cout << "+--- " << title << std::string(55 - title.length(), '-') << "+" << std::endl;
}

void PmergeMe::printSubFooter() {
    if (!_debug_enabled) return;
    printIndent();
    std::cout << "+" << std::string(58, '-') << "+" << std::endl;
}

void PmergeMe::printContainer(const std::string& name, const std::vector<int>& v) {
    if (!_debug_enabled) return;
    printIndent();
    std::cout << "[BOX] " << name << ": [";
    for (size_t i = 0; i < v.size(); ++i) {
        if (i > 0) std::cout << ", ";
        std::cout << v[i];
    }
    std::cout << "]" << std::endl;
}

void PmergeMe::printNodeContainer(const std::string& name, const NodeVec& v) {
    if (!_debug_enabled) return;
    printIndent();
    std::cout << "[NUM] " << name << ": [";
    for (size_t i = 0; i < v.size(); ++i) {
        if (i > 0) std::cout << ", ";
        std::cout << v[i].value << "(" << v[i].id << ")";
    }
    std::cout << "]" << std::endl;
}

void PmergeMe::printNodeContainer(const std::string& name, const NodeDeq& v) {
    if (!_debug_enabled) return;
    printIndent();
    std::cout << "[NUM] " << name << ": [";
    for (size_t i = 0; i < v.size(); ++i) {
        if (i > 0) std::cout << ", ";
        std::cout << v[i].value << "(" << v[i].id << ")";
    }
    std::cout << "]" << std::endl;
}

void PmergeMe::printPairContainer(const std::string& name, const PairVec& v) {
    if (!_debug_enabled) return;
    printIndent();
    std::cout << "[PAIR] " << name << ": [";
    for (size_t i = 0; i < v.size(); ++i) {
        if (i > 0) std::cout << ", ";
        std::cout << "(" << v[i].first << "," << v[i].second << ")";
    }
    std::cout << "]" << std::endl;
}

// ==================== UTILITY FUNCTIONS ====================
bool PmergeMe::less(const Node& a, const Node& b)
{
    if (_debug_enabled) {
        printIndent();
        //std::cout << "[COMPARE] Comparing: " << a.value << " vs " << b.value << std::endl;
    }

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
    if (_debug_enabled) {
        printSectionHeader("SORT VECTOR");
        printContainer("Input vector", v);
    }
    
    NodeVec nodes;
    nodes.reserve(v.size());
    
    for (std::size_t i = 0; i < v.size(); ++i)
        nodes.push_back(Node(v[i], _idSource++));
    
    printNodeContainer("Initial nodes", nodes);
    
    fordJohnsonVec(nodes);
    
    for (std::size_t i = 0; i < v.size(); ++i)
        v[i] = nodes[i].value;
    
    printContainer("Final sorted vector", v);
    if (_debug_enabled) {
        printIndent();
        std::cout << "[OK] Vector sorting completed" << std::endl;
    }
}

void PmergeMe::sortDeque(std::deque<int>& d)
{
    if (_debug_enabled) {
        printSectionHeader("SORT DEQUE");
    }
    
    NodeDeq nodes;
    
    for (std::size_t i = 0; i < d.size(); ++i)
        nodes.push_back(Node(d[i], _idSource++));
    
    fordJohnsonDeq(nodes);
    
    for (std::size_t i = 0; i < d.size(); ++i)
        d[i] = nodes[i].value;
    
    if (_debug_enabled) {
        printIndent();
        std::cout << "[OK] Deque sorting completed" << std::endl;
    }
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
    ++_debug_depth;
    if (_debug_enabled) {
        {
            char depth_str[32];
            sprintf(depth_str, "%d", _debug_depth);
            printSubHeader(std::string("FORD-JOHNSON VECTOR (Depth ") + depth_str + ")");
        }
        printNodeContainer("Input sequence", seq);
    }
    
    const std::size_t n = seq.size();
    
    if (n <= 1) {
        if (_debug_enabled) {
            printIndent();
            std::cout << "[STOP] Base case: n <= 1, returning" << std::endl;
        }
        --_debug_depth;
        if (_debug_enabled) printSubFooter();
        return;
    }
    if (n == 2)
    {
        if (_debug_enabled) {
            printIndent();
            std::cout << "[LOOP] Base case: n == 2, comparing and swapping if needed" << std::endl;
        }
        if (less(seq[1], seq[0]))
            std::swap(seq[0], seq[1]);
        printNodeContainer("After swap", seq);
        --_debug_depth;
        if (_debug_enabled) printSubFooter();
        return;
    }

    NodeVec smaller, larger;
    PairVec pairs;
    
    if (_debug_enabled) {
        printIndent();
        std::cout << "[LOOP] Calling pairAndSplit..." << std::endl;
    }
    pairAndSplit(seq, smaller, larger, pairs);

    if (_debug_enabled) {
        printIndent();
        std::cout << "[DATA] After pairAndSplit:" << std::endl;
        printNodeContainer("smaller", smaller);
        printNodeContainer("larger", larger);
        printPairContainer("pairs", pairs);
    }

    // so now we have
    // seq = [1, 2, 3, 4, 5, 6, 7, 8]
    // smaller = [1, 3, 5, 7]
    // larger = [2, 4, 6, 8]
    // pairs = [(1, 2), (3, 4), (5, 6), (7, 8)]

    if (_debug_enabled) {
        printIndent();
        std::cout << "[LOOP] Recursively calling fordJohnsonVec on larger..." << std::endl;
    }
    fordJohnsonVec(larger);           // Recursion on larger half
    if (_debug_enabled) {
        printIndent();
        std::cout << "[OK] After recursive call on larger:" << std::endl;
        printNodeContainer("larger (sorted)", larger);
    }

    NodeVec chain;
    std::size_t firstSmallId = 0;
    
    if (_debug_enabled) {
        printIndent();
        std::cout << "🔗 Calling buildMainChain..." << std::endl;
    }
    buildMainChain(chain, smaller, larger, pairs, firstSmallId);
    if (_debug_enabled) {
        printIndent();
        std::cout << "[OK] After buildMainChain:" << std::endl;
        printNodeContainer("chain", chain);
        printIndent();
        std::cout << "[TARGET] firstSmallId: " << firstSmallId << std::endl;
    }
    
    if (_debug_enabled) {
        printIndent();
        std::cout << "🔗 Calling insertRemaining..." << std::endl;
    }
    insertRemaining(chain, smaller, pairs, firstSmallId);
    if (_debug_enabled) {
        printIndent();
        std::cout << "[OK] After insertRemaining:" << std::endl;
        printNodeContainer("final chain", chain);
    }

    seq.swap(chain);
    --_debug_depth;
    if (_debug_enabled) printSubFooter();
}

// ==================== FORD-JOHNSON ALGORITHM (DEQUE) ====================
void PmergeMe::fordJohnsonDeq(NodeDeq& seq)
{
    ++_debug_depth;
    if (_debug_enabled) {
        {
            char depth_str[32];
            sprintf(depth_str, "%d", _debug_depth);
            printSubHeader(std::string("FORD-JOHNSON DEQUE (Depth ") + depth_str + ")");
        }
    }
    
    const std::size_t n = seq.size();
    
    if (n <= 1) {
        if (_debug_enabled) {
            printIndent();
            std::cout << "[STOP] Base case: n <= 1, returning" << std::endl;
        }
        --_debug_depth;
        if (_debug_enabled) printSubFooter();
        return;
    }
    if (n == 2)
    {
        if (_debug_enabled) {
            printIndent();
            std::cout << "[LOOP] Base case: n == 2, comparing and swapping if needed" << std::endl;
        }
        if (less(seq[1], seq[0]))
            std::swap(seq[0], seq[1]);
        --_debug_depth;
        if (_debug_enabled) printSubFooter();
        return;
    }

    NodeDeq smaller, larger;
    PairVec pairs;
    
    if (_debug_enabled) {
        printIndent();
        std::cout << "[LOOP] Calling pairAndSplit..." << std::endl;
    }
    pairAndSplit(seq, smaller, larger, pairs);

    if (_debug_enabled) {
        printIndent();
        std::cout << "[DATA] After pairAndSplit:" << std::endl;
        printIndent();
        std::cout << "   smaller size: " << smaller.size() << ", larger size: " << larger.size() << ", pairs size: " << pairs.size() << std::endl;
    }

    fordJohnsonDeq(larger);           // Recursion on larger half

    NodeDeq chain;
    std::size_t firstSmallId = 0;
    
    if (_debug_enabled) {
        printIndent();
        std::cout << "🔗 Calling buildMainChain..." << std::endl;
    }
    buildMainChain(chain, smaller, larger, pairs, firstSmallId);
    
    if (_debug_enabled) {
        printIndent();
        std::cout << "🔗 Calling insertRemaining..." << std::endl;
    }
    insertRemaining(chain, smaller, pairs, firstSmallId);

    seq.swap(chain);
    --_debug_depth;
    if (_debug_enabled) printSubFooter();
}

// ==================== PHASE 1: PAIR & SPLIT ====================
void PmergeMe::pairAndSplit(const NodeVec& input,
                            NodeVec& smaller, NodeVec& larger, PairVec& pairs)
{
    if (_debug_enabled) {
        printSubHeader("PAIR AND SPLIT");
        printNodeContainer("Input", input);
    }
    
    const std::size_t pairCount = input.size() / 2; // we get the pair count by dividing the size of the input vector by 2
    smaller.reserve(pairCount); // we reserve the size of the smaller vector to the pair count
    larger.reserve(pairCount); // we reserve the size of the larger vector to the pair count

    if (_debug_enabled) {
        printIndent();
        std::cout << "[DATA] pairCount: " << pairCount << std::endl;
    }

    for (std::size_t i = 0; i < pairCount; ++i) // we loop the size of the pair count
    {
        Node a = input[2 * i], b = input[2 * i + 1]; // in each iteration, we make two nodes a and b
                                                     // we store the values of the input vector at index 2 * i and 2 * i + 1 
                                                     // if i = 0, a = input[0] and b = input[1]
                                                     // if i = 1, a = input[2] and b = input[3]
        if (_debug_enabled) {
            printIndent();
            std::cout << "[LOOP] Pair " << i << ": comparing " << a.value << "(" << a.id << ") vs " << b.value << "(" << b.id << ")" << std::endl;
        }
        
        if (less(b, a))                         // we compare the values of the two nodes
            std::swap(a, b);
        smaller.push_back(a);                     // we push the smaller node to the smaller vector
        larger.push_back(b);                      // we push the larger node to the larger vector
        // so we push the smaller node to the smaller vector and the larger node to the larger vector

        pairs.push_back(std::make_pair(a.id, b.id));
        // so here we push the id of the smaller node and the id of the larger node to the pairs vector
        // so pairs = [(1, 2), (3, 4), (5, 6), (7, 8)]
    }
    
    if (input.size() % 2) { // if input size is odd, we push the last element to the smaller vector
        if (_debug_enabled) {
            printIndent();
            std::cout << "[WARN]  Odd size detected, adding last element to smaller" << std::endl;
        }
        smaller.push_back(input.back());
    }
    
    if (_debug_enabled) {
        printIndent();
        std::cout << "[OK] After pairAndSplit:" << std::endl;
        printNodeContainer("smaller", smaller);
        printNodeContainer("larger", larger);
        printPairContainer("pairs", pairs);
        printSubFooter();
    }
}

void PmergeMe::pairAndSplit(const NodeDeq& input,
                            NodeDeq& smaller, NodeDeq& larger, PairVec& pairs)
{
    if (_debug_enabled) {
        printSubHeader("PAIR AND SPLIT (DEQUE)");
    }
    
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
    
    if (_debug_enabled) printSubFooter();
}

// ==================== PHASE 2: MAIN CHAIN ====================
void PmergeMe::buildMainChain(NodeVec& chain,
                              const NodeVec& smaller, const NodeVec& larger,
                              const PairVec& pairs,
                              std::size_t& firstSmallId)
{
    if (_debug_enabled) {
        printSubHeader("BUILD MAIN CHAIN");
        printNodeContainer("smaller", smaller);
        printNodeContainer("larger", larger);
        printPairContainer("pairs", pairs);
    }
    
    // Find smaller paired with minimum larger (= larger[0])
    const std::size_t firstLargeId = larger[0].id; // we get the id of the first element of the larger vector and store it in firstLargeId
    if (_debug_enabled) {
        printIndent();
        std::cout << "[TARGET] firstLargeId: " << firstLargeId << std::endl;
    }
    
    for (std::size_t i = 0; i < pairs.size(); ++i) // we loop the size of the pairs vector
    {
        if (pairs[i].second == firstLargeId) // we check if the second element of the pair is equal to the first element of the larger vector
        {
            firstSmallId = pairs[i].first;
            if (_debug_enabled) {
                printIndent();
                std::cout << "[OK] Found firstSmallId: " << firstSmallId << " at pair index " << i << std::endl;
            }
            break; // we break the loop if we find the first element of the larger vector
        }
    }

    // Push that smaller first
    for (std::size_t i = 0; i < smaller.size(); ++i) // we loop the size of the smaller vector
    {
        if (smaller[i].id == firstSmallId) // we check if the id of the smaller vector is equal to the first element of the smaller vector
        {
            chain.push_back(smaller[i]); // we push the smaller vector to the end of the chain vector
            if (_debug_enabled) {
                printIndent();
                std::cout << "[ADD] Added first small element: " << smaller[i].value << "(" << smaller[i].id << ")" << std::endl;
            }
            break;
        }
    }

    // Then the entire sorted larger list
    chain.insert(chain.end(), larger.begin(), larger.end());
    if (_debug_enabled) {
        printIndent();
        std::cout << "[ADD] Added all larger elements to chain" << std::endl;
        printIndent();
        std::cout << "[OK] Final chain:" << std::endl;
        printNodeContainer("chain", chain);
        printSubFooter();
    }
}

void PmergeMe::buildMainChain(NodeDeq& chain,
                              const NodeDeq& smaller, const NodeDeq& larger,
                              const PairVec& pairs,
                              std::size_t& firstSmallId)
{
    if (_debug_enabled) {
        printSubHeader("BUILD MAIN CHAIN (DEQUE)");
    }
    
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
    
    if (_debug_enabled) printSubFooter();
}

// ==================== PHASE 3: REMAINING INSERTS ====================
void PmergeMe::insertRemaining(NodeVec& chain,
                               const NodeVec& smaller, const PairVec& pairs,
                               std::size_t firstSmallId)
{
    if (_debug_enabled) {
        printSubHeader("INSERT REMAINING");
        printNodeContainer("chain (before)", chain);
        printNodeContainer("smaller", smaller);
        printPairContainer("pairs", pairs);
        printIndent();
        std::cout << "[TARGET] firstSmallId: " << firstSmallId << std::endl;
    }
    
    // Gather the smalls that still need to be inserted
    NodeVec remaining;
    remaining.reserve(smaller.size());
    
    for (std::size_t i = 0; i < smaller.size(); ++i)
    {
        if (smaller[i].id != firstSmallId)
            remaining.push_back(smaller[i]);
    }

    if (_debug_enabled) {
        printIndent();
        std::cout << "[LIST] remaining elements to insert:" << std::endl;
        printNodeContainer("remaining", remaining);
    }

    if (remaining.empty()) {
        if (_debug_enabled) {
            printIndent();
            std::cout << "[OK] No remaining elements to insert" << std::endl;
            printSubFooter();
        }
        return;
    }

    // Ford-Johnson insertion order
    std::vector<std::size_t> order = generateJacobsthalOrder(remaining.size());
    if (_debug_enabled) {
        printIndent();
        std::cout << "[DATA] Jacobsthal insertion order: [";
        for (size_t i = 0; i < order.size(); ++i) {
            if (i > 0) std::cout << ", ";
            std::cout << order[i];
        }
        std::cout << "]" << std::endl;
    }

    for (std::size_t k = 0; k < order.size(); ++k)
    {
        std::size_t idx = order[k];
        if (idx >= remaining.size())
            continue;
            
        const Node& elem = remaining[idx];
        if (_debug_enabled) {
            printIndent();
            std::cout << "[LOOP] Inserting element " << elem.value << "(" << elem.id << ") at index " << idx << std::endl;
        }

        // Find the paired larger element to determine optimal search bounds
        std::size_t pairedPos = chain.size();
        for (std::size_t p = 0; p < pairs.size(); ++p)
        {
            if (pairs[p].first == elem.id)
            {
                pairedPos = findId(chain, pairs[p].second);
                if (_debug_enabled) {
                    printIndent();
                    std::cout << "[TARGET] Found paired element at position " << pairedPos << std::endl;
                }
                break;
            }
        }

        // Ford-Johnson optimal insertion: use the position of paired element as upper bound
        std::size_t high = (pairedPos != chain.size()) ? pairedPos : chain.size();
        if (_debug_enabled) {
            printIndent();
            std::cout << "[SEARCH] Binary insert with bounds: low=0, high=" << high << std::endl;
        }
        binaryInsert(chain, elem, 0, high);
        
        if (_debug_enabled) {
            printIndent();
            std::cout << "[OK] Chain after insertion:" << std::endl;
            printNodeContainer("chain", chain);
        }
    }
    
    if (_debug_enabled) printSubFooter();
}

void PmergeMe::insertRemaining(NodeDeq& chain,
                               const NodeDeq& smaller, const PairVec& pairs,
                               std::size_t firstSmallId)
{
    if (_debug_enabled) {
        printSubHeader("INSERT REMAINING (DEQUE)");
    }
    
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
    
    if (_debug_enabled) printSubFooter();
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
    if (_debug_enabled) {
        printIndent();
        std::cout << "[SEARCH] binaryInsert: inserting " << elem.value << "(" << elem.id << ") with bounds [" << low << ", " << high << ")" << std::endl;
    }
    
    while (low < high)
    {
        std::size_t mid = (low + high) / 2;
        if (_debug_enabled) {
            printIndent();
            std::cout << "  [SEARCH] Comparing with element at mid=" << mid << ": " << chain[mid].value << "(" << chain[mid].id << ")" << std::endl;
        }
        
        if (less(elem, chain[mid]))
            high = mid;
        else
            low = mid + 1;
    }
    
    if (_debug_enabled) {
        printIndent();
        std::cout << "  [OK] Inserting at position " << low << std::endl;
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
    if (_debug_enabled) {
        printIndent();
        std::cout << "[DATA] generateJacobsthalOrder called with n=" << n << std::endl;
    }
    
    std::vector<std::size_t> order;
    if (n == 0)
        return order;

    // Generate Jacobsthal numbers: J(n) = J(n-1) + 2*J(n-2)
    std::vector<std::size_t> jacobsthal;
    jacobsthal.push_back(0);  // J(0) = 0
    jacobsthal.push_back(1);  // J(1) = 1
    
    while (jacobsthal.back() < n)
        jacobsthal.push_back(jacobsthal.back() + 2 * jacobsthal[jacobsthal.size() - 2]);

    if (_debug_enabled) {
        printIndent();
        std::cout << "[DATA] Jacobsthal numbers: [";
        for (size_t i = 0; i < jacobsthal.size(); ++i) {
            if (i > 0) std::cout << ", ";
            std::cout << jacobsthal[i];
        }
        std::cout << "]" << std::endl;
    }

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

    if (_debug_enabled) {
        printIndent();
        std::cout << "[DATA] Generated order: [";
        for (size_t i = 0; i < order.size(); ++i) {
            if (i > 0) std::cout << ", ";
            std::cout << order[i];
        }
        std::cout << "]" << std::endl;
    }
    
    return order;
}


