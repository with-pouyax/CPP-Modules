#include "Intern.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include <iostream>

// Orthodox Canonical Form implementations
Intern::Intern() {}

Intern::Intern(const Intern& other) {
    (void)other; // Unused parameter
}

Intern& Intern::operator=(const Intern& other) {
    (void)other; // Unused parameter
    return *this;
}

Intern::~Intern() {}

// Exception implementation
const char* Intern::UnknownFormException::what() const throw() {
    return "Error: Unknown form type requested";
}

// Static helper functions implementation
AForm* Intern::createPresidential(const std::string& target) {
    return new PresidentialPardonForm(target);
}

AForm* Intern::createRobotomy(const std::string& target) {
    return new RobotomyRequestForm(target);
}

AForm* Intern::createShrubbery(const std::string& target) {
    return new ShrubberyCreationForm(target);
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
            AForm* form = (forms[i].create)(target);
            std::cout << "Intern creates " << form->getName() << std::endl;
            return form;
        }
    }

    // If form type not found, throw exception
    throw Intern::UnknownFormException();
} 