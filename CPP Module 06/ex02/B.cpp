#include "B.hpp"

B::B() {
    // Empty constructor implementation
}

B::B(const B& other) {
    (void)other; // Suppress unused parameter warning
    // Empty copy constructor implementation
}

B& B::operator=(const B& other) {
    if (this != &other) {
        // Empty copy assignment implementation
    }
    return *this;
}

B::~B() {
    // Empty destructor implementation
} 