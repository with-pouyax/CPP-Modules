#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <string>
#include <iostream>
#include <exception>

/*
- In the Bureaucrat class, we have this function: void signForm(Form& form);
- That means Bureaucrat needs to know that the type `Form` exists.
- At the same time, in the Form class, there's a function: void beSigned(const Bureaucrat& bureaucrat);
- So Form also needs to know about the Bureaucrat type.
- This creates a mutual dependency: Bureaucrat needs Form, and Form needs Bureaucrat.
- If we use `#include "Form.hpp"` inside "Bureaucrat.hpp" and also `#include "Bureaucrat.hpp"` inside "Form.hpp",
  we create a circular include problem (infinite loop of includes).
- The compiler will keep including one header into the other over and over, and it can't finish resolving types.
- To fix this, we use a **forward declaration**: we write `class Form;` at the top of "Bureaucrat.hpp".
- This tells the compiler: “Form is a class, trust me — I’ll give you full details later.”
- Now we can declare pointers or references to Form (like `Form& form`) without needing the full class definition.
- This breaks the loop and lets both classes refer to each other safely.
*/



// Forward declaration of Form to avoid circular dependency
class Form;

class Bureaucrat {
private:
    const std::string _name; 
    int _grade; 

    // Private default constructor
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
    void signForm(Form& form); // sign a form

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