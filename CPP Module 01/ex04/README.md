
# Sed is for Losers - File Content Replacer in C++

This project focuses on string manipulation and file handling in C++ without using the `std::string::replace` function.

---

## Goal

Create a program that:

- Takes three command-line arguments:
  1. A filename
  2. A string `s1` to find
  3. A string `s2` to replace `s1` with
- Reads the content of the given file.
- Replaces **all occurrences** of `s1` with `s2`.
- Writes the result into a new file named `<filename>.replace`.

---

## Restrictions

- You are **not allowed** to use `std::string::replace`.
- All other `std::string` member functions **are allowed**.
- Using C-style file handling (e.g., `fopen`, `fread`, `fwrite`) is **not allowed**.
- You must use C++ file streams (`ifstream`, `ofstream`).

---

## Project Files

- `Makefile`
- `main.cpp`
- Other source/header files (`*.cpp`, `*.h`, `*.hpp`)

---

## Program Behavior

Example usage:

```bash
./sed_is_for_losers input.txt hello hi
```

This will:

1. Open `input.txt`
2. Replace all occurrences of `"hello"` with `"hi"`
3. Save the result in `input.txt.replace`

---

## Edge Case Handling

- If the wrong number of arguments is provided, the program should display an error message.
- If the file cannot be opened, the program should handle the error gracefully.
- If `s1` is empty, replacement should not occur (or should return an error).

---

## Tips

- Read the entire file content into a single `std::string`.
- Use a loop with `find()` and `substr()` to build the replaced string manually.
- Create your own test files and test different inputs thoroughly.

---

## Summary

This project is a great way to practice:

- Command-line argument parsing
- File input/output using C++ streams
- Manual string replacement using `find`, `substr`, and concatenation
- Writing clean, testable, and robust code
