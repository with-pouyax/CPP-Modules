#ifndef SHRUBBERYCREATIONFORM_HPP
#define SHRUBBERYCREATIONFORM_HPP

#include "AForm.hpp"

class ShrubberyCreationForm : public AForm {

public:

    // Orthodox Canonical Form
    ShrubberyCreationForm(const std::string& target);
    ShrubberyCreationForm(const ShrubberyCreationForm& other);
    ShrubberyCreationForm& operator=(const ShrubberyCreationForm& other);
    virtual ~ShrubberyCreationForm();


    // Member functions
    virtual void execute(Bureaucrat const & executor) const;


    // Static constants
    static const int SIGN_GRADE = 145; // the grade required to sign the form
    static const int EXEC_GRADE = 137; // the grade required to execute the form
};

#endif // SHRUBBERYCREATIONFORM_HPP 