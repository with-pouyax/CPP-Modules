#include "PmergeMe.hpp"
#include <stdexcept>

namespace {
    static int toPositive(const std::string& token)
    {
        if (token.empty() || token.find_first_not_of("0123456789") != std::string::npos)
            throw std::invalid_argument("NaN or Negative: " + token);
        int value = 0;
        for (std::string::size_type i = 0; i < token.size(); ++i)
        {
            value = value * 10 + (token[i] - '0');
            if (value < 0) throw std::invalid_argument("Overflow of: " + token);
        }
        return value;
    }
}

void parseArgsToContainers(int argc, char* argv[], std::vector<int>& outVector, std::deque<int>& outDeque)
{ // argc = number of arguments, argv = array of arguments, outVector = vector to store the values, outDeque = deque to store the values

    outVector.clear(); // clear the vector
    outDeque.clear();  // clear the deque
    for (int i = 1; i < argc; ++i) // loop through the arguments
    {
        const int n = toPositive(std::string(argv[i])); // convert the argument to a positive integer and store it in n
        outVector.push_back(n);                               // push the value to the vector
        outDeque.push_back(n);                                // push the value to the dque
    }
}
