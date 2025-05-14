#ifndef SHRUBBERYCREATIONFORM_HPP
#define SHRUBBERYCREATIONFORM_HPP


#include "AForm.hpp"

//-----------------------------------------------------------------------------

// Declaration of ShrubberyCreationForm class
class ShrubberyCreationForm : public AForm { // ShrubberyCreationForm is a derived class from AForm

public:

    // Orthodox Canonical Form
    ShrubberyCreationForm(const std::string& target);
    ShrubberyCreationForm(const ShrubberyCreationForm& other);
    ShrubberyCreationForm& operator=(const ShrubberyCreationForm& other);
    virtual ~ShrubberyCreationForm();


    // Member functions
    virtual void execute(Bureaucrat const & executor) const;


    // Static constants
    // static means that the value is the same for all instances of the class
    // so it is like a global variable between all the instances of ShrubberyCreationForm
    /* We make attributes private to protect the internal state of the object and prevent any unintended changes from outside the class.
    But in this case, SIGN_GRADE and EXEC_GRADE are declared static const, which means they are:
    Shared between all instances of the class (because they are static), and
    Immutable — they cannot be changed (because they are const).
    So even though they are public, no code outside the class can modify them.
    Keeping them public makes the code cleaner and more readable, and allows easy access to these constant values, which represent the fixed grade requirements of the form. */
    
    static const int SIGN_GRADE = 145; // the grade required to sign the form
    static const int EXEC_GRADE = 137; // the grade required to execute the form
};

#endif // SHRUBBERYCREATIONFORM_HPP 