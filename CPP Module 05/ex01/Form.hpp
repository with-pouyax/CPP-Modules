#ifndef FORM_HPP
#define FORM_HPP

#include <string>
#include <iostream>
#include <exception>


class Bureaucrat;

class Form {
private:
    const std::string _name;           // this is the name of the form
    bool _isSigned;                    // this is a boolean that will be used to check if the form is signed
    const int _gradeRequiredToSign;    // this is the grade required to sign the form
    const int _gradeRequiredToExecute; // this is the grade required to execute the form

    // Private default constructor
    Form();

public:
    // Orthodox Canonical Form
    Form(const std::string& name, int gradeToSign, int gradeToExecute); // constructor with name, grade to sign and grade to execute
    Form(const Form& other); // copy constructor
    Form& operator=(const Form& other); // assignment operator
    ~Form(); // destructor

    // Getters
    const std::string& getName() const;    // get the name of the form
    bool getIsSigned() const;              // get if the form is signed
    int getGradeRequiredToSign() const;    // get the grade required to sign the form
    int getGradeRequiredToExecute() const; // get the grade required to execute the form




//===============================================
    // Member functions
    void beSigned(const Bureaucrat& bureaucrat);  // this will receive a bureaucrat object and try to sign the form
//===============================================




    // Exception classes
    class GradeTooHighException : public std::exception { // this is a custom exception class that will be used to handle the grade too high exception
    public:
        virtual const char* what() const throw();
    };

    class GradeTooLowException : public std::exception { // this is a custom exception class that will be used to handle the grade too low exception
    public:
        virtual const char* what() const throw();
    };

    class FormAlreadySignedException : public std::exception { // this is a custom exception class that will be used to handle the form already signed exception
    public:
        virtual const char* what() const throw();
    };
};

// Overload of the insertion operator
std::ostream& operator<<(std::ostream& os, const Form& form);

#endif // FORM_HPP 