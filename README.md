![C++ GIF](https://media3.giphy.com/media/v1.Y2lkPTc5MGI3NjExM2R1Mm52ZHJ2bWZ5bTJ1Y3d5bDRwYzNmdzVpbDFybG0xY2NsaHJ3eiZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/QpVUMRUJGokfqXyfa1/giphy.gif)

# **CPP-Modules**

## **What are CPP-Modules?**
CPP-Modules are a series of structured exercises designed by **42 School** to teach fundamental and advanced C++ concepts. They follow a progressive approach, ensuring students develop a deep understanding of object-oriented programming, memory management, and proper coding practices. Each module consists of multiple exercises that build upon previous knowledge, helping students master the language step by step.

I am working on **CPP Modules 00 to 09** from **42**. Each module consists of multiple exercises, and inside each exercise folder, I provide an explanation of its content and purpose.

---

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
