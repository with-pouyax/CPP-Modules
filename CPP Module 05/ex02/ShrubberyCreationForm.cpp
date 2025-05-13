#include "ShrubberyCreationForm.hpp"
#include "Bureaucrat.hpp"
#include <fstream>

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target)
    : AForm("Shrubbery Creation", target, SIGN_GRADE, EXEC_GRADE) {
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& other)
    : AForm(other) {
}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& other) {
    if (this != &other) {
        AForm::operator=(other);
    }
    return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm() {
}

void ShrubberyCreationForm::execute(Bureaucrat const & executor) const {
    checkExecutionRequirements(executor);
    
    std::string filename = getTarget() + "_shrubbery";
    std::ofstream outFile(filename.c_str());
    
    if (!outFile.is_open()) {
        throw std::runtime_error("Could not create file: " + filename);
    }

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
} 