# Exercise 01: Moar brainz!

## Description
This exercise focuses on array allocation and memory management by creating a horde of zombies. We implement a function that creates multiple zombie objects in a single allocation.

## Requirements
- Implement `zombieHorde(int N, std::string name)` function that:
  - Allocates N Zombie objects in a single allocation
  - Initializes each zombie with the given name
  - Returns a pointer to the first zombie

## Key Concepts
- Array allocation
- Memory management
- Proper cleanup of allocated memory
- Testing for memory leaks

## Important Notes
- Must use a single allocation for all zombies
- Must properly deallocate all zombies using delete
- Should test the horde by calling announce() for each zombie
- Must check for memory leaks

## Files Required
- Makefile
- main.cpp
- Zombie.hpp
- Zombie.cpp
- zombieHorde.cpp 