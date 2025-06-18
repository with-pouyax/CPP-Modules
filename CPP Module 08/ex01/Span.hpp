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

    // Exception classeses
    // ==========================================================================
    
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
    // ==========================================================================
};

// Template implementation must be in header
template<typename Iterator>
void Span::addRange(Iterator begin, Iterator end) {
    // Iterator() means calling the default constructor of Iterator type
    // since it is empty, it is not a valid iterator (samething like NULL)
    // it is used normally like std::vector<int>::iterator it = std::vector<int>::iterator();
    // When we want to make a a iterator that is not yet connected to a container
    if (begin == Iterator() || end == Iterator()) 
        throw InvalidRangeException();

    // if begin and end are the same, it is an empty range
    if (begin == end)
        throw InvalidRangeException();

    // First, try to calculate the distance between iterators
    // This will throw if the range is invalid
    try {
        size_t count = 0;
        Iterator it = begin;
        while (it != end) {
            ++it; // by ++it 1- increment "it" 2- return the incremented "it" as a reference (no copy)
                  //but by it++ 1- copy "it" to "tmp" 2- increment "it" 3- return "tmp"
                  //like this we avoid copying "it" and "count" each time
            ++count;
            if (count > _maxSize) // because _maxSize can also be == range size
                throw InvalidRangeException();
        }

        if (_numbers.size() + count > _maxSize) //if size of numbers vector (current size) + range size(range size we want to add) > _maxSize mean we don't have enough space to add the range
            throw SpanFullException();

        // If we get here, the range is valid, so we can safely insert
        while (begin != end) {
            _numbers.push_back(*begin);
            ++begin; //  we already pushed the value to the vector, so we can pre-increment the begin iterator
        }
    } catch (const std::exception&) {
        throw InvalidRangeException();
    }
}

#endif // SPAN_HPP 