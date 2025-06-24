#include "RobotomyRequestForm.hpp"
#include "Bureaucrat.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

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
    

    //rand creates a random number between 0 and 32767 for us
    // the problem is in each execution of the program, the random number is the same
    // to solve this, we need to use srand
    // srand takes an int as a parameter, which we call seed
    // so now if we first call srand(99) and then rand() we will get different random numbers
    // but again, if we run the program multiple times, the random numbers will be the same
    // now we can fix this by giving it dynamic seed every time we run the program
    // we use time(0), it returns the current time as the number of seconds since the epoch
    // so now every time we run the program, the seed is different

    std::srand(std::time(0));
    
    if (std::rand() % 2) { // rand() % 2 will return 0 or 1
        std::cout << getTarget() << " has been robotomized successfully!" << std::endl;
    } else {
        std::cerr << "Robotomy failed on " << getTarget() << "." << std::endl;
    }
} 