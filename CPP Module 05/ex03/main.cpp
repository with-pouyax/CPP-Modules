#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"
#include <iostream>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

void printHeader(const std::string& title) {
    std::cout << std::endl;
    std::cout << BLUE << "══════════════════════════════════════════════════════════════" << RESET << std::endl;
    std::cout << BLUE << "                    " << title << RESET << std::endl;
    std::cout << BLUE << "══════════════════════════════════════════════════════════════" << RESET << std::endl;
}

void printSubHeader(const std::string& subtitle) {
    std::cout << std::endl;
    std::cout << CYAN << "----------------------------------------" << RESET << std::endl;
    std::cout << CYAN << subtitle << RESET << std::endl;
    std::cout << CYAN << "----------------------------------------" << RESET << std::endl;
}

void printTestResult(const std::string& testName, bool success) {
    std::cout << (success ? GREEN : RED) << "[" << (success ? "SUCCESS" : "FAILURE") << "] " 
              << RESET << testName << std::endl;
}

void testInternWithEmptyTarget() {
    printHeader("TESTING INTERN WITH EMPTY TARGET");
    
    try {
        Intern intern;
        
        printSubHeader("Testing Forms with Empty Target");
        std::cout << MAGENTA << "Creating forms with empty target (should use 'unknown'):" << RESET << std::endl;
        
        AForm* scf = intern.makeForm("shrubbery creation", "");
        std::cout << YELLOW << "Created: " << *scf << RESET << std::endl;
        delete scf;
        
        AForm* rrf = intern.makeForm("robotomy request", "");
        std::cout << YELLOW << "Created: " << *rrf << RESET << std::endl;
        delete rrf;
        
        AForm* ppf = intern.makeForm("presidential pardon", "");
        std::cout << YELLOW << "Created: " << *ppf << RESET << std::endl;
        delete ppf;

        AForm* unknown = intern.makeForm("", "");
        std::cout << YELLOW << "Created: " << *unknown << RESET << std::endl;
        delete unknown;
    }
    catch (const std::exception& e) {
        std::cout << RED << "Exception caught: " << e.what() << RESET << std::endl;
    }
}

void testInternCaseSensitivity() {
    printHeader("TESTING INTERN CASE SENSITIVITY");
    
    try {
        Intern intern;
        
        printSubHeader("Testing Different Case Variations");
        std::cout << MAGENTA << "Testing 'SHRUBBERY CREATION':" << RESET << std::endl;
        try {
            AForm* form = intern.makeForm("SHRUBBERY CREATION", "garden");
            std::cout << YELLOW << "Created: " << *form << RESET << std::endl;
            delete form;
        } catch (const Intern::UnknownFormException& e) {
            std::cout << RED << "Exception caught: " << e.what() << RESET << std::endl;
        }
        
        std::cout << MAGENTA << "Testing 'Robotomy Request':" << RESET << std::endl;
        try {
            AForm* form = intern.makeForm("Robotomy Request", "Bender");
            std::cout << YELLOW << "Created: " << *form << RESET << std::endl;
            delete form;
        } catch (const Intern::UnknownFormException& e) {
            std::cout << RED << "Exception caught: " << e.what() << RESET << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cout << RED << "Exception caught: " << e.what() << RESET << std::endl;
    }
}

void testCompleteWorkflowWithAllForms() {
    printHeader("TESTING COMPLETE WORKFLOW WITH ALL FORMS");
    
    try {
        Intern intern;
        Bureaucrat boss("Boss", 1);
        Bureaucrat worker("Worker", 150);
        
        printSubHeader("Testing Shrubbery Creation Workflow");
        AForm* scf = intern.makeForm("shrubbery creation", "office_garden");
        std::cout << YELLOW << "Created: " << *scf << RESET << std::endl;
        
        std::cout << MAGENTA << "Worker trying to sign:" << RESET << std::endl;
        worker.signForm(*scf);
        
        std::cout << MAGENTA << "Boss signing and executing:" << RESET << std::endl;
        boss.signForm(*scf);
        boss.executeForm(*scf);
        delete scf;
        
        printSubHeader("Testing Robotomy Request Workflow");
        AForm* rrf = intern.makeForm("robotomy request", "Robot");
        std::cout << YELLOW << "Created: " << *rrf << RESET << std::endl;
        
        std::cout << MAGENTA << "Boss signing and executing:" << RESET << std::endl;
        boss.signForm(*rrf);
        boss.executeForm(*rrf);
        delete rrf;
        
        printSubHeader("Testing Presidential Pardon Workflow");
        AForm* ppf = intern.makeForm("presidential pardon", "Prisoner");
        std::cout << YELLOW << "Created: " << *ppf << RESET << std::endl;
        
        std::cout << MAGENTA << "Boss signing and executing:" << RESET << std::endl;
        boss.signForm(*ppf);
        boss.executeForm(*ppf);
        delete ppf;
    }
    catch (const std::exception& e) {
        std::cout << RED << "Exception caught: " << e.what() << RESET << std::endl;
    }
}

int main() {
    try {
        // Test Intern functionality (the only new feature in ex03)
        testInternWithEmptyTarget();
        testInternCaseSensitivity();
        testCompleteWorkflowWithAllForms();
        
        std::cout << std::endl << GREEN << "══════════════════════════════════════════════════════════════" << RESET << std::endl;
        std::cout << GREEN << "                    ALL INTERN TESTS COMPLETED SUCCESSFULLY!" << RESET << std::endl;
        std::cout << GREEN << "══════════════════════════════════════════════════════════════" << RESET << std::endl;

    } catch (std::exception& e) {
        std::cout << RED << "Main exception caught: " << e.what() << RESET << std::endl;
    }

    return 0;
} 