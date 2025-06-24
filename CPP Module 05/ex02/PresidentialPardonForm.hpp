#ifndef PRESIDENTIALPARDONFORM_HPP
#define PRESIDENTIALPARDONFORM_HPP

#include "AForm.hpp"

//same as ShrubberyCreationForm and RobotomyRequestForm only SIGN_GRADE and EXEC_GRADE are different
class PresidentialPardonForm : public AForm {
public:
    PresidentialPardonForm(const std::string& target);
    PresidentialPardonForm(const PresidentialPardonForm& other);
    PresidentialPardonForm& operator=(const PresidentialPardonForm& other);
    virtual ~PresidentialPardonForm();

    virtual void execute(Bureaucrat const & executor) const; // it needs to be virtual because it is a child class of AForm

    static const int SIGN_GRADE = 25;
    static const int EXEC_GRADE = 5;
};

#endif // PRESIDENTIALPARDONFORM_HPP 