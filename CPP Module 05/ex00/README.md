# Bureaucrat Management System

This program simulates a bureaucratic office environment where you can create and manage bureaucrats with different authority levels.

## What it does:

### Bureaucrat Creation
- Create bureaucrats with a name and a grade (authority level)
- Grades range from 1 (highest authority) to 150 (lowest authority)
- Each bureaucrat has a unique name that cannot be changed

### Grade Management
- **Increment Grade**: Makes a bureaucrat more powerful (grade 3 becomes grade 2)
- **Decrement Grade**: Makes a bureaucrat less powerful (grade 2 becomes grade 3)
- The system prevents creating bureaucrats with invalid grades (below 1 or above 150)

### Safety Features
- **Error Handling**: If you try to create a bureaucrat with an invalid grade, the program shows an error message
- **Grade Limits**: You cannot increment a grade 1 bureaucrat (they're already at the top)
- **Grade Limits**: You cannot decrement a grade 150 bureaucrat (they're already at the bottom)

### Display Information
- Shows bureaucrat information in a readable format: "Name, bureaucrat grade X"
- Displays clear error messages when something goes wrong

## Example Usage:
- Create a bureaucrat named "Bob" with grade 50
- Increment Bob's grade to make him more powerful
- Try to create a bureaucrat with grade 0 (will show an error)
- Try to increment a grade 1 bureaucrat (will show an error)

This system ensures that bureaucrats always have valid authority levels and provides clear feedback when operations fail.

## Overview
This exercise implements a `Bureaucrat` class that simulates a bureaucratic system with grades and names. The implementation follows the Orthodox Canonical Form and includes proper exception handling.

## Class Structure

### Bureaucrat Class
- **Attributes**:
  - `_name`: Constant string representing the bureaucrat's name
  - `_grade`: Integer representing the bureaucrat's grade (1-150)

### Grade System
- Grade 1 is the highest possible grade
- Grade 150 is the lowest possible grade
- Invalid grades throw exceptions

### Member Functions
- **Constructors**:
  - `Bureaucrat(const std::string& name, int grade)`: Main constructor
  - `Bureaucrat(const Bureaucrat& other)`: Copy constructor
  - `Bureaucrat& operator=(const Bureaucrat& other)`: Assignment operator
  - `~Bureaucrat()`: Destructor

- **Getters**:
  - `getName()`: Returns the bureaucrat's name
  - `getGrade()`: Returns the bureaucrat's grade

- **Grade Management**:
  - `incrementGrade()`: Increases the bureaucrat's grade (decreases the number)
  - `decrementGrade()`: Decreases the bureaucrat's grade (increases the number)

### Exception Classes
- `GradeTooHighException`: Thrown when grade is too high (< 1)
- `GradeTooLowException`: Thrown when grade is too low (> 150)

### Output Format
- Overloaded insertion operator (`<<`) prints: `<name>, bureaucrat grade <grade>`

## Usage Example
```cpp
try {
    Bureaucrat bob("Bob", 2);
    std::cout << bob << std::endl;
    bob.incrementGrade();  // Grade becomes 1
    std::cout << bob << std::endl;
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
- `Bureaucrat.hpp`: Header file containing class declaration
- `Bureaucrat.cpp`: Implementation file
- `main.cpp`: Test program
- `Makefile`: Compilation rules 