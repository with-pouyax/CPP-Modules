# CPP-Modules


# **General Rules**

## **1. Compiling**
- Compile your code using `c++` with the flags: `-Wall -Wextra -Werror`.
- Your code should still compile when adding the flag: `-std=c++98`.

---

## **2. Formatting and Naming Conventions**
- **Directories**: Exercise directories must be named `ex00`, `ex01`, ..., `exn`.
- **Files and Classes**:
  - Class names must be in **UpperCamelCase** format.
  - Files containing class code must match the class name, e.g.:
    - `ClassName.hpp` / `ClassName.h` for headers.
    - `ClassName.cpp` for implementation.
    - `ClassName.tpp` for template classes (if applicable).
  - Example: For a class `BrickWall`, files would be `BrickWall.hpp` and `BrickWall.cpp`.
- **Output Messages**:
  - All output messages must end with a newline (`\n`).
  - Messages must be displayed to the **standard output**.
- **Coding Style**:
  - No enforced coding style (e.g., no Norminette).
  - Write **clean and readable code** for peer evaluation.

---

## **3. Allowed/Forbidden**
### **Allowed**
- Use the **C++ standard library** (except where explicitly forbidden).
- Use C++-specific versions of C functions where possible.

### **Forbidden**
- **C++11** (and derived forms) and **Boost libraries**.
- Functions: `*printf()`, `*alloc()`, and `free()`.
- Using `using namespace <ns_name>` or the `friend` keyword.
- **STL (Standard Template Library)**:
  - **Modules 00–07**: No containers (`vector`, `list`, etc.) or algorithms (from `<algorithm>` header).
  - STL is allowed starting **Module 08**.
- Function implementations in header files (except for templates).
- Headers missing include guards or improper dependency handling.

---

## **4. Memory Management**
- Avoid memory leaks.
- Use proper memory management when allocating memory with `new`.

---

## **5. Design Requirements**
- **Orthodox Canonical Form**:
  - Follow this from **Module 02–09**, unless explicitly stated otherwise.
- **Header Files**:
  - Each header must work independently (include all its dependencies).
  - Prevent double inclusion using include guards (`#ifndef / #define`).
- Improper practices (e.g., missing include guards or dependency issues) will result in a **0** grade.

---

## **6. Additional Notes**
- You may add additional files if necessary to split code logically.
- Examples in exercises may show implicit requirements—study them carefully.
- Read the entire module before starting any exercise.
- Scripting your editor for repetitive tasks (like creating classes) can save time.

---

## **7. Guidelines for Success**
- Pay attention to:
  - Proper formatting.
  - Readability for peer evaluators.
- Use theoretical concepts and avoid shortcuts to gain deeper understanding.
- Follow mandatory rules and take the time to complete exercises properly.
