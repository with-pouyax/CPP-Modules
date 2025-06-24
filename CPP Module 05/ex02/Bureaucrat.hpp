#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <string>
#include <iostream>
#include <exception>

// Forward declaration of AForm to avoid circular dependency
class AForm;

class Bureaucrat {
private:
    const std::string _name; 
    int _grade; 

    // Private default constructor
    Bureaucrat();

public:

    // Orthodox Canonical Form
    Bureaucrat(const std::string& name, int grade); // constructor with name and grade
    Bureaucrat(const Bureaucrat& other);            // copy constructor
    Bureaucrat& operator=(const Bureaucrat& other); // assignment operator
    ~Bureaucrat();                              // destructor



    // Getters
    const std::string& getName() const;         // get the name of the bureaucrat
    int getGrade() const;                       // get the grade of the bureaucrat



    // Member functions
    void incrementGrade();                      // increment the grade of the bureaucrat
    void decrementGrade();                      // decrement the grade of the bureaucrat
    void signForm(AForm& form);                 // sign a form
    void executeForm(AForm const & form) const; // execute a form                  //new



    // Exception classes
    class GradeTooHighException : public std::exception {
    public:
        virtual const char* what() const throw();
    };

    class GradeTooLowException : public std::exception {
    public:
        virtual const char* what() const throw();
    };
};


// Overload of the insertion operator
std::ostream& operator<<(std::ostream& os, const Bureaucrat& bureaucrat);



#endif // BUREAUCRAT_HPP 