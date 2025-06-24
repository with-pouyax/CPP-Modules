#include "ShrubberyCreationForm.hpp"
#include "Bureaucrat.hpp"
#include <fstream>
#include <iostream>

//-----------------------------------------------------------------------------

// Constructor
// 1- we recieve a target as a parameter of the constructor of ShrubberyCreationForm
// 2- since ShrubberyCreationForm is a derived class from AForm, we call the constructor of AForm with the name "Shrubbery Creation"
//, the target that we recieved as a parameter of the constructor of ShrubberyCreationForm, and since we have SIGN_GRADE and EXEC_GRADE
// as static const attributes in ShrubberyCreationForm class they are global to all the instances of ShrubberyCreationForm
// so we can access them here and also pass them to the constructor of AForm

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target)
    : AForm("Shrubbery Creation", target, SIGN_GRADE, EXEC_GRADE) {
}

// Copy constructor
// we just call the copy constructor of AForm because a ShrubberyCreationForm has no extra attributes compared to AForm
ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& other)
    : AForm(other) {
}

// Assignment operator
//again we just call the assignment operator of AForm because a ShrubberyCreationForm has no extra attributes compared to AForm
ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& other) {
    if (this != &other) {
        AForm::operator=(other);
    }
    return *this;
}

// Destructor
ShrubberyCreationForm::~ShrubberyCreationForm() {
}


//-----------------------------------------------------------------------------

// Member function
// we need to call execute function always in a try block because it can throw an exception
void ShrubberyCreationForm::execute(Bureaucrat const & executor) const {
    checkExecutionRequirements(executor); //first we check if the requirements are met
    
    std::string filename = getTarget() + "_shrubbery"; //we get the target and add "_shrubbery" to it
    std::ofstream outFile(filename.c_str()); //we create an ofstream object with the filename we created
    
    if (!outFile.is_open()) {
        throw std::runtime_error("Could not create file: " + filename); //if the file is not created, we throw a runtime exception
    }

    //if we don't have an error, and the file is created, we write the tree in the file
    outFile << "      /\\      " << std::endl;
    outFile << "     /\\*\\     " << std::endl;
    outFile << "    /\\O\\*\\    " << std::endl;
    outFile << "   /*/\\/\\/\\   " << std::endl;
    outFile << "  /\\O\\/\\*\\/\\  " << std::endl;
    outFile << " /\\*\\/\\*\\/\\/\\ " << std::endl;
    outFile << "/\\O\\/\\/*/\\/O/\\" << std::endl;
    outFile << "      ||      " << std::endl;
    outFile << "      ||      " << std::endl;
    outFile << "      ||      " << std::endl;
    
    outFile.close();
    
    std::cout << "\033[33m[WARNING]\033[0m Shrubbery created successfully in file: " << filename << std::endl << std::endl;
} 