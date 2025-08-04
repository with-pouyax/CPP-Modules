/* ************************************************************************** */
/*                          PmergeMe.cpp (refactored)                          */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <algorithm>   // std::swap
#include <iostream>

/*-- static data --*/
std::size_t PmergeMe::_cmp      = 0;
std::size_t PmergeMe::_idSource = 0;

/*-- small utilities --*/
bool PmergeMe::less(const Node& a, const Node& b)
{
	std::cout << "Comparing: " << a.value << " vs " << b.value << '\n';

    if (a.value != b.value)          // value comparison (counts!)
    {
        ++_cmp;
        return a.value < b.value;
    }
    return a.id < b.id;              // tie-break (does NOT count)
}

std::size_t PmergeMe::comparisons()      { return _cmp; }
void        PmergeMe::resetComparisons() { _cmp = 0; }
double      PmergeMe::us(clock_t s,clock_t e)
{ return static_cast<double>(e-s)*1e6/CLOCKS_PER_SEC; }

/*-- canonicals --*/
PmergeMe::PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe&) {}
PmergeMe& PmergeMe::operator=(const PmergeMe&) { return *this; }
PmergeMe::~PmergeMe() {}

/*==============================  PUBLIC  ===================================*/
void PmergeMe::sortVector(std::vector<int>& v)
{
    NodeVec nodes;
    nodes.reserve(v.size());
    for(std::size_t i=0;i<v.size();++i)
        nodes.push_back(Node(v[i],_idSource++));
    fordJohnsonVec(nodes);
    for(std::size_t i=0;i<v.size();++i) v[i]=nodes[i].value;
}

void PmergeMe::sortDeque(std::deque<int>& d)
{
    NodeDeq nodes;
    for(std::size_t i=0;i<d.size();++i)
        nodes.push_back(Node(d[i],_idSource++));
    fordJohnsonDeq(nodes);
    for(std::size_t i=0;i<d.size();++i) d[i]=nodes[i].value;
}

/*===========================  FORD-JOHNSON (vec)  ==========================*/
void PmergeMe::fordJohnsonVec(NodeVec& seq)
{
    const std::size_t n = seq.size();
    if(n<=1) return;
    if(n==2){ if(less(seq[1],seq[0])) std::swap(seq[0],seq[1]); return; }

    NodeVec small,large;
    PairVec pairs;
    pairAndSplit(seq,small,large,pairs);

    fordJohnsonVec(large);           /* recursion on larger half */

    NodeVec chain;
    std::size_t firstSmallId = 0;
    buildMainChain(chain,small,large,pairs,firstSmallId);
    insertRemaining(chain,small,pairs,firstSmallId);

    seq.swap(chain);
}

/*===========================  FORD-JOHNSON (deq)  ==========================*/
void PmergeMe::fordJohnsonDeq(NodeDeq& seq)
{
    const std::size_t n = seq.size();
    if(n<=1) return;
    if(n==2){ if(less(seq[1],seq[0])) std::swap(seq[0],seq[1]); return; }

    NodeDeq small,large;
    PairVec pairs;
    pairAndSplit(seq,small,large,pairs);

    fordJohnsonDeq(large);           /* recursion on larger half */

    NodeDeq chain;
    std::size_t firstSmallId = 0;
    buildMainChain(chain,small,large,pairs,firstSmallId);
    insertRemaining(chain,small,pairs,firstSmallId);

    seq.swap(chain);
}

/*====================  PHASE 1 : PAIR & SPLIT  ============================*/
void PmergeMe::pairAndSplit(const NodeVec& in,
                            NodeVec& small,NodeVec& large,PairVec& pairs)
{
    const std::size_t pairCnt = in.size()/2;
    small.reserve(pairCnt);
    large.reserve(pairCnt);

    for(std::size_t i=0;i<pairCnt;++i){
        Node a=in[2*i], b=in[2*i+1];
        if(less(b,a)) std::swap(a,b);
        small.push_back(a);
        large.push_back(b);
        pairs.push_back(std::make_pair(a.id,b.id));
    }
    if(in.size()%2) small.push_back(in.back());   /* odd element piggy-backs */
}

void PmergeMe::pairAndSplit(const NodeDeq& in,
                            NodeDeq& small,NodeDeq& large,PairVec& pairs)
{
    const std::size_t pairCnt = in.size()/2;
    for(std::size_t i=0;i<pairCnt;++i){
        Node a=in[2*i], b=in[2*i+1];
        if(less(b,a)) std::swap(a,b);
        small.push_back(a);
        large.push_back(b);
        pairs.push_back(std::make_pair(a.id,b.id));
    }
    if(in.size()%2) small.push_back(in.back());
}

/*====================  PHASE 2 : MAIN CHAIN  ==============================*/
void PmergeMe::buildMainChain(NodeVec& chain,
                              const NodeVec& small,const NodeVec& large,
                              const PairVec& pairs,
                              std::size_t& firstSmallId)
{
    /* find smaller paired with minimum larger (= large[0]) */
    const std::size_t firstLargeId = large[0].id;
    for(std::size_t i=0;i<pairs.size();++i)
        if(pairs[i].second==firstLargeId){ firstSmallId=pairs[i].first; break;}

    /* push that smaller first */
    for(std::size_t i=0;i<small.size();++i)
        if(small[i].id==firstSmallId){ chain.push_back(small[i]); break; }

    /* then the entire sorted larger list */
    chain.insert(chain.end(),large.begin(),large.end());
}

void PmergeMe::buildMainChain(NodeDeq& chain,
                              const NodeDeq& small,const NodeDeq& large,
                              const PairVec& pairs,
                              std::size_t& firstSmallId)
{
    const std::size_t firstLargeId = large[0].id;
    for(std::size_t i=0;i<pairs.size();++i)
        if(pairs[i].second==firstLargeId){ firstSmallId=pairs[i].first; break;}

    for(std::size_t i=0;i<small.size();++i)
        if(small[i].id==firstSmallId){ chain.push_back(small[i]); break; }

    chain.insert(chain.end(),large.begin(),large.end());
}

/*====================  PHASE 3 : REMAINING INSERTS  =======================*/
void PmergeMe::insertRemaining(NodeVec& chain,
	const NodeVec& small, const PairVec& pairs,
	std::size_t firstSmallId)
{
/* gather the smalls that still need to be inserted */
NodeVec rest;
rest.reserve(small.size());
for (std::size_t i = 0; i < small.size(); ++i)
	if (small[i].id != firstSmallId)
		rest.push_back(small[i]);

/* Jacobsthal insertion order */
std::vector<std::size_t> order = generateJacobsthal(rest.size());

for (std::size_t k = 0; k < order.size(); ++k)
{
	std::size_t r = order[k];
	if (r >= rest.size())           /* safety-guard */
		continue;
	const Node& elem = rest[r];

	/* upper search bound = location of its paired “large” element */
	std::size_t hi = chain.size();  /* default: whole chain          */
	for (std::size_t p = 0; p < pairs.size(); ++p)
		if (pairs[p].first == elem.id)       /* match on small-id    */
		{
			std::size_t pos = locateId(chain, pairs[p].second);
			if (pos != chain.size())         /* partner already in   */
				hi = pos;                    /* restrict search      */
			break;
		}

	binInsertRange(chain, elem, 0, hi);
}
}

void PmergeMe::insertRemaining(NodeDeq& chain,
	const NodeDeq& small, const PairVec& pairs,
	std::size_t firstSmallId)
{
NodeDeq rest;
for (std::size_t i = 0; i < small.size(); ++i)
	if (small[i].id != firstSmallId)
		rest.push_back(small[i]);

std::vector<std::size_t> order = generateJacobsthal(rest.size());

for (std::size_t k = 0; k < order.size(); ++k)
{
	std::size_t r = order[k];
	if (r >= rest.size())
		continue;
	const Node& elem = rest[r];

	std::size_t hi = chain.size();
	for (std::size_t p = 0; p < pairs.size(); ++p)
		if (pairs[p].first == elem.id)
		{
			std::size_t pos = locateId(chain, pairs[p].second);
			if (pos != chain.size())
				hi = pos;
			break;
		}

	binInsertRange(chain, elem, 0, hi);
}
}


/*=========================  LOW-LEVEL UTILITIES  ==========================*/
std::size_t PmergeMe::locateId(const NodeVec& c,std::size_t id) const
{
    for(std::size_t i=0;i<c.size();++i) if(c[i].id==id) return i;
    return c.size();
}
std::size_t PmergeMe::locateId(const NodeDeq& c,std::size_t id) const
{
    for(std::size_t i=0;i<c.size();++i) if(c[i].id==id) return i;
    return c.size();
}

std::size_t PmergeMe::binInsertRange(NodeVec& c,const Node& e,
                                     std::size_t lo,std::size_t hi)
{
    while(lo<hi){
        std::size_t mid=(lo+hi)/2;
        if(less(e,c[mid])) hi=mid;
        else               lo=mid+1;
    }
    c.insert(c.begin()+lo,e);
    return lo;
}
std::size_t PmergeMe::binInsertRange(NodeDeq& c,const Node& e,
                                     std::size_t lo,std::size_t hi)
{
    while(lo<hi){
        std::size_t mid=(lo+hi)/2;
        if(less(e,c[mid])) hi=mid;
        else               lo=mid+1;
    }
    c.insert(c.begin()+lo,e);
    return lo;
}

std::vector<std::size_t> PmergeMe::generateJacobsthal(std::size_t n) const {
	std::vector<std::size_t> jseq;
	if (n == 0) return jseq;

	// Generate Jacobsthal numbers up to > n
	std::vector<std::size_t> jacob;
	jacob.push_back(0); // not used
	jacob.push_back(1);
	while (jacob.back() < n)
		jacob.push_back(jacob.back() + 2 * jacob[jacob.size() - 2]);

	std::vector<bool> used(n, false);
	for (std::size_t i = jacob.size() - 1; i > 0; --i)
	{
		std::size_t idx = jacob[i];
		if (idx - 1 < n && !used[idx - 1]) {
			jseq.push_back(idx - 1);
			used[idx - 1] = true;
		}
	}

	// Add remaining indices
	for (std::size_t i = 0; i < n; ++i)
		if (!used[i])
			jseq.push_back(i);

	return jseq;
}


