# CPP Module 05 - Exercise 00: Mommy, when I grow up, I want to be a bureaucrat!

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