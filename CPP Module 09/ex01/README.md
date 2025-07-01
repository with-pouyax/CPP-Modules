# Exercise 01: Reverse Polish Notation (RPN)

## Overview
A C++ program that evaluates Reverse Polish Notation expressions using a custom stack implementation with `std::list` as the underlying container.

## Program Usage
```bash
./RPN "<RPN expression>"
```

## Requirements Checklist

### ✅ Basic Requirements
- [x] Program name: `RPN`
- [x] Takes RPN expression as argument (only 1 string) like "1 1 +"
- [x] Numbers in input < 10 (single digits only) (-9 to 9)
- [x] Handles operators: `+ - / *`
- [x] Outputs result to stdout
- [x] Error messages to stderr

### ✅ Container Usage
- [x] Uses at least one container ✅ (`std::list` in custom Stack)
- [x] Avoids `std::deque` for future exercises ✅

### ✅ 42 School Standards
- [x] Orthodox Canonical Form ✅
- [x] Include guards ✅
- [x] No forbidden functions ✅
- [x] Proper Makefile targets ✅
- [x] Compiles with `-std=c++98` ✅

### ✅ Error Handling
- [x] Invalid tokens → "Error"
- [x] Division by zero → "Error"
- [x] Insufficient operands → "Error"
- [x] Too many operands → "Error"
- [x] Invalid arguments → "Error"

## Test Cases

### Valid Expressions
```bash
./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"  # Output: 42
./RPN "7 7 * 7 -"                  # Output: 42
./RPN "1 2 * 2 / 2 * 2 4 - +"     # Output: 0
./RPN "5 3 +"                      # Output: 8
```

### Error Cases
```bash
./RPN "(1 + 1)"                    # Error: Invalid token
./RPN "10 2 /"                     # Error: Number ≥ 10
./RPN "1 0 /"                      # Error: Division by zero
./RPN "1 +"                        # Error: Insufficient operands
./RPN "1 2 3"                      # Error: Too many operands
./RPN                              # Error: Missing arguments
```

## Implementation Details

### Custom Stack Class
- Uses `std::list` as underlying container
- Template-based implementation
- Standard stack operations: `push`, `pop`, `top`, `empty`, `size`

### RPN Class
- Orthodox Canonical Form implementation
- Token validation for single digits (-9-9)
- Operator validation (`+`, `-`, `*`, `/`)
- Comprehensive error handling

## Build Instructions
```bash
make        # Build the program
make clean  # Remove object files
make fclean # Remove object files and executable
make re     # Rebuild everything
```

## Files
- `RPN.hpp` - Header file with Stack template and RPN class declaration
- `RPN.cpp` - Implementation of RPN class methods
- `main.cpp` - Main program with argument handling
- `Makefile` - Build configuration

## Status: ✅ READY FOR SUBMISSION 