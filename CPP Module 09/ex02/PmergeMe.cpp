#include "PmergeMe.hpp"
#include <stdexcept>
#include <climits>
#include <cctype>

// Parse a single C-string token into a strictly positive int with overflow checks.
// Rules: only digits allowed (optional single leading '+'), value in (0..INT_MAX].
static int parseStrictPositiveInt(const char* token)
{
    if (token == 0 || *token == '\0') throw std::invalid_argument("Error"); // token = argv, if argv = 0 means there is no argument, if *token = '\0' means the argument is empty

    // Handle optional leading '+'
    size_t index = 0;
    if (token[index] == '+')
    {
        ++index;
        if (token[index] == '\0') throw std::invalid_argument("Error");
    }

    int value = 0;
    for (; token[index] != '\0'; ++index)                                    // we loop through the argument
    {
        const unsigned char ch = static_cast<unsigned char>(token[index]);   // we save the arguments in ch
                                                                            
        if (!std::isdigit(ch)) throw std::invalid_argument("Error");         // if the argument is not a digit, we throw an error
        const int digit = token[index] - '0';                                // we convert the argument to an integer
        // Overflow guard: value*10 + digit <= INT_MAX
        if (value > (INT_MAX - digit) / 10) throw std::invalid_argument("Error"); // if the value is greater than INT_MAX, we throw an error
        value = value * 10 + digit;                                               // we convert the argument to an integer
    }

    if (value <= 0) throw std::invalid_argument("Error");
    return value;
}

void parseArgsToContainers(int argc, char* argv[], std::vector<int>& outVector, std::deque<int>& outDeque)
{
    outVector.clear();  // we clear the vector because we want to make sure it is empty
    outDeque.clear();   // we clear the deque because we want to make sure it is empty

    for (int i = 1; i < argc; ++i)         // we start from 1 because the first argument is the program name
    {
        const int n = parseStrictPositiveInt(argv[i]);  // we parse the argument and store it in n
        outVector.push_back(n);
        outDeque.push_back(n);
    }
}
