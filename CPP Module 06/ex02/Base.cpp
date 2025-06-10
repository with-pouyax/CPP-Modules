#include "Base.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <new>

Base* generate(void) {
    
    // srand(seed) sets the starting point for the random number generator
    // so imagine we have srand(42), then each time we call std::rand(), it will return a different number starting from 42
    // now why we have a static bool here ?
    // we used time(NULL) which returns us the number of seconds since the epoch
    // then we cast it to unsigned int
    // ***** we have to know that time(NULL) is changing every second.
    // so since multiple calls will happen in less than a second, multiple ran(), will return the same number
    // because they had the same seed
    //by this static bool, we ensure that the seed is only set once
    static bool seeded = false;
    if (!seeded) { 
        // time(NULL) return type is time_t it can be casted implicitly to unsigned int but we do it explicitly for clarity
        std::srand(static_cast<unsigned int>(std::time(NULL)));
        seeded = true;
    }

    // Generate a random number between 0 and 2
    int random = std::rand() % 3;

    try {
        switch (random) {
            case 0:
                return new A(); // since A is inherited from Base, the pointer type is Base* but the object type is A*
            case 1:
                return new B();
            case 2:
                return new C();
            default:
                return NULL;
        }
    } catch (const std::bad_alloc& e) {
        std::cerr << "Memory allocation failed: " << e.what() << std::endl;
        return NULL;
    }
}

void identify(Base* p) { // here we recieve a pointer to a Base object
    if (p == NULL) {
        std::cerr << "Error: NULL pointer passed to identify" << std::endl;
        return;
    }

    if (dynamic_cast<A*>(p))
        std::cout << "A" << std::endl;
    else if (dynamic_cast<B*>(p))
        std::cout << "B" << std::endl;
    else if (dynamic_cast<C*>(p))
        std::cout << "C" << std::endl;
    else
        std::cerr << "Error: Unknown type" << std::endl;
}

void identify(Base& p) { // here we recieve a reference to a Base object
                         // so we can't check if it's NULL
    try {
        (void)dynamic_cast<A&>(p); // since a reference can't be NULL, in case of failure, dynamic_cast will throw a bad_cast exception
        std::cout << "A" << std::endl;
        return;
    } catch (const std::bad_cast&) {} // if the cast fails, we catch the exception and do nothing
    
    try {
        (void)dynamic_cast<B&>(p);
        std::cout << "B" << std::endl;
        return;
    } catch (const std::bad_cast&) {}
    
    try {
        (void)dynamic_cast<C&>(p);
        std::cout << "C" << std::endl;
        return;
    } catch (const std::bad_cast&) {
        std::cerr << "Error: Unknown type" << std::endl;
    }
} 