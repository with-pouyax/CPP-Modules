# Exercise 00: BraiiiiiiinnnzzzZ

## Description
This exercise focuses on memory allocation and object lifecycle management in C++. We implement a simple Zombie class and two functions to create zombies either on the heap or stack.

## Requirements
- Create a `Zombie` class with:
  - Private string attribute `name`
  - Constructor that takes a name
  - Destructor that prints zombie's name
  - `announce()` function that prints: `<name>: BraiiiiiiinnnzzzZ...`

- Implement two functions:
  1. `newZombie(std::string name)`: Creates a zombie on the heap and returns a pointer
  2. `randomChump(std::string name)`: Creates a zombie on the stack and makes it announce itself

## Key Concepts
- Stack vs Heap allocation
- Object lifecycle management
- Memory management (proper cleanup)
- Constructor and destructor usage

## Files Required
- Makefile
- main.cpp
- Zombie.hpp
- Zombie.cpp
- newZombie.cpp
- randomChump.cpp