#include "Form.hpp"
#include "Bureaucrat.hpp"

// Exception implementations
const char* Form::GradeTooHighException::what() const throw() {
    return "Form grade is too high!";
}

const char* Form::GradeTooLowException::what() const throw() {
    return "Bureaucrat grade is too low!";
}

const char* Form::FormAlreadySignedException::what() const throw() {
    return "Form is already signed!";
}

// Constructor
Form::Form(const std::string& name, int gradeToSign, int gradeToExecute)
    : _name(name.empty() ? "unknown" : name), _isSigned(false), _gradeRequiredToSign(gradeToSign), _gradeRequiredToExecute(gradeToExecute) {
    if (gradeToSign < 1 || gradeToExecute < 1)
        throw GradeTooHighException();
    if (gradeToSign > 150 || gradeToExecute > 150)
        throw GradeTooLowException();
}

// Copy constructor
Form::Form(const Form& other)
    : _name(other._name), _isSigned(other._isSigned),
      _gradeRequiredToSign(other._gradeRequiredToSign), _gradeRequiredToExecute(other._gradeRequiredToExecute) {
}

// Assignment operator
Form& Form::operator=(const Form& other) {
    if (this != &other) {
        // We can only assign the signed status, as the other attributes are constant
        _isSigned = other._isSigned;
    }
    return *this;
}

// Destructor
Form::~Form() {}

// Getters
const std::string& Form::getName() const {
    return _name;
}

// here we get _isSigned
bool Form::getIsSigned() const {
    return _isSigned;
}

// here we get _gradeRequiredToSign
int Form::getGradeRequiredToSign() const {
    return _gradeRequiredToSign;
}

// here we get _gradeRequiredToExecute
int Form::getGradeRequiredToExecute() const {
    return _gradeRequiredToExecute;
}

// Member functions



//===============================================
// here we receive a bureaucrat object and try to sign the form
void Form::beSigned(const Bureaucrat& bureaucrat) {
    if (_isSigned) { // if the form is already signed
        throw FormAlreadySignedException(); // then we throw an exception
    }
    if (bureaucrat.getGrade() <= _gradeRequiredToSign) { // if the bureaucrat grade is less than or equal to the grade required to sign the form
        _isSigned = true; // then we sign the form
    } else { // if the bureaucrat grade is greater than the grade required to sign the form
        throw GradeTooLowException(); // then we throw an exception
    }
}
//===============================================



// Overload of the insertion operator
// this will return a refrence to the output stream (cout)
// it will receive at the left side of << an object of type ostream (cout) and at the right side an object of type Form
std::ostream& operator<<(std::ostream& os, const Form& form) {
    os << "Form: " << form.getName() // os is usually cout
       << ", Sign status: " << (form.getIsSigned() ? "Signed" : "Not signed") // here if the form is signed, we print "Signed", otherwise we print "Not signed"
       << ", Grade required to sign: " << form.getGradeRequiredToSign() // here we print the grade required to sign the form
       << ", Grade required to execute: " << form.getGradeRequiredToExecute(); // here we print the grade required to execute the form
    return os;
} 