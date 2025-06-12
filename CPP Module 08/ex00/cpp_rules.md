
# C++ Rules Summary

This document summarizes all important rules and recommendations for completing C++  at 42 school.

---

## Compilation

- Compile with `c++` using the following flags:
```bash
c++ -Wall -Wextra -Werror
```
- Your code must also compile with the `-std=c++98` flag.

---

## Formatting and Naming Conventions

- Directory names: `ex00`, `ex01`, ..., `exn`
- Class names: **UpperCamelCase**.
  - Files must match class names exactly:
    ```
    ClassName.hpp
    ClassName.cpp
    ClassName.tpp
    ```
  Example:
    ```
    BrickWall.hpp, BrickWall.cpp
    ```
- Every output line must end with a newline (`\n`) character.
- No strict coding style enforced, but write clean, readable, and understandable code.

---

## Allowed and Forbidden

### ✅ **Allowed:**
- Most C++ standard library functions, except STL containers (`vector`, `list`, `map`, etc.) and algorithms (`<algorithm>`) until Module 08.
- Always prefer **C++-style standard library functions** over **C-style functions**.

### ❌ **Explicitly Forbidden:**
- External libraries: **C++11, Boost, etc.**
- Specific functions: `*printf()`, `*alloc()`, `free()` (Grade = 0)
- Keywords:
  - `using namespace <ns_name>`
  - `friend`
  (Grade = -42)

---

## Design Requirements

- Prevent memory leaks using `new`/`delete` correctly.
- From Module 02 onwards, classes must follow the **Orthodox Canonical Form**.
- **No function implementation in header files** except for template functions (otherwise, grade = 0).
- Each header file must have **include guards** to avoid double inclusion (otherwise, grade = 0).

Example of include guards:
```cpp
#ifndef BRICKWALL_HPP
#define BRICKWALL_HPP

// Your code here

#endif // BRICKWALL_HPP
```

---

## Makefile Requirements

Follow standard 42 Makefile conventions:

- Mandatory targets: `all`, `clean`, `fclean`, `re`.
- No unnecessary recompilations or relinking.

---

## Recommendations and Tips

- You may add additional helper files as needed (mandatory files must be submitted).
- Carefully read and understand module instructions and provided examples.
- **Use your logic and reasoning!**

---

## Understanding C++ vs. C Functions

Prefer **C++ standard library features** instead of old C functions:

| Task                 | ✅ C++ style                  | ❌ C style                     |
|----------------------|-------------------------------|---------------------------------|
| Printing             | `std::cout`                   | `printf()`                      |
| Input                | `std::cin`                    | `scanf()`                       |
| String manipulation  | `std::string`                 | `strcpy(), strcat(), strlen()`  |
| Memory allocation    | `new/delete`                  | `malloc()/free()`               |

### Examples:

#### ✅ **Correct C++ Example**
```cpp
#include <iostream>
#include <string>

int main() {
    std::string name;
    std::cout << "Enter your name: ";
    std::cin >> name;
    std::cout << "Hello, " << name << "!" << std::endl;
}
```

#### ❌ **Incorrect C-style Example**
```cpp
#include <stdio.h>

int main() {
    char name[50];
    printf("Enter your name: ");
    scanf("%49s", name);
    printf("Hello, %s!\n", name);
}
```

---

## Penalty Summary

| Violation                                                   | Penalty   |
|-------------------------------------------------------------|-----------|
| Using forbidden functions (`*printf()`, `*alloc()`, `free()`) | Grade 0   |
| Using `using namespace` or `friend` keywords                | Grade -42 |
| Using STL before Module 08                                  | Grade -42 |
| Function implementation inside header files (except templates)| Grade 0   |
| Missing include guards                                      | Grade 0   |

---

Follow these rules carefully to ensure successful submission of Module 00.

