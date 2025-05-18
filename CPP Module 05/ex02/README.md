# CPP Module 05 - Exercise 02: No, you need form 28B, not 28C...

## Overview
This exercise extends the previous implementation by creating an abstract base class `AForm` and three concrete form classes that perform specific actions. The implementation follows object-oriented principles and includes proper exception handling.

## Class Structure

### AForm (Abstract Base Class)
- **Attributes**:
  - `_name`: Constant string representing the form's name
  - `_isSigned`: Boolean indicating if the form is signed
  - `_gradeRequiredToSign`: Constant integer for required grade to sign
  - `_gradeRequiredToExecute`: Constant integer for required grade to execute

- **Pure Virtual Functions**:
  - `execute(Bureaucrat const & executor) const`: Abstract method to be implemented by derived classes

### Concrete Form Classes

#### ShrubberyCreationForm
- **Required Grades**:
  - Sign: 145
  - Execute: 137
- **Action**: Creates a file `<target>_shrubbery` with ASCII trees

#### RobotomyRequestForm
- **Required Grades**:
  - Sign: 72
  - Execute: 45
- **Action**: Attempts to robotomize the target (50% success rate)

#### PresidentialPardonForm
- **Required Grades**:
  - Sign: 25
  - Execute: 5
- **Action**: Issues a pardon from Zaphod Beeblebrox

### Member Functions
- **Form Management**:
  - `beSigned(const Bureaucrat& bureaucrat)`: Attempts to sign the form
  - `execute(Bureaucrat const & executor) const`: Executes the form's action

### Exception Classes
- `GradeTooHighException`: Thrown when grade is too high (< 1)
- `GradeTooLowException`: Thrown when grade is too low (> 150)
- `FormNotSignedException`: Thrown when attempting to execute unsigned form

## Bureaucrat Class Updates
- Added `executeForm(AForm const & form) const` member function
- Prints success/failure messages when attempting to execute forms

## Usage Example
```cpp
try {
    Bureaucrat bob("Bob", 1);
    ShrubberyCreationForm shrubbery("home");
    bob.signForm(shrubbery);
    bob.executeForm(shrubbery);
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
- `AForm.hpp`: Abstract base class header
- `AForm.cpp`: Abstract base class implementation
- `ShrubberyCreationForm.hpp/cpp`: Shrubbery form implementation
- `RobotomyRequestForm.hpp/cpp`: Robotomy form implementation
- `PresidentialPardonForm.hpp/cpp`: Pardon form implementation
- `Bureaucrat.hpp/cpp`: Updated Bureaucrat class
- `main.cpp`: Test program
- `Makefile`: Compilation rules 