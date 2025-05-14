#include "Intern.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include <iostream>

// Orthodox Canonical Form implementations

// default constructor
Intern::Intern() {}

// copy constructor
Intern::Intern(const Intern& other) {
    (void)other; // Unused parameter
}

// assignment operator
Intern& Intern::operator=(const Intern& other) {
    (void)other; // Unused parameter because we don't need to copy anything
    return *this;
}

// destructor
Intern::~Intern() {}

//--------------------------------------------------------------------------

// Exception implementation
const char* Intern::UnknownFormException::what() const throw() {
    return "Error: Unknown form type requested";
}

const char* Intern::FormAllocationException::what() const throw() {
    return "Error: Failed to allocate memory for the form";
}

// Static helper functions implementation
//here we create the presidential pardon form with new because we need to return a pointer to the form
AForm* Intern::createPresidential(const std::string& target) {
    try {
        AForm* form = new PresidentialPardonForm(target);
        return form;
    }
    catch (std::bad_alloc&) {
        throw FormAllocationException();
    }
}

AForm* Intern::createRobotomy(const std::string& target) {
    try {
        AForm* form = new RobotomyRequestForm(target);
        return form;
    }
    catch (std::bad_alloc&) {
        throw FormAllocationException();
    }
}

AForm* Intern::createShrubbery(const std::string& target) {
    try {
        AForm* form = new ShrubberyCreationForm(target);
        return form;
    }
    catch (std::bad_alloc&) {
        throw FormAllocationException();
    }
}

// Form creation implementation
AForm* Intern::makeForm(const std::string& formName, const std::string& target) {
    // Structure to hold form types and their creation functions
    struct FormType {
        const char* name;
        AForm* (*create)(const std::string&);
    };

    // Array of form types and their creators
    static const FormType forms[] = {
        {"presidential pardon", &Intern::createPresidential},
        {"robotomy request", &Intern::createRobotomy},
        {"shrubbery creation", &Intern::createShrubbery}
    };
    static const int numForms = 3;

    // Find and create the requested form
    for (int i = 0; i < numForms; ++i) {
        if (formName == forms[i].name) {
            try {
                AForm* form = (forms[i].create)(target);
                std::cout << "Intern creates " << form->getName() << std::endl;
                return form;
            }
            catch (FormAllocationException& e) {
                throw; // Re-throw the same exception
            }
        }
    }

    // If form type not found, throw exception
    throw Intern::UnknownFormException();
} 