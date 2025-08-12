#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <string>

// Parse argv into positive integers with the same validation rules as before
// (non-digits or negatives rejected; overflow guarded). Throws std::invalid_argument.
void parseArgsToContainers(int argc, char* argv[], std::vector<int>& outVector, std::deque<int>& outDeque);

#endif
