/* ************************************************************************** */
/*                          PmergeMe.hpp (refactored)                          */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <cstddef>
#include <ctime>

class PmergeMe
{
public:
    /*-- canonical form --*/
    PmergeMe();
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);
    ~PmergeMe();

    /*-- public API --*/
    void              sortVector(std::vector<int>& v);
    void              sortDeque (std::deque<int>&  d);

    static std::size_t comparisons();
    static void        resetComparisons();
    static double      us(clock_t s, clock_t e);

private:
    /*-- internal node with stable id --*/
    struct Node
    {
        int          value;
        std::size_t  id;
        Node(int v = 0, std::size_t i = 0) : value(v), id(i) {}
    };

    typedef std::vector<Node> NodeVec;
    typedef std::deque<Node>  NodeDeq;
    typedef std::vector<std::pair<std::size_t,std::size_t> > PairVec;

    /*-- top-level drivers (vector / deque) --*/
    void fordJohnsonVec(NodeVec& seq);
    void fordJohnsonDeq(NodeDeq& seq);

    /*-- phase helpers (vector) --*/
    void pairAndSplit (const NodeVec& in, NodeVec& small, NodeVec& large,
                       PairVec& pairs);
    void buildMainChain(NodeVec& chain,
                        const NodeVec& small, const NodeVec& large,
                        const PairVec& pairs,
                        std::size_t& firstSmallId);
    void insertRemaining(NodeVec& chain,
                         const NodeVec& small, const PairVec& pairs,
                         std::size_t firstSmallId);

    /*-- phase helpers (deque) --*/
    void pairAndSplit (const NodeDeq& in, NodeDeq& small, NodeDeq& large,
                       PairVec& pairs);
    void buildMainChain(NodeDeq& chain,
                        const NodeDeq& small, const NodeDeq& large,
                        const PairVec& pairs,
                        std::size_t& firstSmallId);
    void insertRemaining(NodeDeq& chain,
                         const NodeDeq& small, const PairVec& pairs,
                         std::size_t firstSmallId);

    /*-- low-level utils (++comparison counter) --*/
    static bool        less(const Node& a, const Node& b);
    std::size_t        locateId(const NodeVec& c, std::size_t id) const;
    std::size_t        locateId(const NodeDeq& c, std::size_t id) const;
    std::size_t        binInsertRange(NodeVec& c,const Node& e,
                                      std::size_t lo,std::size_t hi);
    std::size_t        binInsertRange(NodeDeq& c,const Node& e,
                                      std::size_t lo,std::size_t hi);
    std::vector<std::size_t> generateJacobsthal(std::size_t n) const;

    /*-- static state --*/
    static std::size_t _cmp;       // global comparison counter
    static std::size_t _idSource;  // unique id generator
};

#endif /* PMERGEME_HPP */
