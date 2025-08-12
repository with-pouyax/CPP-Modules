#include "PmergeMe.hpp"
#include <stdexcept>
#include <climits>
#include <cctype>

// Parse a single C-string token into a strictly positive int with overflow checks.
// Rules: only digits allowed (optional single leading '+'), value in (0..INT_MAX].
static int parseStrictPositiveInt(const char* token)
{
    if (token == 0 || *token == '\0') throw std::invalid_argument("Error");

    // Handle optional leading '+'
    size_t index = 0;
    if (token[index] == '+')
    {
        ++index;
        if (token[index] == '\0') throw std::invalid_argument("Error");
    }

    int value = 0;
    for (; token[index] != '\0'; ++index)
    {
        const unsigned char ch = static_cast<unsigned char>(token[index]);
        if (!std::isdigit(ch)) throw std::invalid_argument("Error");
        const int digit = token[index] - '0';
        // Overflow guard: value*10 + digit <= INT_MAX
        if (value > (INT_MAX - digit) / 10) throw std::invalid_argument("Error");
        value = value * 10 + digit;
    }

    if (value <= 0) throw std::invalid_argument("Error");
    return value;
}

void parseArgsToContainers(int argc, char* argv[], std::vector<int>& outVector, std::deque<int>& outDeque)
{
    outVector.clear();
    outDeque.clear();

    for (int i = 1; i < argc; ++i)
    {
        const int n = parseStrictPositiveInt(argv[i]);
        outVector.push_back(n);
        outDeque.push_back(n);
    }
}
