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
    // Count only the key (value) comparison.
    if (a.value != b.value) {
        ++_cmp;
        return a.value < b.value;
    }
    // Equal values: tie-break by id (deterministic), but don't count it.
    return a.id < b.id;
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

// 1) Collect remaining smalls (exclude the one already placed first)
NodeVec remaining;
remaining.reserve(smaller.size());
for (std::size_t i = 0; i < smaller.size(); ++i)
if (smaller[i].id != firstSmallId)
remaining.push_back(smaller[i]);

if (_debug_enabled) {
printIndent();
std::cout << "[LIST] remaining elements to insert:" << std::endl;
printNodeContainer("remaining", remaining);
}
if (remaining.empty()) { if (_debug_enabled) printSubFooter(); return; }

// 2) Build a fast test: which small IDs are paired?
//    (paired small ids are the 'first' components in pairs)
std::vector<std::size_t> pairedSmallIds;
pairedSmallIds.reserve(pairs.size());
for (std::size_t p = 0; p < pairs.size(); ++p)
pairedSmallIds.push_back(pairs[p].first);



// 3) Split 'remaining' into: indices of paired smalls, and the (optional) odd index
std::vector<std::size_t> pairedIdx; pairedIdx.reserve(remaining.size());
std::size_t oddIdx = static_cast<std::size_t>(-1);
for (std::size_t i = 0; i < remaining.size(); ++i) {
if (containsId(pairedSmallIds, remaining[i].id))
pairedIdx.push_back(i);
else
oddIdx = i; // there can be at most one odd
}
const bool hasOdd = (oddIdx != static_cast<std::size_t>(-1));

// 4) Jacobsthal order ONLY over the paired positions (0..pairedIdx.size()-1),
//    then map back to 'remaining' via pairedIdx[]
std::vector<std::size_t> base = generateJacobsthalOrder(pairedIdx.size());

std::vector<std::size_t> finalOrder; finalOrder.reserve(remaining.size());
if (!base.empty()) {
// First Jacobsthal element
finalOrder.push_back(pairedIdx[base[0]]);
// Then the odd (if it exists)
if (hasOdd) finalOrder.push_back(oddIdx);
// Then the rest of Jacobsthal over paired
for (std::size_t k = 1; k < base.size(); ++k)
finalOrder.push_back(pairedIdx[base[k]]);
} else {
// No paired left ⇒ only odd (or nothing)
if (hasOdd) finalOrder.push_back(oddIdx);
}

if (_debug_enabled) {
printIndent();
std::cout << "[DATA] Insertion order (paired Jacobsthal + odd after first): [";
for (std::size_t i = 0; i < finalOrder.size(); ++i) {
if (i) std::cout << ", ";
std::cout << finalOrder[i];
}
std::cout << "]" << std::endl;
}

// 5) Do the bounded binary inserts
for (std::size_t step = 0; step < finalOrder.size(); ++step)
{
std::size_t ridx = finalOrder[step];
if (ridx >= remaining.size()) continue;

const Node& elem = remaining[ridx];
if (_debug_enabled) {
printIndent();
std::cout << "[LOOP] Inserting element " << elem.value
<< "(" << elem.id << ") from remaining index " << ridx << std::endl;
}

// Upper bound = position of its paired larger (if any); otherwise end
std::size_t pairedPos = chain.size();
for (std::size_t p = 0; p < pairs.size(); ++p) {
if (pairs[p].first == elem.id) {
pairedPos = findId(chain, pairs[p].second);
if (_debug_enabled) {
printIndent();
std::cout << "[TARGET] Paired larger position = "
   << (pairedPos == chain.size() ? -1 : (int)pairedPos)
   << std::endl;
}
break;
}
}
std::size_t high = (pairedPos != chain.size()) ? pairedPos : chain.size();
if (_debug_enabled) {
printIndent();
std::cout << "[SEARCH] Binary insert bounds: [0, " << high << ")" << std::endl;
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

std::vector<std::size_t> PmergeMe::generateJacobsthalOrder(std::size_t n) const
{
    std::vector<std::size_t> order;
    if (n == 0) return order;

    // Jacobsthal numbers J(0)=0, J(1)=1, J(k)=J(k-1)+2*J(k-2)
    std::vector<std::size_t> J; 
    J.push_back(0); 
    J.push_back(1);
    while (J.back() < n) 
        J.push_back(J.back() + 2 * J[J.size() - 2]);

    // Find k with J[k] < = n <= J[k+1]
    std::size_t k = J.size() - 2; // because J.back() >= n

    std::vector<bool> used(n, false);
    // Insert in DESCENDING blocks: from min(J(t+1)-1, n-1) down to J(t)-1
    for (std::size_t t = k; t >= 1; --t) {
        std::size_t upper = std::min(n - 1, J[t + 1] - 1);
        std::size_t lower = (J[t] == 0) ? 0 : J[t] - 1;

        for (std::size_t i = upper + 1; i-- > lower; ) {
            if (i < n && !used[i]) { order.push_back(i); used[i] = true; }
            if (i == 0) break; // prevent size_t underflow
        }
        if (t == 1) break;
    }

    // Safety: append any indices not yet used (should be none except possibly 0)
    for (std::size_t i = n; i-- > 0; )
        if (!used[i]) order.push_back(i);

    return order;
}

bool PmergeMe::containsId(const std::vector<std::size_t>& vec, std::size_t id) {
    for (std::size_t i = 0; i < vec.size(); ++i)
        if (vec[i] == id) return true;
    return false;
}
