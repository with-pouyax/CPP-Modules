#include "RobotomyRequestForm.hpp"
#include "Bureaucrat.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <time.h>

RobotomyRequestForm::RobotomyRequestForm(const std::string& target)
    : AForm("Robotomy Request", target.empty() ? "unknown" : target, SIGN_GRADE, EXEC_GRADE) {
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& other)
    : AForm(other) {
}

RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm& other) {
    if (this != &other) {
        AForm::operator=(other);
    }
    return *this;
}

RobotomyRequestForm::~RobotomyRequestForm() {
}

void RobotomyRequestForm::execute(Bureaucrat const & executor) const {
    checkExecutionRequirements(executor);
    
    std::cout << "* DRILLING NOISES *" << std::endl;
    
    // Use time with microseconds for better randomness in quick successive calls
    struct timespec ts;    //struct timespec is a data type that can store the time in nanoseconds
    clock_gettime(CLOCK_REALTIME, &ts); // clock_gettime is a function that returns the time in nanoseconds
                                        //it receives two parameters: 1- the clock id, which is CLOCK_REALTIME means the current time
                                        //2- the address of the struct timespec variable to store the time
    long randomValue = ts.tv_nsec; // nanoseconds for microsecond precision
    
    if ((randomValue % 2) == 0) {
        std::cout << getTarget() << " has been robotomized successfully!" << std::endl;
    } else {
        std::cerr << "Robotomy failed on " << getTarget() << "." << std::endl;
    }
} 