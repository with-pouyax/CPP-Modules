# Form Management System

This program extends the bureaucratic system by adding forms that bureaucrats can sign and manage. It creates a complete workflow where bureaucrats interact with various types of forms based on their authority levels.

## What it does:

### Form Creation
- Create forms with a name and specific grade requirements
- Each form has two grade requirements:
  - **Sign Grade**: Minimum authority level needed to sign the form
  - **Execute Grade**: Minimum authority level needed to execute the form
- Forms start as unsigned when created

### Form Signing Process
- **Authority Check**: Only bureaucrats with sufficient authority can sign forms
- **Grade Comparison**: A bureaucrat's grade must be equal to or better than the form's sign grade
- **Success/Failure Messages**: Clear feedback on whether signing succeeded or failed
- **Status Tracking**: Forms remember whether they've been signed

### Bureaucrat-Form Interaction
- **Signing Attempts**: Bureaucrats can try to sign forms
- **Authority Validation**: The system checks if the bureaucrat has enough authority
- **Error Handling**: Shows specific reasons why signing failed (grade too low, etc.)

### Safety Features
- **Grade Validation**: Prevents creating forms with invalid grade requirements
- **Exception Handling**: Gracefully handles errors and shows meaningful messages
- **Form Status**: Tracks whether forms are signed or unsigned

### Display Information
- Shows form details: name, sign status, and grade requirements
- Displays bureaucrat information with their current grade
- Provides clear success/failure messages for all operations

## Example Usage:
- Create a "Tax Form" requiring grade 30 to sign and grade 25 to execute
- Create bureaucrats "Bob" (grade 50) and "Alice" (grade 20)
- Bob tries to sign the form (fails - grade too low)
- Alice signs the form successfully (grade 20 is better than required 30)
- View the form's updated status after signing

This system ensures that only authorized bureaucrats can sign forms and provides a complete audit trail of all signing attempts.

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