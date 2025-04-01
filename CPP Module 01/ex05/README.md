
# Harl 2.0 - Complaint Logger with Member Function Pointers

This project automates a character named Harl who complains at different levels such as DEBUG, INFO, WARNING, and ERROR.  
The goal is to use pointers to member functions in C++ to select and invoke these complaint levels dynamically based on input.

---

## Goal

- Implement a `Harl` class that simulates complaint levels:
  - `DEBUG`
  - `INFO`
  - `WARNING`
  - `ERROR`
- Use pointers to member functions to call the correct complaint method without using multiple if-else or switch statements.
- Create a `complain(std::string level)` function that routes the call based on the provided level.

---

## Complaint Levels & Messages

### DEBUG
> "I love having extra bacon for my 7XL-double-cheese-triple-pickle-special-ketchup burger. I really do!"

### INFO
> "I cannot believe adding extra bacon costs more money. You didn’t put enough bacon in my burger! If you did, I wouldn’t be asking for more!"

### WARNING
> "I think I deserve to have some extra bacon for free. I’ve been coming for years, whereas you started working here just last month."

### ERROR
> "This is unacceptable! I want to speak to the manager now."

---

## Class Structure

### Private Member Functions

```cpp
void debug(void);
void info(void);
void warning(void);
void error(void);
```

### Public Member Function

```cpp
void complain(std::string level);
```

This function determines which private function to call using pointers to member functions.

---

## Project Files

- `Makefile`
- `main.cpp`
- `Harl.cpp`
- `Harl.hpp` or `Harl.h`

---

## Testing

You should test the program by calling `Harl::complain` with different level strings.  
Make sure each level triggers the appropriate message.

Example:

```cpp
Harl harl;
harl.complain("DEBUG");
harl.complain("ERROR");
```

---

## Summary

This project strengthens understanding of:

- Class design and encapsulation
- Pointers to member functions
- Clean and dynamic control flow without long chains of conditionals
