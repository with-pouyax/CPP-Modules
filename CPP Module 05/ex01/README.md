# CPP Module 05 - Exercise 01: Form up, maggots!

## Overview
This exercise extends the previous implementation by adding a `Form` class that bureaucrats can sign. The implementation follows the Orthodox Canonical Form and includes proper exception handling.

## Class Structure

### Form Class
- **Attributes**:
  - `_name`: Constant string representing the form's name
  - `_isSigned`: Boolean indicating if the form is signed
  - `_gradeRequiredToSign`: Constant integer for required grade to sign
  - `_gradeRequiredToExecute`: Constant integer for required grade to execute

### Grade System
- Grade 1 is the highest possible grade
- Grade 150 is the lowest possible grade
- Invalid grades throw exceptions

### Member Functions
- **Constructors**:
  - `Form(const std::string& name, int gradeToSign, int gradeToExecute)`: Main constructor
  - `Form(const Form& other)`: Copy constructor
  - `Form& operator=(const Form& other)`: Assignment operator
  - `~Form()`: Destructor

- **Getters**:
  - `getName()`: Returns the form's name
  - `getIsSigned()`: Returns the form's signed status
  - `getGradeRequiredToSign()`: Returns required grade to sign
  - `getGradeRequiredToExecute()`: Returns required grade to execute

- **Form Management**:
  - `beSigned(const Bureaucrat& bureaucrat)`: Attempts to sign the form

### Exception Classes
- `GradeTooHighException`: Thrown when grade is too high (< 1)
- `GradeTooLowException`: Thrown when grade is too low (> 150)

### Output Format
- Overloaded insertion operator (`<<`) prints form information

## Bureaucrat Class Updates
- Added `signForm(Form& form)` member function
- Prints success/failure messages when attempting to sign forms

## Usage Example
```cpp
try {
    Bureaucrat bob("Bob", 2);
    Form form("Tax Return", 5, 3);
    bob.signForm(form);
    std::cout << form << std::endl;
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
- `Form.hpp`: Header file containing Form class declaration
- `Form.cpp`: Form class implementation
- `Bureaucrat.hpp`: Updated Bureaucrat class header
- `Bureaucrat.cpp`: Updated Bureaucrat class implementation
- `main.cpp`: Test program
- `Makefile`: Compilation rules 