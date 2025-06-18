#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <algorithm>
#include <stdexcept>
#include <limits>

class Span {
private:
    unsigned int _maxSize;                            // Maximum size of the span
    std::vector<int> _numbers;                        // Vector to hold the numbers

public:
    // Orthodox Canonical Form
    Span();                                           // Default constructor
    Span(unsigned int N);                             // Constructor with size parameter
    Span(const Span& other);                          // Copy constructor
    Span& operator=(const Span& other);               // Assignment operator
    ~Span();                                          // Destructor

    // Member functions
    void addNumber(int number);                       // Add a single number to the span
    template<typename Iterator>                       // Add a range of numbers using iterators
    void addRange(Iterator begin, Iterator end);      
    unsigned int shortestSpan() const;                // Find the shortest span
    unsigned int longestSpan() const;                 // Find the longest span

    // Exception classes
    class SpanFullException : public std::exception { // Exception for full span
    public:
        virtual const char* what() const throw();
    };

    class NoSpanException : public std::exception {   // Exception for no span available
    public:
        virtual const char* what() const throw();
    };

    class InvalidRangeException : public std::exception { // Exception for invalid iterator range
    public:
        virtual const char* what() const throw();
    };

    class InvalidSizeException : public std::exception { // Exception for invalid span size
    public:
        virtual const char* what() const throw();
    };

    class DefaultConstructionException : public std::exception { // Exception for default construction
    public:
        virtual const char* what() const throw();
    };
};

// Template implementation must be in header
template<typename Iterator>
void Span::addRange(Iterator begin, Iterator end) {
    // Defensive check for null-like iterators (not always reliable)
    if (begin == Iterator() || end == Iterator())
        throw InvalidRangeException();

    // Check for empty range
    if (begin == end)
        throw InvalidRangeException();

    // First, try to calculate the distance between iterators
    // This will throw if the range is invalid
    try {
        size_t count = 0;
        Iterator it = begin;
        while (it != end) {
            ++it;
            ++count;
            if (count > _maxSize) // Safety check to prevent infinite loops
                throw InvalidRangeException();
        }

        if (_numbers.size() + count > _maxSize)
            throw SpanFullException();

        // If we get here, the range is valid, so we can safely insert
        while (begin != end) {
            _numbers.push_back(*begin);
            ++begin;
        }
    } catch (const std::exception&) {
        throw InvalidRangeException();
    }
}

#endif // SPAN_HPP 