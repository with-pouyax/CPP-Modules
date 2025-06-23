# Advanced Form Management System with Interns

This program creates a complete bureaucratic ecosystem with specialized forms, form execution capabilities, and interns who can create forms on demand. It's like having a smart office assistant who can generate different types of forms based on your needs.

## What it does:

### Intern Form Creation
- **Smart Intern**: An intern who can create different types of forms just by asking
- **Form Types Available**:
  - **Shrubbery Creation Form**: Creates decorative trees in files
  - **Robotomy Request Form**: Simulates robot surgery (50% success rate)
  - **Presidential Pardon Form**: Grants pardons from Zaphod Beeblebrox
- **Dynamic Creation**: Just tell the intern what form you need and who it's for

### Specialized Forms with Actions
Each form type has specific requirements and performs unique actions:

#### Shrubbery Creation Form
- **Requirements**: Grade 145 to sign, Grade 137 to execute
- **Action**: Creates a file with ASCII art trees
- **Target**: Specifies where to plant the shrubbery

#### Robotomy Request Form
- **Requirements**: Grade 72 to sign, Grade 45 to execute
- **Action**: Makes drilling noises and has a 50% chance of success
- **Target**: The person to be robotomized

#### Presidential Pardon Form
- **Requirements**: Grade 25 to sign, Grade 5 to execute
- **Action**: Announces a presidential pardon
- **Target**: The person being pardoned

### Complete Workflow
1. **Form Creation**: Intern creates the right form for your needs
2. **Form Signing**: Bureaucrat with sufficient authority signs the form
3. **Form Execution**: Bureaucrat with sufficient authority executes the form's action
4. **Error Handling**: Clear messages for any failures or insufficient authority

### Safety and Validation
- **Authority Checks**: Ensures only qualified bureaucrats can sign and execute
- **Form Validation**: Prevents execution of unsigned forms
- **Error Messages**: Clear feedback when operations fail
- **Memory Management**: Proper cleanup of created forms

### Example Workflow:
1. Ask intern to create a "robotomy request" form for "Bender"
2. High-level bureaucrat signs the form
3. High-level bureaucrat executes the form (drilling noises, success/failure message)
4. Form is properly cleaned up

This system provides a complete bureaucratic workflow where interns handle the tedious form creation, and bureaucrats handle the authority-based signing and execution of specialized forms.

## Class Structure

### Intern Class
- **Purpose**: Creates different types of forms based on their names
- **No Attributes**: Interns have no name, grade, or unique characteristics

### Member Functions
- **Form Creation**:
  - `makeForm(const std::string& formName, const std::string& target)`: Creates and returns a form based on the name and target

### Supported Form Types
- `shrubbery creation`
- `robotomy request`
- `presidential pardon`

### Error Handling
- Throws an exception if the requested form type doesn't exist
- Prints appropriate success/error messages

## Usage Example
```cpp
try {
    Intern someRandomIntern;
    AForm* rrf;
    rrf = someRandomIntern.makeForm("robotomy request", "Bender");
    if (rrf) {
        Bureaucrat bob("Bob", 1);
        bob.signForm(*rrf);
        bob.executeForm(*rrf);
        delete rrf;
    }
} catch (std::exception& e) {
    std::cout << e.what() << std::endl;
}
```

## Compilation
Use the provided Makefile to compile the project:
```bash
make
```

## Files
- `Intern.hpp`: Intern class header
- `Intern.cpp`: Intern class implementation
- `AForm.hpp/cpp`: Abstract form base class
- `ShrubberyCreationForm.hpp/cpp`: Shrubbery form implementation
- `RobotomyRequestForm.hpp/cpp`: Robotomy form implementation
- `PresidentialPardonForm.hpp/cpp`: Pardon form implementation
- `Bureaucrat.hpp/cpp`: Bureaucrat class
- `main.cpp`: Test program
- `Makefile`: Compilation rules

## Design Notes
- The implementation avoids using excessive if/else structures
- Form creation is handled elegantly through a form factory pattern
- Memory management is properly handled with appropriate cleanup 