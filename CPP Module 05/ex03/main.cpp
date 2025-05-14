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

void testShrubberyCreationForm() {
    printHeader("TESTING SHRUBBERY CREATION FORM");
    
    try {
        Bureaucrat highGrade("HighGrade", 1); // we make a bureaucrat with the highest grade
        Bureaucrat lowGrade("LowGrade", 150); // we make a bureaucrat with the lowest grade
        ShrubberyCreationForm form("garden"); // we make a shrubbery creation form with the target "garden"

        printSubHeader("Form Information");   
        std::cout << YELLOW << form << RESET << std::endl;
        
        printSubHeader("Testing Low Grade Bureaucrat");
        std::cout << MAGENTA << "Attempting to sign with " << lowGrade << RESET << std::endl;
        lowGrade.signForm(form);
        
        printSubHeader("Testing High Grade Bureaucrat");
        std::cout << MAGENTA << "Attempting to sign with " << highGrade << RESET << std::endl;
        highGrade.signForm(form);
        
        printSubHeader("Testing Form Execution");
        std::cout << MAGENTA << "Attempting to execute with low grade bureaucrat:" << RESET << std::endl;
        lowGrade.executeForm(form);
        std::cout << MAGENTA << "\nAttempting to execute with high grade bureaucrat:" << RESET << std::endl;
        highGrade.executeForm(form);
    }
    catch (const std::exception& e) {
        std::cout << RED << "Exception caught: " << e.what() << RESET << std::endl;
    }
}

void testRobotomyRequestForm() {
    printHeader("TESTING ROBOTOMY REQUEST FORM");
    
    try {
        Bureaucrat highGrade("HighGrade", 1);
        Bureaucrat mediumGrade("MediumGrade", 50);
        RobotomyRequestForm form("Bender");

        printSubHeader("Form Information");
        std::cout << YELLOW << form << RESET << std::endl;
        
        printSubHeader("Testing Execution Without Signature");
        std::cout << MAGENTA << "Attempting to execute without signing:" << RESET << std::endl;
        highGrade.executeForm(form);
        
        printSubHeader("Testing Form Signing");
        std::cout << MAGENTA << "Signing the form with high grade bureaucrat:" << RESET << std::endl;
        highGrade.signForm(form);
        
        printSubHeader("Testing Multiple Robotomy Attempts");
        std::cout << MAGENTA << "Executing form multiple times with high grade bureaucrat:" << RESET << std::endl;
        for (int i = 0; i < 3; ++i) {
            std::cout << "\nAttempt " << (i + 1) << ":" << std::endl;
            highGrade.executeForm(form);
        }
        
        printSubHeader("Testing Medium Grade Execution");
        std::cout << MAGENTA << "Attempting to execute with " << mediumGrade << RESET << std::endl;
        mediumGrade.executeForm(form);
    }
    catch (const std::exception& e) {
        std::cout << RED << "Exception caught: " << e.what() << RESET << std::endl;
    }
}

void testPresidentialPardonForm() {
    printHeader("TESTING PRESIDENTIAL PARDON FORM");
    
    try {
        Bureaucrat president("President", 1);
        Bureaucrat secretary("Secretary", 20);
        PresidentialPardonForm form("Arthur Dent");

        printSubHeader("Form Information");
        std::cout << YELLOW << form << RESET << std::endl;
        
        printSubHeader("Testing Secretary Actions");
        std::cout << MAGENTA << "Attempting to sign with " << secretary << RESET << std::endl;
        secretary.signForm(form);
        std::cout << MAGENTA << "\nAttempting to execute with secretary:" << RESET << std::endl;
        secretary.executeForm(form);
        
        printSubHeader("Testing Presidential Actions");
        std::cout << MAGENTA << "Attempting actions with " << president << RESET << std::endl;
        president.signForm(form);
        president.executeForm(form);
    }
    catch (const std::exception& e) {
        std::cout << RED << "Exception caught: " << e.what() << RESET << std::endl;
    }
}

int main() {
    try {
        // Test Intern class
        printHeader("Testing Intern");
        {
            Intern someRandomIntern;
            AForm* rrf;
            
            // Test creating RobotomyRequestForm
            rrf = someRandomIntern.makeForm("robotomy request", "Bender");
            std::cout << *rrf << std::endl;
            delete rrf;

            // Test creating PresidentialPardonForm
            AForm* ppf = someRandomIntern.makeForm("presidential pardon", "Criminal");
            std::cout << *ppf << std::endl;
            delete ppf;

            // Test creating ShrubberyCreationForm
            AForm* scf = someRandomIntern.makeForm("shrubbery creation", "Garden");
            std::cout << *scf << std::endl;
            delete scf;

            // Test invalid form name
            try {
                AForm* invalid = someRandomIntern.makeForm("invalid form", "Target");
                delete invalid;
            } catch (std::exception& e) {
                std::cout << "Exception caught: " << e.what() << std::endl;
            }
        }

        // Test complete workflow
        printHeader("Testing Complete Workflow");
        {
            Intern intern;
            Bureaucrat boss("Boss", 1);
            Bureaucrat worker("Worker", 150);

            AForm* form = intern.makeForm("robotomy request", "Bender");
            
            std::cout << "\nTrying to execute without signing:" << std::endl;
            try {
                boss.executeForm(*form);
            } catch (std::exception& e) {
                std::cout << "Exception caught: " << e.what() << std::endl;
            }

            std::cout << "\nSigning and executing the form:" << std::endl;
            boss.signForm(*form);
            boss.executeForm(*form);

            delete form;
        }

    } catch (std::exception& e) {
        std::cout << "Main exception caught: " << e.what() << std::endl;
    }

    return 0;
} 