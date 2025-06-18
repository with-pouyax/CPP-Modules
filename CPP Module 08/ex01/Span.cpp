#include "Span.hpp"

// Orthodox Canonical Form
Span::Span() {
    throw DefaultConstructionException();
}

Span::Span(unsigned int N) : _maxSize(N) {
    if (N == 0)
        throw InvalidSizeException();
}

Span::Span(const Span& other) : _maxSize(other._maxSize), _numbers(other._numbers) {}

Span& Span::operator=(const Span& other) {
    if (this != &other) {
        _maxSize = other._maxSize;
        _numbers = other._numbers;
    }
    return *this;
}

Span::~Span() {}

// Member functions
void Span::addNumber(int number) {
    if (_numbers.size() >= _maxSize)
        throw SpanFullException();
    _numbers.push_back(number);
}

unsigned int Span::shortestSpan() const {
    if (_numbers.size() < 2)
        throw NoSpanException();
    
    std::vector<int> sorted = _numbers;
    std::sort(sorted.begin(), sorted.end());
    
    unsigned int minSpan = std::numeric_limits<unsigned int>::max();
    for (size_t i = 1; i < sorted.size(); ++i) {
        unsigned int span = static_cast<unsigned int>(sorted[i] - sorted[i-1]);
        if (span < minSpan)
            minSpan = span;
    }
    return minSpan;
}

unsigned int Span::longestSpan() const {
    if (_numbers.size() < 2)
        throw NoSpanException();
    
    std::vector<int> sorted = _numbers;
    std::sort(sorted.begin(), sorted.end());
    
    return static_cast<unsigned int>(sorted.back() - sorted.front());
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