#ifndef INTERN_HPP
#define INTERN_HPP

#include "AForm.hpp"
#include <string>

class Intern {
private:

    // Static helper functions for form creation
    static AForm* createPresidential(const std::string& target);
    static AForm* createRobotomy(const std::string& target);
    static AForm* createShrubbery(const std::string& target);

public:

    // Orthodox Canonical Form
    Intern();
    Intern(const Intern& other);
    Intern& operator=(const Intern& other);
    ~Intern();

    // Main functionality
    // we make a form with the name and target that we recieve as parameters
    AForm* makeForm(const std::string& formName, const std::string& target);

    // Exception class for unknown form
    // we throw this exception if the form name is not found
    class UnknownFormException : public std::exception {
    public:
        virtual const char* what() const throw();
    };
};

#endif // INTERN_HPP 