/* ************************************************************************** */
/*                          PmergeMe.cpp (Phase 1)                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>

/* ---------- file-local helpers: printing ---------- */

static void printIntVec(const std::vector<int>& v) {
    std::cout << '[';
    for (std::size_t i = 0; i < v.size(); ++i) {
        if (i) std::cout << ", ";
        std::cout << v[i];
    }
    std::cout << ']';
}

static void printPairList(const std::vector< std::vector<int> >& pairs) {
    std::cout << '[';
    for (std::size_t i = 0; i < pairs.size(); ++i) {
        if (i) std::cout << ", ";
        std::cout << '[' << pairs[i][0] << ", " << pairs[i][1] << ']';
    }
    std::cout << ']';
}

/* Print a list of groups; each group is an even-length flat vector, which we
** render as a list of 2-sized pairs (e.g. [1,3,8,9] -> [[1,3], [8,9]]).
*/
static void printGroupList(const std::vector< std::vector<int> >& groups) {
    std::cout << '[';
    for (std::size_t g = 0; g < groups.size(); ++g) {
        if (g) std::cout << ", ";
        std::cout << '[';
        const std::vector<int>& grp = groups[g];
        for (std::size_t i = 0; i + 1 < grp.size(); i += 2) {
            if (i) std::cout << ", ";
            std::cout << '[' << grp[i] << ", " << grp[i + 1] << ']';
        }
        std::cout << ']';
    }
    std::cout << ']';
}

/* ************************************************************************** */
/*                                PmergeMe                                    */
/* ************************************************************************** */

std::size_t PmergeMe::_cmp = 0;
bool        PmergeMe::_debug_enabled = false;

void PmergeMe::enableDebug(bool enable) { _debug_enabled = enable; }
bool PmergeMe::isDebugEnabled() { return _debug_enabled; }

std::size_t PmergeMe::comparisons() { return _cmp; }
void        PmergeMe::resetComparisons() { _cmp = 0; }

// Add method to clear leftovers
void PmergeMe::clearLeftovers() { _leftovers.clear(); }

// Add method to get leftovers
const std::vector< std::pair<int, std::vector<int> > >& PmergeMe::getLeftovers() const {
    return _leftovers;
}

double PmergeMe::us(clock_t s, clock_t e) {
    return static_cast<double>(e - s) * 1e6 / CLOCKS_PER_SEC;
}

/* --------- canonical --------- */
PmergeMe::PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe&) {}
PmergeMe& PmergeMe::operator=(const PmergeMe&) { return *this; }
PmergeMe::~PmergeMe() {}

/* ************************************************************************** */
/*                         Phase 1: pairing + grouping                         */
/* ************************************************************************** */

/* Increase counter and return a<b. */
static bool less_incr(std::size_t& counter, int a, int b) {
    ++counter;
    return a < b;
}

void PmergeMe::sortVector(std::vector<int>& v)
{
    /* Phase 1 only: build & sort groups by rightmost elements; do not modify v. */
    if (_debug_enabled) {
        std::cout << "[Depth 0] Input: ";
        printIntVec(v);
        std::cout << '\n';
    }

    // Clear any previous leftovers
    _leftovers.clear();

    // ----- Depth 0: make sorted pairs from input -----
    std::vector< std::vector<int> > pairs;
    pairs.reserve(v.size() / 2);

    std::size_t startCmp = _cmp;

    for (std::size_t i = 0; i + 1 < v.size(); i += 2) {
        int a = v[i];
        int b = v[i + 1];
        if (less_incr(_cmp, b, a)) { // compare once to sort the pair
            int t = a; a = b; b = t;
        }
        std::vector<int> p(2);
        p[0] = a; p[1] = b;
        pairs.push_back(p);
    }

    bool hasLeftover0 = (v.size() % 2) != 0;
    int  leftover0    = hasLeftover0 ? v.back() : 0;

    // Store depth 0 leftover
    if (hasLeftover0) {
        std::vector<int> leftoverVec;
        leftoverVec.push_back(leftover0);
        _leftovers.push_back(std::make_pair(0, leftoverVec));
    }

    if (_debug_enabled) {
        std::cout << "[Depth 0] Pairs: ";
        printPairList(pairs);
        std::cout << '\n';
        if (hasLeftover0) {
            std::cout << "[Depth 0] Leftover: [" << leftover0 << "]\n";
        } else {
            std::cout << "[Depth 0] Leftover: []\n";
        }
        // Optional: per-depth comparison count for pair formation
        std::cout << "[Depth 0] Comparisons (pairing): "
                  << (_cmp - startCmp) << '\n';
    }

    // If there are 0 or 1 pairs, baseline is reached immediately after depth 0.
    if (pairs.size() <= 1U) {
        if (_debug_enabled) {
            if (pairs.empty())
                std::cout << "[Depth 0] Baseline reached (no pairs)\n";
            else
                std::cout << "[Depth 1] Baseline reached\n";
        }
        return; // Phase 1 ends
    }

    // ----- Depth >= 1: recursively group adjacent groups, ordered by rightmost -----
    std::vector< std::vector<int> > curr = pairs;
    int depth = 1;

    while (curr.size() > 1U) {
        if (_debug_enabled) {
            if (depth == 1)
                std::cout << "[Depth " << depth << "] Input pairs: ";
            else
                std::cout << "[Depth " << depth << "] Input groups: ";
            if (depth == 1) printPairList(curr); else printGroupList(curr);
            std::cout << '\n';
        }

        std::size_t cmpAtDepthStart = _cmp;

        // Pair consecutive groups, compare rightmost (last element) to order them.
        std::vector< std::vector<int> > next;
        next.reserve(curr.size() / 2);

        std::vector< std::vector<int> > sortedSequenceForPrint; // flattened pairs in the order produced at this depth

        for (std::size_t i = 0; i + 1 < curr.size(); i += 2) {
            const std::vector<int>& A = curr[i];
            const std::vector<int>& B = curr[i + 1];
            int rightA = A.empty() ? 0 : A[A.size() - 1];
            int rightB = B.empty() ? 0 : B[B.size() - 1];

            bool A_before_B = !less_incr(_cmp, rightB, rightA); // A goes first if rightA <= rightB
            const std::vector<int>& first  = A_before_B ? A : B;
            const std::vector<int>& second = A_before_B ? B : A;

            // merged group for the next depth
            std::vector<int> merged;
            merged.reserve(first.size() + second.size());
            for (std::size_t k = 0; k < first.size(); ++k)  merged.push_back(first[k]);
            for (std::size_t k = 0; k < second.size(); ++k) merged.push_back(second[k]);
            next.push_back(merged);

            // build the "sorted pairs/groups" flat sequence for printing
            // (render as consecutive pairs, in the new order)
            for (std::size_t k = 0; k + 1 < first.size(); k += 2) {
                std::vector<int> p(2);
                p[0] = first[k]; p[1] = first[k + 1];
                sortedSequenceForPrint.push_back(p);
            }
            for (std::size_t k = 0; k + 1 < second.size(); k += 2) {
                std::vector<int> p(2);
                p[0] = second[k]; p[1] = second[k + 1];
                sortedSequenceForPrint.push_back(p);
            }
        }

        bool hasLeftover = (curr.size() % 2) != 0;
        std::vector<int> leftoverGroup;
        if (hasLeftover) {
            leftoverGroup = curr.back();
            // Store leftover at this depth
            _leftovers.push_back(std::make_pair(depth, leftoverGroup));
        }

        if (_debug_enabled) {
            if (depth == 1)
                std::cout << "[Depth " << depth << "] Sorted pairs: ";
            else
                std::cout << "[Depth " << depth << "] Sorted groups: ";

            printPairList(sortedSequenceForPrint);
            std::cout << '\n';

            if (hasLeftover) {
                if (depth == 1) {
                    std::cout << "[Depth " << depth << "] Leftover: ";
                    printPairList(std::vector< std::vector<int> >(1, leftoverGroup));
                    std::cout << '\n';
                } else {
                    std::cout << "[Depth " << depth << "] Leftover: ";
                    printGroupList(std::vector< std::vector<int> >(1, leftoverGroup));
                    std::cout << '\n';
                }
            } else {
                std::cout << "[Depth " << depth << "] Leftover: []\n";
            }

            std::cout << "[Depth " << depth << "] Comparisons: "
                      << (_cmp - cmpAtDepthStart) << '\n';

            // "containers at the end of each depth" -> groups that will be the input of the next depth
            std::cout << "[Depth " << depth << "] Groups for next depth: ";
            printGroupList(next);
            std::cout << '\n';
        }

        curr.swap(next);
        ++depth;
    }

    // Baseline reached (only one group remains)
    if (_debug_enabled) {
        std::cout << "[Depth " << depth << "] Baseline reached\n";
    }

    // Call recursive function to go back through depths with leftovers
    if (!curr.empty()) {
        _mergeInsertionPhase(curr[0], depth - 1);
    }

    // NOTE: Phase 1 does not reorder 'v'. Later phases would use the grouping to
    // do the merge-insertion; here we stop after producing/printing the groups.
}

void PmergeMe::_mergeInsertionPhase(const std::vector<int>& container, int depth) {
    if (_debug_enabled) {
        std::cout << "[Depth " << depth << "] Merge-insertion phase with container: ";
        printGroupList(std::vector< std::vector<int> >(1, container));
        std::cout << '\n';
    }

    // Find leftover for this depth
    std::vector<int> leftoverForDepth;
    for (std::size_t i = 0; i < _leftovers.size(); ++i) {
        if (_leftovers[i].first == depth) {
            leftoverForDepth = _leftovers[i].second;
            break;
        }
    }

    if (!leftoverForDepth.empty()) {
        if (_debug_enabled) {
            std::cout << "[Depth " << depth << "] Adding leftover: ";
            if (depth == 0) {
                // For depth 0, leftover is a single element, not a pair
                std::cout << "[" << leftoverForDepth[0] << "]";
            } else {
                printGroupList(std::vector< std::vector<int> >(1, leftoverForDepth));
            }
            std::cout << '\n';
        }
    } else {
        if (_debug_enabled) {
            std::cout << "[Depth " << depth << "] No leftover for this depth\n";
        }
    }



    // If we're at depth 0, we're done
    if (depth <= 0) {
        if (_debug_enabled) {
            std::cout << "[Depth " << depth << "] Reached depth 0, merge-insertion complete\n";
        }
        return;
    }

    // Recursively call for next depth down
    _mergeInsertionPhase(container, depth - 1);
}
