#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <string>
#include <iostream>
#include <exception>


class Bureaucrat {
private:
    const std::string _name; 
    int _grade; 

    // our constructor is private because we don't want to be able to create a Bureaucrat without a name and a grade
    // so like this we don't have access to default constructor from outside the class
    Bureaucrat(); 

public:
    // Orthodox Canonical Form
    Bureaucrat(const std::string& name, int grade); // constructor with name and grade
    Bureaucrat(const Bureaucrat& other); // copy constructor
    Bureaucrat& operator=(const Bureaucrat& other); // assignment operator
    ~Bureaucrat(); // destructor

    // Getters
    const std::string& getName() const; // get the name of the bureaucrat
    int getGrade() const; // get the grade of the bureaucrat

    // Member functions
    void incrementGrade(); // increment the grade of the bureaucrat
    void decrementGrade(); // decrement the grade of the bureaucrat

    // Exception classes
    // here we defined a class inside the Bureaucrat class
    // because we want to be able to throw an exception from the Bureaucrat class
    // this a child of the std::exception class.
    // exception classes comes from include <exception>
    // we override the what() function to return our desired message

    // we call this throw() at the end of the function Exception Specification
    //it means that we promise the compiler that this function will not throw an exception (it will not fail on something)
    // we need to include it here because the original what(), has this throw()

    class GradeTooHighException : public std::exception {
    public:
        virtual const char* what() const throw();
    };

    //Because exception classes are lightweight, short-lived, and not meant to be copied or assigned, so Orthodox Canonical Form is unnecessary.
    class GradeTooLowException : public std::exception {
    public:
        virtual const char* what() const throw();
    };
};

// Overload of the insertion operator
std::ostream& operator<<(std::ostream& os, const Bureaucrat& bureaucrat);

#endif // BUREAUCRAT_HPP 