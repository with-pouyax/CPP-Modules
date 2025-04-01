
# HI THIS IS BRAIN - String Pointer and Reference

This project introduces the use of pointers and references in C++ by working with a single string variable.

---

## Goal

- Create a string variable initialized to `"HI THIS IS BRAIN"`.
- Create a pointer that points to the string variable.
- Create a reference to the same string variable.
- Display both memory addresses and values to understand how pointers and references work in practice.

---

## Implementation

Your program should:

- Declare a `std::string` variable with the value `"HI THIS IS BRAIN"`.
- Declare `stringPTR` as a pointer to the string.
- Declare `stringREF` as a reference to the string.

Print the following:

1. The memory address of the string variable.
2. The memory address held by `stringPTR`.
3. The memory address held by `stringREF`.

Then print:

1. The value of the string variable.
2. The value pointed to by `stringPTR`.
3. The value pointed to by `stringREF`.

---

## Project Files

- `Makefile`
- `main.cpp`

---

## Example Output

```text
Memory address of the string variable:      0x7ffee3b2f3c8
Memory address held by stringPTR:           0x7ffee3b2f3c8
Memory address held by stringREF:           0x7ffee3b2f3c8

Value of the string variable:               HI THIS IS BRAIN
Value pointed to by stringPTR:              HI THIS IS BRAIN
Value pointed to by stringREF:              HI THIS IS BRAIN
```

Note: Actual addresses will vary each time you run the program.

---

## Summary

This project helps clarify the difference (and similarity) between pointers and references.  
It reinforces the concept of address manipulation and highlights how references serve as aliases for existing variables with cleaner syntax.
