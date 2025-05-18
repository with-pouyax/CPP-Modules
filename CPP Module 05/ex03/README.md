# CPP Module 05 - Exercise 03: At least this beats coffee-making

## Overview
This exercise adds an `Intern` class to the previous implementation, which can create different types of forms based on their names. The implementation follows object-oriented principles and includes proper error handling.

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