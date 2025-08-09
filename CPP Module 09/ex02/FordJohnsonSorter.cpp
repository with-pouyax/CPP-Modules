#include "FordJohnsonSorter.hpp"

#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <stdexcept>

// No namespaces per project rules. All helpers are file-local classes.
    typedef std::vector<int> VBlock;
    typedef std::vector<VBlock> VBlocks;
    typedef VBlocks::iterator VBlocksIt;
    struct VPair { VBlock left; VBlock right; };
    typedef std::vector<VPair> VPairs;
    typedef VPairs::iterator VPairsIt;

    typedef std::deque<int> DBlock;
    typedef std::deque<DBlock> DBlocks;
    typedef DBlocks::iterator DBlocksIt;
    struct DPair { DBlock left; DBlock right; };
    typedef std::deque<DPair> DPairs;
    typedef DPairs::iterator DPairsIt;

    class TokenToIntConverter
    {
    public:
        int toPositive(const std::string& token) const
{
    if (token.empty() || token.find_first_not_of("0123456789") != std::string::npos)
        throw std::invalid_argument("NaN or Negative: " + token);
            int value = 0;
            for (std::string::size_type i = 0; i < token.size(); ++i)
    {
                value = value * 10 + (token[i] - '0');
                if (value < 0)
            throw std::invalid_argument("Overflow of: " + token);
    }
            return value;
        }
    };

    

    class InsertionSchedule
    {
    public:
        std::vector<int> forVector(int n)
        {
            const int limit = n + 1;
            std::vector<int> jac; buildJacobsthal(jac, limit);
            std::vector<int> order = expand(jac);
            if (!jac.empty() && jac.back() < limit)
            {
                for (int i = limit - 1; i > jac.back(); --i) order.push_back(i);
            }
            for (size_t i = 0; i < order.size(); ++i) order[i] = order[i] - 1;
            return order;
        }

        std::deque<int> forDeque(int n)
        {
            const int limit = n + 1;
            std::deque<int> jac; buildJacobsthal(jac, limit);
            std::deque<int> order = expand(jac);
            if (!jac.empty() && jac.back() < limit)
            {
                for (int i = limit - 1; i > jac.back(); --i) order.push_back(i);
            }
            for (size_t i = 0; i < order.size(); ++i) order[i] = order[i] - 1;
            return order;
        }

    private:
        void buildJacobsthal(std::vector<int>& seq, int limit)
        {
            seq.clear(); seq.push_back(0); seq.push_back(1);
            while (true) { int next = seq.back() + 2 * seq[seq.size() - 2]; if (next >= limit) break; seq.push_back(next); }
        }
        void buildJacobsthal(std::deque<int>& seq, int limit)
        {
            seq.clear(); seq.push_back(0); seq.push_back(1);
            while (true) { int next = seq.back() + 2 * seq[seq.size() - 2]; if (next >= limit) break; seq.push_back(next); }
        }
        std::vector<int> expand(const std::vector<int>& jac)
        {
            std::vector<int> order; std::vector<int> tmp = jac; if (tmp.size() > 2) tmp.erase(tmp.begin(), tmp.begin() + 2);
            for (size_t i = 0; i < tmp.size(); ++i) { int s = tmp[i]; int e = (i == 0) ? 0 : tmp[i - 1]; for (int p = s; p > e; --p) order.push_back(p);} return order;
        }
        std::deque<int> expand(const std::deque<int>& jac)
        {
            std::deque<int> order; std::deque<int> tmp = jac; if (tmp.size() > 2) tmp.erase(tmp.begin(), tmp.begin() + 2);
            for (size_t i = 0; i < tmp.size(); ++i) { int s = tmp[i]; int e = (i == 0) ? 0 : tmp[i - 1]; for (int p = s; p > e; --p) order.push_back(p);} return order;
        }
    };

    class VectorPipeline
    {
    public:
        VectorPipeline(): _comparisons(0) {}

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
        void tagPairs(VPairs& pairs)
        {
            int idx = 0;
            for (VPairsIt it = pairs.begin(); it != pairs.end(); ++it)
            {
                if (it->left[0] > it->right[0]) { VBlock tmp = it->left; it->left = it->right; it->right = tmp; }
                _comparisons++;
                it->left.push_back(idx); it->right.push_back(idx); ++idx;
            }
        }

        std::vector<int> mateOf(VPairs& pairs, VBlocks& chain, int index, VBlocksIt& upper)
        {
            VBlocksIt it = chain.begin(); while (it != chain.end() && *(it->begin()) != index) ++it; upper = it;
            if (it == chain.end()) throw std::invalid_argument("Invalid state: missing sorted partner");
            VPairsIt pit = pairs.begin(); while (pit != pairs.end() && upper->back() != pit->left.back()) ++pit;
            if (pit == pairs.end()) throw std::invalid_argument("Invalid state: missing unsorted partner");
            pit->left.insert(pit->left.begin(), -1); return pit->left;
        }

        void tagPositions(VBlocks& seq)
        {
            VBlocksIt it = seq.begin(); int pos = 0; while (it != seq.end()) { it->insert(it->begin(), pos); ++it; ++pos; }
        }

        VBlocks doSort(VBlocks& elements)
        {
            if (elements.size() < 2) return elements;

            VBlock odd;
            if (elements.size() % 2 != 0) { odd = elements.back(); odd.insert(odd.begin(), -1); odd.push_back(-1); }

            VPairs grouped;
            VBlocksIt it = elements.begin(); VBlocksIt end = elements.end();
            while (it != end && (it + 1) != end) { VPair p; p.left = *it; p.right = *(it + 1); grouped.push_back(p); it += 2; }

            tagPairs(grouped);

            VBlocks biggers; for (VPairsIt gp = grouped.begin(); gp != grouped.end(); ++gp) biggers.push_back(gp->right);
            biggers = doSort(biggers);
            tagPositions(biggers);

            int chainSize = biggers.size();
            InsertionSchedule schedule; std::vector<int> plan = schedule.forVector(odd.size() > 0 ? biggers.size() + 1 : biggers.size());

            for (size_t i = 0; i < plan.size(); ++i)
            {
                VBlocksIt limit; VBlock target;
                if (plan[i] == chainSize) { target = odd; limit = biggers.end(); }
                else { target = mateOf(grouped, biggers, plan[i], limit); }

                VBlocksIt lo = biggers.begin();
                while (lo < limit)
                {
                    VBlocksIt mid = lo + (limit - lo) / 2;
                    if (target[1] > (*mid)[1]) lo = mid + 1; else limit = mid; _comparisons++;
                }
                biggers.insert(lo, target);
            }

            for (VBlocksIt b = biggers.begin(); b != biggers.end(); ++b) { b->pop_back(); b->erase(b->begin()); }
            return biggers;
        }

    private:
        VBlocks _in;
        VBlocks _out;
        int _comparisons;
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
        void tagPairs(DPairs& pairs)
        {
            int idx = 0; for (DPairsIt it = pairs.begin(); it != pairs.end(); ++it) { if (it->left[0] > it->right[0]) { DBlock t = it->left; it->left = it->right; it->right = t; } it->left.push_back(idx); it->right.push_back(idx); ++idx; }
        }

        std::deque<int> mateOf(DPairs& pairs, DBlocks& chain, int index, DBlocksIt& upper)
        {
            DBlocksIt it = chain.begin(); while (it != chain.end() && *(it->begin()) != index) ++it; upper = it;
            if (it == chain.end()) throw std::invalid_argument("Invalid state: missing sorted partner");
            DPairsIt pit = pairs.begin(); while (pit != pairs.end() && upper->back() != pit->left.back()) ++pit;
            if (pit == pairs.end()) throw std::invalid_argument("Invalid state: missing unsorted partner");
            pit->left.insert(pit->left.begin(), -1); return pit->left;
        }

        void tagPositions(DBlocks& seq)
        {
            DBlocksIt it = seq.begin(); int pos = 0; while (it != seq.end()) { it->insert(it->begin(), pos); ++it; ++pos; }
        }

        DBlocks doSort(DBlocks& elements)
        {
            if (elements.size() < 2) return elements;

            DBlock odd; if (elements.size() % 2 != 0) { odd = elements.back(); odd.insert(odd.begin(), -1); odd.push_back(-1); }
            DPairs grouped; DBlocksIt it = elements.begin(); DBlocksIt end = elements.end(); while (it != end && (it + 1) != end) { DPair p; p.left = *it; p.right = *(it + 1); grouped.push_back(p); it += 2; }
            tagPairs(grouped);
            DBlocks biggers; for (DPairsIt gp = grouped.begin(); gp != grouped.end(); ++gp) biggers.push_back(gp->right);
            biggers = doSort(biggers);
            tagPositions(biggers);

            int chainSize = biggers.size(); InsertionSchedule schedule; std::deque<int> plan = schedule.forDeque(odd.size() > 0 ? biggers.size() + 1 : biggers.size());
            for (size_t i = 0; i < plan.size(); ++i)
            {
                DBlocksIt limit; DBlock target;
                if (plan[i] == chainSize) { target = odd; limit = biggers.end(); }
                else { target = mateOf(grouped, biggers, plan[i], limit); }
                DBlocksIt lo = biggers.begin(); while (lo < limit) { DBlocksIt mid = lo + (limit - lo) / 2; if (target[1] > (*mid)[1]) lo = mid + 1; else limit = mid; } biggers.insert(lo, target);
            }

            for (DBlocksIt b = biggers.begin(); b != biggers.end(); ++b) { b->pop_back(); b->erase(b->begin()); }
            return biggers;
        }

    private:
        DBlocks _in;
        DBlocks _out;
    };

    // Helper to ingest pre-populated integer containers into pipelines.
    static void ingestVector(const std::vector<int>& values, VectorPipeline& vectorPipeline)
    {
        for (size_t i = 0; i < values.size(); ++i)
        {
            VBlock valueBlock; valueBlock.push_back(values[i]);
            vectorPipeline.input().push_back(valueBlock);
        }
    }

    static void ingestDeque(const std::deque<int>& values, DequePipeline& dequePipeline)
    {
        for (size_t i = 0; i < values.size(); ++i)
        {
            DBlock valueBlock; valueBlock.push_back(values[i]);
            dequePipeline.input().push_back(valueBlock);
        }
    }

struct FordJohnsonSorter::Impl
{
    TokenToIntConverter conv;
    InsertionSchedule schedule;
    VectorPipeline vec;
    DequePipeline deq;

    void load(const std::vector<int>& vecValues, const std::deque<int>& deqValues)
    {
        ingestVector(vecValues, vec);
        ingestDeque(deqValues, deq);
    }

    void run()
    {
        vec.resetCounter();
        vec.output() = vec.sort(vec.input());
        deq.output() = deq.sort(deq.input());
    }

    void runVector()
    {
        vec.resetCounter();
        vec.output() = vec.sort(vec.input());
    }

    void runDeque()
    {
        deq.output() = deq.sort(deq.input());
    }

    void print()
    {
        std::cout << "Before: "; vec.dump(vec.input());
        std::cout << "After: ";  vec.dump(vec.output());
    }

    int comparisons() const { return vec.count(); }
    size_t inputSize() { return vec.input().size(); }
};

FordJohnsonSorter::FordJohnsonSorter(): _p(new Impl) {}
FordJohnsonSorter::~FordJohnsonSorter() { delete _p; }

void FordJohnsonSorter::loadInputData(const std::vector<int>& valuesVector, const std::deque<int>& valuesDeque)
{
    _p->load(valuesVector, valuesDeque); 
}

void FordJohnsonSorter::performSortOperations()
{
    _p->run();
}

void FordJohnsonSorter::performVectorSort()
{
    _p->runVector();
}

void FordJohnsonSorter::performDequeSort()
{
    _p->runDeque();
}

void FordJohnsonSorter::performVectorSort(const std::vector<int>& valuesVector)
{
    // Reset and ingest only the vector pipeline; leave deque as-is
    _p->vec.input().clear();    // clear the input vector
    _p->vec.output().clear();   // clear the output vector
    ingestVector(valuesVector, _p->vec); // ingest the vector into the vector pipeline
    _p->runVector();
}

void FordJohnsonSorter::performDequeSort(const std::deque<int>& valuesDeque)
{
    // Reset and ingest only the deque pipeline; leave vector as-is
    _p->deq.input().clear();
    _p->deq.output().clear();
    ingestDeque(valuesDeque, _p->deq);
    _p->runDeque();
}

void FordJohnsonSorter::printResults()
{
    _p->print();
}

int FordJohnsonSorter::getTotalComparisons() const
{
    return _p->comparisons();
}

size_t FordJohnsonSorter::getInputSize() const
{
    return const_cast<FordJohnsonSorter::Impl*>(_p)->inputSize();
}
