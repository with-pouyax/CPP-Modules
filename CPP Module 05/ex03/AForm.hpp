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
    const std::string _target;         // Added target member

    
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
    
    
    // Pure virtual execute function
    virtual void execute(Bureaucrat const & executor) const = 0;
    
    // Exception classes
    //===============================================
    class GradeTooHighException : public std::exception {
    public:
        virtual const char* what() const throw();
    };

    class GradeTooLowException : public std::exception {
    public:
        virtual const char* what() const throw();
    };

    class FormNotSignedException : public std::exception {
    public:
        virtual const char* what() const throw();
    };

    class FormAlreadySignedException : public std::exception {
    public:
        virtual const char* what() const throw();
    };
    //===============================================

    // Protected function to check execution requirements
protected:

    void checkExecutionRequirements(const Bureaucrat& executor) const;
};

// Overload of the insertion operator
std::ostream& operator<<(std::ostream& os, const AForm& form);

#endif // AFORM_HPP 