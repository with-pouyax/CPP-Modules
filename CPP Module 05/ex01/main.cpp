#include "Bureaucrat.hpp"
#include "Form.hpp"
#include <iostream>

int main() {
    try {
        // Test valid form and bureaucrat creation
        std::cout << "Creating a valid form and bureaucrats..." << std::endl;
        Form taxForm("Tax Form", 30, 25); // here we create a form called "Tax Form" with a sign grade of 30 and an execute grade of 25
        Bureaucrat bob("Bob", 50); // here we create a bureaucrat called "Bob" with a grade of 50
        Bureaucrat alice("Alice", 20); // here we create a bureaucrat called "Alice" with a grade of 20

        std::cout << std::endl;
        std::cout << taxForm << std::endl; // here we print the taxForm
        std::cout << "--------------------------------" << std::endl; // here we print a separator
        std::cout << bob << std::endl; // here we print the bob
        std::cout << "--------------------------------" << std::endl; // here we print a separator
        std::cout << alice << std::endl; // here we print the alice
        std::cout << "--------------------------------" << std::endl; // here we print a separator

        // Test signing form - should fail due to low grade
        std::cout << "\nTrying to sign form with Bob (grade 50)..." << std::endl;
        bob.signForm(taxForm);

        // Test signing form - should succeed
        std::cout << "\nTrying to sign form with Alice (grade 20)..." << std::endl;
        alice.signForm(taxForm);

        // Form should be signed now
        std::cout << "\nForm status after Alice's signature attempt:" << std::endl;
        std::cout << taxForm << std::endl;

        // Trying to sign an already signed form
        std::cout << "\nTrying to sign an already signed form with Bob..." << std::endl;
        bob.signForm(taxForm);
    }
    catch (const std::exception& e) { // here we catch too high or too low grade exceptions
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    try {
        // Test form with too high grade
        std::cout << "\nTrying to create a form with sign grade 0..." << std::endl;
        Form invalidForm("Invalid Form", 0, 25); // here we create a form called "Invalid Form" with a sign grade of 0 and an execute grade of 25
    }
    catch (const std::exception& e) { // here we catch too high or too low grade exceptions
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    try {
        // Test form with too low grade
        std::cout << "\nTrying to create a form with execute grade 151..." << std::endl;
        Form invalidForm("Invalid Form", 50, 151); // here we create a form called "Invalid Form" with a sign grade of 50 and an execute grade of 151
    }
    catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
} 