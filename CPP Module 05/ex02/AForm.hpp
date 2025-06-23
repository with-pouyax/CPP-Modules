#ifndef AFORM_HPP
#define AFORM_HPP

#include <string>
#include <iostream>
#include <exception>

//-----------------------------------------------------------------------------

// Forward declaration of Bureaucrat class
class Bureaucrat;

//-----------------------------------------------------------------------------

// Declaration of AForm class
class AForm {

private:

    const std::string _name;           
    bool _isSigned;                    
    const int _gradeRequiredToSign;    
    const int _gradeRequiredToExecute; 
    const std::string _target;         // Added target member  //new

    
    // Private default constructor
    AForm();


public:
    
    // Orthodox Canonical Form
    AForm(const std::string& name, const std::string& target, int gradeToSign, int gradeToExecute);
    AForm(const AForm& other);
    AForm& operator=(const AForm& other);
    virtual ~AForm();

    
    // Getters
    const std::string& getName() const;
    bool getIsSigned() const;
    int getGradeRequiredToSign() const;
    int getGradeRequiredToExecute() const;
    const std::string& getTarget() const;

    
    // Member functions
    void beSigned(const Bureaucrat& bureaucrat); //try to sign the form
    
    
    // Pure virtual execute function means that AForm is an abstract class and we can't create an object of type AForm
    virtual void execute(Bureaucrat const & executor) const = 0;                 //new
    
    // Exception classes
    class GradeTooHighException : public std::exception {
    public:
        virtual const char* what() const throw();
    };

    class GradeTooLowException : public std::exception {
    public:
        virtual const char* what() const throw();
    };

    class GradeTooLowToExecuteException : public std::exception {
    public:
        virtual const char* what() const throw();
    };

    class FormNotSignedException : public std::exception {
    public:
        virtual const char* what() const throw();
    };

    // Protected function to check execution requirements, it is protected because it is used in the child classes but still why ? ******
protected:

    void checkExecutionRequirements(const Bureaucrat& executor) const; //new
};

// Overload of the insertion operator
std::ostream& operator<<(std::ostream& os, const AForm& form);

#endif // AFORM_HPP 