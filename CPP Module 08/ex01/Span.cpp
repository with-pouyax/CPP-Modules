#include "Span.hpp"

// Orthodox Canonical Form
Span::Span() {
    throw DefaultConstructionException();
}

Span::Span(unsigned int N) : _maxSize(N) {
    if (N == 0)
        throw InvalidSizeException();
}


// Copy constructor
Span::Span(const Span& other) : _maxSize(other._maxSize), _numbers(other._numbers) {}


// Copy assignment operator
Span& Span::operator=(const Span& other) {
    if (this != &other) {
        _maxSize = other._maxSize;
        _numbers = other._numbers;
    }
    return *this;
}

Span::~Span() {}

//--------------------------------

// Member functions
void Span::addNumber(int number) {
    if (_numbers.size() >= _maxSize)
        throw SpanFullException();
    try {
        _numbers.push_back(number); // add the number to the end of the vector
    } catch (const std::bad_alloc&) {
        throw MemoryAllocationException();
    }
}

unsigned int Span::shortestSpan() const {
    if (_numbers.size() < 2) // if there are less than 2 numbers, there is no span
        throw NoSpanException();
    
    std::vector<int> sorted = _numbers;
    std::sort(sorted.begin(), sorted.end()); // it sorts the vector in ascending order (smaller to bigger)
    
    unsigned int minSpan = std::numeric_limits<unsigned int>::max(); //std::numeric_limits<unsigned int>::max() is the maximum value of an unsigned int
                                                                     // we need it as a base to start comparing the spans and we set it to the maximum value
    for (size_t i = 1; i < sorted.size(); ++i) {                    // we compare the span between the current number and the previous one
                                                                    // we used unsigned int because the span is always positive and we can have a bigger range than int
        unsigned int span = static_cast<unsigned int>(sorted[i] - sorted[i-1]); // we check the span between each current number and the previous one
                                                                                //  we cast it because
        if (span < minSpan)                                                     // if the span is smaller than the minimum span, we update the minimum span
            minSpan = span;
    }
    return minSpan;
}

unsigned int Span::longestSpan() const {
    if (_numbers.size() < 2)
        throw NoSpanException();
    
    std::vector<int> sorted = _numbers;                   
    std::sort(sorted.begin(), sorted.end());                          // we sort the vector in ascending order
    
    return static_cast<unsigned int>(sorted.back() - sorted.front()); // we return the difference between the last and the first element of the vector
}

// Exception implementations
const char* Span::SpanFullException::what() const throw() {
    return "Span is full";
}

const char* Span::NoSpanException::what() const throw() {
    return "No span can be found";
}

const char* Span::InvalidRangeException::what() const throw() {
    return "wrong iterator range";
}

const char* Span::InvalidSizeException::what() const throw() {
    return "Invalid span size: size must be greater than 0";
}

const char* Span::DefaultConstructionException::what() const throw() {
    return "Default construction of Span is not allowed";
}

const char* Span::MemoryAllocationException::what() const throw() {
    return "Memory allocation failed";
} 