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
// it takes a form name and a target and returns a pointer to a new AForm object based on the form name
AForm* Intern::makeForm(const std::string& formName, const std::string& target) {
    // Structure to hold form types and their creation functions
    struct FormType {
        std::string name;                       // we store the form name
        
        // (*create) means we are making a variable called create that is a pointer to a function
        // AForm* means the function returns a pointer to an AForm object
        // (const std::string&) means the function takes a const reference to a std::string
        AForm* (*create)(const std::string&);   // we store the form creation function
    };


    // here we make a variable called forms and by [] we mean it is an array
    // this array contains FormType objects as its elements
    // we save our 3 forms names and their creation functions in this array
    // bellow we are makeing what called - FUNCTION POINTER TABLE -
    static const FormType forms[] = {
        {std::string("presidential pardon"), &Intern::createPresidential}, //first element name is "presidential pardon" and the creation function is &Intern::createPresidential
        {std::string("robotomy request"), &Intern::createRobotomy}, //second element name is "robotomy request" and the creation function is &Intern::createRobotomy
        {std::string("shrubbery creation"), &Intern::createShrubbery} //third element name is "shrubbery creation" and the creation function is &Intern::createShrubbery
    };
    static const int numForms = 3; //by static This is created once, and reused every time. It lives for the entire life of the program.

    // we loop through the array and check if the form name fromName we received matches the name of one of the forms in the array
    for (int i = 0; i < numForms; ++i) {
        if (formName == forms[i].name) {
            try {
                AForm* form = (forms[i].create)(target); // we call the creation function from our array
                std::cout << "Intern creates " << form->getName() << std::endl; // we print a message that the intern creates the form
                return form; // we return the form
            }
            // we will go to catch if we fail to allocate memory in the creation function
            catch (FormAllocationException& e) {
                throw; // it calls rethrow, means I'm catching the exception here, but I'm not handling it. Just pass it on to the next catch outside. 
            }
        }
    }

    // If form type not found, throw exception
    throw Intern::UnknownFormException();
} 