
# 📘 C++98-Compliant Standard Library Function Guide for PhoneBook Project

## 🔐 Constraints Recap:
- Must compile with `-std=c++98`
- STL containers (`vector`, `list`, `map`) and `<algorithm>` are **forbidden**
- C++-style standard library functions are **preferred**
- Avoid C-style functions (`printf`, `scanf`, `atoi`, `malloc`, etc.)

---

## 📥 1. User Input Handling

| Function | Header | Description | 💎 Best Choice |
|---------|--------|-------------|----------------|
| `std::getline(std::cin, str)` | `<iostream>` | Safely reads full line, including spaces | ✅ Best and safest choice |
| `std::cin >> var` | `<iostream>` | Reads one word (no spaces) | ❌ Avoid, breaks on spaces |
| `std::cin.fail() / clear() / ignore()` | `<iostream>` | For input stream error handling | ✅ Use with getline if needed |

**Recommended:**
```cpp
std::string input;
std::getline(std::cin, input);
```

---

## 🧮 2. String-to-Integer Conversion

| Method | Header | Description | 💎 Best Choice |
|--------|--------|-------------|----------------|
| `std::stringstream` | `<sstream>` | Safely extract `int` from a string | ✅ Best choice in C++98 |
| `atoi()` | `<cstdlib>` | C-style, no error handling | ❌ Not recommended (C-style) |

**Example:**
```cpp
#include <sstream>
int index;
std::stringstream ss(input);
ss >> index;
```

---

## 🔢 3. Digit Validation (Optional for extra safety)

| Function | Header | Description | 💎 Best Choice |
|---------|--------|-------------|----------------|
| `std::isdigit(char)` | `<cctype>` | Check if a single character is a digit | ✅ Good choice |

---

## 📏 4. Output Formatting (Right-aligned display)

| Function | Header | Description | 💎 Best Choice |
|---------|--------|-------------|----------------|
| `std::cout` | `<iostream>` | Standard output stream | ✅ Use always |
| `std::setw(n)` | `<iomanip>` | Sets width of output | ✅ Best for formatting |
| `std::right / std::left` | `<iomanip>` | Sets alignment | ✅ Use with setw |
| `std::setfill(' ')` | `<iomanip>` | Set padding character | ✅ Optional, useful |

**Example:**
```cpp
std::cout << std::setw(10) << std::right << "Index" << "|";
```

---

## ✂️ 5. String Manipulation

| Function | Header | Description | 💎 Best Choice |
|---------|--------|-------------|----------------|
| `str.length()` / `str.size()` | `<string>` | Get string length | ✅ Use freely |
| `str.substr(start, len)` | `<string>` | Extract substring | ✅ Use for truncateTo10 |
| `str.empty()` | `<string>` | Check if string is empty | ✅ Useful |
| `str.c_str()` | `<string>` | Get C-style string | ✅ Only if needed |

### Helper Function:
```cpp
std::string truncateTo10(const std::string& str) {
    if (str.length() <= 10)
        return str;
    return str.substr(0, 9) + ".";
}
```

---

## ✅ Summary of Best Tools

| Task | 💎 Best Tool | Why |
|------|--------------|-----|
| Full-line input | `std::getline()` | Handles spaces, safe |
| Non-empty check | `str.empty()` | Clean |
| Convert to int | `std::stringstream` | Safe, robust |
| Digit validation | `std::isdigit()` | Optional |
| Table formatting | `std::setw()` + `std::right` | Clean formatting |
| Truncation | `substr()` + helper | Perfect 10-char format |

---

## ✅ Conclusion
All tasks can be implemented cleanly using C++98 standard library functions — no STL containers, no C-style functions required.
