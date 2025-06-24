#include "Bureaucrat.hpp"

int main() {

    //test default constructor

    /* std::cout << "\nTesting default constructor..." << std::endl;
    Bureaucrat defaultBureaucrat;
    std::cout << defaultBureaucrat << std::endl; */

    try {
        // Test valid bureaucrat creation
        std::cout << "Creating a valid bureaucrat..." << std::endl;
        Bureaucrat bob("Bob", 50);
        std::cout << bob << std::endl;

        // Test incrementing grade
        std::cout << "\nIncrementing Bob's grade..." << std::endl;
        bob.incrementGrade();
        std::cout << bob << std::endl;

        // Test decrementing grade
        std::cout << "\nDecrementing Bob's grade..." << std::endl;
        bob.decrementGrade();
        std::cout << bob << std::endl;

        // Test grade too high exception
        std::cout << "\nTrying to create a bureaucrat with grade 0..." << std::endl;
        Bureaucrat high("High", 0);
    }
    catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }


    try {
        // Test grade too low exception
        std::cout << "\nTrying to create a bureaucrat with grade 151..." << std::endl;
        Bureaucrat low("Low", 151);
    }
    catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    try {
        // Test incrementing highest grade
        std::cout << "\nCreating a bureaucrat with grade 1 and trying to increment..." << std::endl;
        Bureaucrat top("Top", 1);
        std::cout << top << std::endl;
        top.incrementGrade();
    }
    catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    try {
        // Test decrementing lowest grade
        std::cout << "\nCreating a bureaucrat with grade 150 and trying to decrement..." << std::endl;
        Bureaucrat bottom("Bottom", 150);
        std::cout << bottom << std::endl;
        bottom.decrementGrade();
    }
    catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
} 