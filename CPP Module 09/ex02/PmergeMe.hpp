/* ************************************************************************** */
/*                          PmergeMe.hpp (refactored)                          */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <cstddef>
#include <ctime>
#include <string>
#include <iostream>

class PmergeMe
{
public:
    // ==================== CANONICAL FORM ====================
    PmergeMe();
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);
    ~PmergeMe();

    // ==================== PUBLIC API ====================
    void sortVector(std::vector<int>& v);
    void sortDeque(std::deque<int>& d);

    static std::size_t comparisons();
    static void resetComparisons();
    static double us(clock_t s, clock_t e);
    
    // ==================== DEBUG CONTROL ====================
    static void enableDebug(bool enable = true);
    static bool isDebugEnabled();

private:
    // ==================== INTERNAL TYPES ====================
    struct Node
    {
        int value;
        std::size_t id;
        
        Node(int v = 0, std::size_t i = 0) : value(v), id(i) {}
    };

    typedef std::vector<Node> NodeVec;
    typedef std::deque<Node> NodeDeq;
    typedef std::vector<std::pair<std::size_t, std::size_t> > PairVec;

    // ==================== DEBUG UTILITY FUNCTIONS ====================
    static void printIndent();
    static void printSectionHeader(const std::string& title);
    static void printSubHeader(const std::string& title);
    static void printSubFooter();
    static void printContainer(const std::string& name, const std::vector<int>& v);
    static void printNodeContainer(const std::string& name, const NodeVec& v);
    static void printNodeContainer(const std::string& name, const NodeDeq& v);
    static void printPairContainer(const std::string& name, const PairVec& v);

    // ==================== FORD-JOHNSON ALGORITHM DRIVERS ====================
    void fordJohnsonVec(NodeVec& seq);
    void fordJohnsonDeq(NodeDeq& seq);

    // ==================== PHASE HELPERS (VECTOR) ====================
    void pairAndSplit(const NodeVec& input, 
                      NodeVec& smaller, 
                      NodeVec& larger,
                      PairVec& pairs);
    
    void buildMainChain(NodeVec& chain,
                        const NodeVec& smaller, 
                        const NodeVec& larger,
                        const PairVec& pairs,
                        std::size_t& firstSmallId);
    
    void insertRemaining(NodeVec& chain,
                         const NodeVec& smaller, 
                         const PairVec& pairs,
                         std::size_t firstSmallId);

    // ==================== PHASE HELPERS (DEQUE) ====================
    void pairAndSplit(const NodeDeq& input, 
                      NodeDeq& smaller, 
                      NodeDeq& larger,
                      PairVec& pairs);
    
    void buildMainChain(NodeDeq& chain,
                        const NodeDeq& smaller, 
                        const NodeDeq& larger,
                        const PairVec& pairs,
                        std::size_t& firstSmallId);
    
    void insertRemaining(NodeDeq& chain,
                         const NodeDeq& smaller, 
                         const PairVec& pairs,
                         std::size_t firstSmallId);

    // ==================== UTILITY FUNCTIONS ====================
    static bool less(const Node& a, const Node& b);
    
    std::size_t findId(const NodeVec& chain, std::size_t id) const;
    std::size_t findId(const NodeDeq& chain, std::size_t id) const;
    
    std::size_t binaryInsert(NodeVec& chain, const Node& elem,
                             std::size_t low, std::size_t high);
    std::size_t binaryInsert(NodeDeq& chain, const Node& elem,
                             std::size_t low, std::size_t high);
    
    std::vector<std::size_t> generateJacobsthalOrder(std::size_t n) const;

    // ==================== STATIC STATE ====================
    static std::size_t _cmp;       // Global comparison counter
    static std::size_t _idSource;  // Unique id generator
    static int _debug_depth;       // Track recursion depth
    static bool _debug_enabled;    // Debug output control
};

#endif /* PMERGEME_HPP */
