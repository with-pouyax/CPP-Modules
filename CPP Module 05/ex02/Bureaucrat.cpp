#include "Bureaucrat.hpp"
#include "AForm.hpp"

// Exception implementations

const char* Bureaucrat::GradeTooHighException::what() const throw() {
    return "Grade is too high!";
}

const char* Bureaucrat::GradeTooLowException::what() const throw() {
    return "Grade is too low!";
}



// Orthodox Canonical Form

// Constructor
Bureaucrat::Bureaucrat(const std::string& name, int grade) : _name(name) {
    if (grade < 1)
        throw GradeTooHighException();
    if (grade > 150)
        throw GradeTooLowException();
    _grade = grade;
}



// Copy constructor
Bureaucrat::Bureaucrat(const Bureaucrat& other) : _name(other._name), _grade(other._grade) {}


// Assignment operator
Bureaucrat& Bureaucrat::operator=(const Bureaucrat& other) {
    if (this != &other) {
        _grade = other._grade; // we don't assign the name because it's a const member
    }
    return *this;
}


// Destructor
Bureaucrat::~Bureaucrat() {}


// Getters
const std::string& Bureaucrat::getName() const {
    return _name;
}

int Bureaucrat::getGrade() const {
    return _grade;
}



// Member functions
void Bureaucrat::incrementGrade() {                //increment the grade of the bureaucrat
    if (_grade <= 1)
        throw GradeTooHighException();
    _grade--;
}

void Bureaucrat::decrementGrade() {               //decrement the grade of the bureaucrat
    if (_grade >= 150)
        throw GradeTooLowException();
    _grade++;
}

void Bureaucrat::signForm(AForm& form) { // this will receive a form object and try to sign it
    try {
        form.beSigned(*this);            //this will sign the form
                                         //we go to the next line only if the form is signed otherwise we catch the exception
        std::cout << _name << " signed " << form.getName() << std::endl;  //we print that the bureaucrat(name) signed the form(name)
    } catch (const std::exception& e) {
        std::cout << _name << " couldn't sign " << form.getName() << " because " << e.what() << std::endl;
    }
}

void Bureaucrat::executeForm(AForm const & form) const {
    try {
        form.execute(*this);                  //this will execute the form
        std::cout << _name << " executed " << form.getName() << std::endl;
    } catch (const std::exception& e) {
        std::cout << _name << " couldn't execute " << form.getName() << " because " << e.what() << std::endl;
    }
}



// Overload of the insertion operator
std::ostream& operator<<(std::ostream& os, const Bureaucrat& bureaucrat) {
    os << bureaucrat.getName() << ", bureaucrat grade " << bureaucrat.getGrade() << ".";
    return os;
}