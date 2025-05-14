#ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP

#include "AForm.hpp"

//same as ShrubberyCreationForm only SIGN_GRADE and EXEC_GRADE are different
class RobotomyRequestForm : public AForm {
public:
    RobotomyRequestForm(const std::string& target);
    RobotomyRequestForm(const RobotomyRequestForm& other);
    RobotomyRequestForm& operator=(const RobotomyRequestForm& other);
    virtual ~RobotomyRequestForm();

    virtual void execute(Bureaucrat const & executor) const;

    static const int SIGN_GRADE = 72;
    static const int EXEC_GRADE = 45;
};

#endif // ROBOTOMYREQUESTFORM_HPP 