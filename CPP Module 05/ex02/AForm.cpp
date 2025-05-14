#include "AForm.hpp"
#include "Bureaucrat.hpp"

//-----------------------------------------------------------------------------


// Exception implementations
const char* AForm::GradeTooHighException::what() const throw() {
    return "Form grade is too high!";
}

const char* AForm::GradeTooLowException::what() const throw() {
    return "Form grade is too low!";
}

const char* AForm::FormNotSignedException::what() const throw() {
    return "Form is not signed!";
}


//-----------------------------------------------------------------------------


// Orthodox Canonical Form
// Constructor
AForm::AForm(const std::string& name, const std::string& target, int gradeToSign, int gradeToExecute)
    : _name(name), _isSigned(false), _gradeRequiredToSign(gradeToSign), 
      _gradeRequiredToExecute(gradeToExecute), _target(target) { // we set the default values of isSigned to false because the form is not signed yet
    if (gradeToSign < 1 || gradeToExecute < 1)
        throw GradeTooHighException();
    if (gradeToSign > 150 || gradeToExecute > 150)
        throw GradeTooLowException();
}

// Copy constructor
AForm::AForm(const AForm& other)
    : _name(other._name), _isSigned(other._isSigned),
      _gradeRequiredToSign(other._gradeRequiredToSign), 
      _gradeRequiredToExecute(other._gradeRequiredToExecute),
      _target(other._target) {
}

// Assignment operator
AForm& AForm::operator=(const AForm& other) {
    if (this != &other) {
        _isSigned = other._isSigned;
    }
    return *this;
}

// Destructor
AForm::~AForm() {}


//-----------------------------------------------------------------------------

// Getters
const std::string& AForm::getName() const {
    return _name;
}


bool AForm::getIsSigned() const {
    return _isSigned;
}


int AForm::getGradeRequiredToSign() const {
    return _gradeRequiredToSign;
}


int AForm::getGradeRequiredToExecute() const {
    return _gradeRequiredToExecute;
}


const std::string& AForm::getTarget() const {
    return _target;
}


//-----------------------------------------------------------------------------


// Member functions
void AForm::beSigned(const Bureaucrat& bureaucrat) {
    if (bureaucrat.getGrade() <= _gradeRequiredToSign) { // if the bureaucrat's grade is less than or equal to the grade required
        _isSigned = true; // we set the form to signed
    } else {
        throw GradeTooLowException();
    }
}


// we check if the form is signed and if the executor's grade is greater than the grade required
// if form is not signed, we throw an exception with the message "Form is not signed!"
// if executor's grade is greater than the grade required, we throw an exception with the message "Grade too low!"
// if if the form is signed and the executor's grade is less than or equal to the grade required, we do nothing
// we call checkExecutionRequirements in the main function in a try block to jump to the catch block if the requirements are not met

void AForm::checkExecutionRequirements(const Bureaucrat& executor) const {
    if (!_isSigned) // if the form is not signed
        throw FormNotSignedException(); // we throw an exception
    if (executor.getGrade() > _gradeRequiredToExecute) // if the executor's grade is greater than the grade required
        throw GradeTooLowException(); // we throw an exception
}

// Overload of the insertion operator
std::ostream& operator<<(std::ostream& os, const AForm& form) {
    os << "Form: " << form.getName()
       << ", Target: " << form.getTarget()
       << ", Sign status: " << (form.getIsSigned() ? "Signed" : "Not signed")
       << ", Grade required to sign: " << form.getGradeRequiredToSign()
       << ", Grade required to execute: " << form.getGradeRequiredToExecute();
    return os;
} 