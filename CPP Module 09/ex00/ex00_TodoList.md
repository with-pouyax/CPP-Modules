# Exercise 00: BitcoinExchange - Todo List

## 🎯 **Project Overview**
Create a Bitcoin exchange rate calculator that reads historical data from `data.csv` and processes user input files with date-value pairs using `std::map<Date, float>` container.

## ⚠️ **CRITICAL C++ RULES COMPLIANCE**

### **✅ ALLOWED (Module 09):**
- **STL Containers**: `std::map`, `std::string`, `std::vector`, etc.
- **STL Algorithms**: `<algorithm>` header
- **C++ Standard Library**: `std::cout`, `std::cin`, `std::ifstream`, etc.
- **C++98 Standard**: All C++98 features

### **❌ FORBIDDEN (Will result in grade 0 or -42):**
- **C-style functions**: `printf()`, `scanf()`, `malloc()`, `free()`
- **C++11+ features**: `auto`, `nullptr`, `range-based for`, etc.
- **Keywords**: `using namespace std`, `friend`
- **External libraries**: Boost, etc.
- **Function implementation in headers** (except templates)

### **🚨 CRITICAL WARNINGS:**
- **NO `std::isnan()` or `std::isinf()`** - These are C++11 functions!
- **NO `using namespace std`** - Will result in grade -42
- **NO function implementations in .hpp files** - Will result in grade 0
- **MUST have include guards** - Will result in grade 0

## 📋 **Implementation Priority Order**

### **Phase 1: Core Structure & Basic Setup** 🔧
- [ ] **1.1** Create project structure
  - [ ] Create `ex00/` directory
  - [ ] Create `Makefile`
  - [ ] Create `main.cpp`
  - [ ] Create `BitcoinExchange.hpp`
  - [ ] Create `BitcoinExchange.cpp`

- [ ] **1.2** Basic Makefile setup
  - [ ] Compiler flags: `-Wall -Wextra -Werror -std=c++98`
  - [ ] Dependency flags: `-MMD -MP` for automatic dependency generation
  - [ ] Target: `btc` (program name)
  - [ ] Source files: `main.cpp BitcoinExchange.cpp`
  - [ ] Header files: `BitcoinExchange.hpp`
  - [ ] Object files: `$(SRCS:.cpp=.o)`
  - [ ] Dependency files: `$(SRCS:.cpp=.d)`
  - [ ] Include dependency files: `-include $(DEPS)`
  - [ ] Clean target (remove .o and .d files)
  - [ ] Fclean target (remove executable too)
  - [ ] Re target (fclean + all)
  - [ ] **⚠️ MUST compile with c++ compiler (not g++)**

- [ ] **1.3** Basic class structure
  - [ ] Define `BitcoinExchange` class
  - [ ] Private member: `std::map<Date, float> _data`
  - [ ] Constructor/Destructor
  - [ ] Copy constructor/Assignment operator (if needed)
  - [ ] **⚠️ Include guards in .hpp file**

### **Phase 2: Date Class Implementation** 📅
- [ ] **2.1** Create `Date` class
  - [ ] Private members: `int _year`, `int _month`, `int _day`
  - [ ] Constructor: `Date(const std::string& dateStr)`
  - [ ] Destructor
  - [ ] Copy constructor
  - [ ] Assignment operator
  - [ ] Comparison operators (`<`, `<=`, `==`, `!=`, `>`, `>=`)
  - [ ] **⚠️ Orthodox Canonical Form compliance**

- [ ] **2.2** Date validation methods
  - [ ] `bool isValidFormat(const std::string& dateStr)`
    - [ ] Check length (exactly 10 characters)
    - [ ] Check hyphens at positions 4 and 7
    - [ ] Check all other characters are digits
  - [ ] `bool isValidDate() const`
    - [ ] Validate year range (reasonable bounds)
    - [ ] Validate month (1-12)
    - [ ] Validate day for specific month
    - [ ] **Leap year validation**
      - [ ] Years divisible by 4 but not 100 are leap years
      - [ ] Years divisible by 400 are leap years
    - [ ] Month-specific day limits:
      - [ ] February: 28 days (29 in leap years)
      - [ ] April, June, September, November: 30 days
      - [ ] January, March, May, July, August, October, December: 31 days

- [ ] **2.3** Date parsing
  - [ ] `void parseDate(const std::string& dateStr)`
  - [ ] Extract year, month, day from string
  - [ ] Handle parsing errors

### **Phase 3: Value Validation** 💰
- [ ] **3.1** Basic value validation
  - [ ] `bool isValidValue(const std::string& valueStr, float& value)`
  - [ ] Check for empty values
  - [ ] Check for non-numeric characters (except allowed ones)
  - [ ] Parse string to float using `std::strtof` (C++98 compatible)

- [ ] **3.2** Range validation
  - [ ] Check negative values: `Error: not a positive number.`
  - [ ] Check values > 1000: `Error: too large a number.`
  - [ ] **String-based boundary checking for precision issues**
    - [ ] For values == 1000, check string after "1000" for non-zero digits
    - [ ] Handle cases like `1000.00000000001`

- [ ] **3.3** Format validation
  - [ ] Check for multiple decimal points
  - [ ] Check for leading/trailing decimal points
  - [ ] **Scientific notation support**
    - [ ] Allow `eE+-` characters
    - [ ] Validate scientific notation format
    - [ ] Check exponent bounds

- [ ] **3.4** Floating-point edge cases (CRITICAL - C++98 COMPLIANT)
  - [ ] **NaN/Inf detection (C++98 APPROACH)**
    - [ ] **⚠️ DO NOT USE `std::isnan()` or `std::isinf()`** (C++11 functions)
    - [ ] Use manual checks: `value != value` for NaN detection
    - [ ] Use manual checks: `value > FLT_MAX || value < -FLT_MAX` for Inf detection
    - [ ] Error message: `Error: invalid value => [value]`
  - [ ] **Overflow detection in calculations**
    - [ ] Check result after multiplication using manual bounds checking
    - [ ] Error message: `Error: calculation overflow`
  - [ ] **Underflow detection**
    - [ ] Check if result is 0 when inputs are non-zero
    - [ ] Error message: `Error: calculation underflow`

### **Phase 4: CSV Database Loading** 📊
- [ ] **4.1** CSV file handling
  - [ ] `void loadDatabase(const std::string& filename)`
  - [ ] Open and read `data.csv` using `std::ifstream`
  - [ ] Handle file not found: `Error: could not open file.`
  - [ ] Handle empty file: `Error: empty input file`

- [ ] **4.2** CSV parsing
  - [ ] Skip header line if present
  - [ ] Parse each line: `date,exchange_rate`
  - [ ] Validate CSV format (comma separator)
  - [ ] Handle malformed CSV lines

- [ ] **4.3** Data storage
  - [ ] Create `Date` object from date string
  - [ ] Parse exchange rate to float
  - [ ] Store in `std::map<Date, float> _data`
  - [ ] Handle duplicate dates (overwrite or error)
  - [ ] Handle negative exchange rates (throw runtime error)

### **Phase 5: Input File Processing** 📁
- [ ] **5.1** File validation
  - [ ] Check command line arguments
  - [ ] Handle no arguments: `Error: could not open file.`
  - [ ] Open input file using `std::ifstream`
  - [ ] Handle file not found: `Error: could not open file.`
  - [ ] Handle empty file: `Error: empty input file`

- [ ] **5.2** Line parsing
  - [ ] Read file line by line using `std::getline`
  - [ ] Skip empty lines
  - [ ] Parse format: `"date | value"`
  - [ ] Handle missing separator: `Error: bad input => [line]`
  - [ ] Handle extra characters after date: `Invalid date format`

- [ ] **5.3** Input validation
  - [ ] Validate date format and content
  - [ ] Validate value format and range
  - [ ] Handle all edge cases from Phase 3

### **Phase 6: Date Lookup & Calculation** 🔍
- [ ] **6.1** Date lookup algorithm
  - [ ] Use `std::map::lower_bound()` for efficient lookup
  - [ ] Handle exact date match
  - [ ] Handle no exact match (use closest previous date)
  - [ ] Handle date before first entry: `Error: no earlier data available`

- [ ] **6.2** Calculation
  - [ ] Multiply input value by exchange rate
  - [ ] Format output: `date => value = result`
  - [ ] Handle precision in output (reasonable decimal places)

### **Phase 7: Main Function & Integration** 🚀
- [ ] **7.1** Main function structure
  - [ ] Check command line arguments
  - [ ] Create `BitcoinExchange` object
  - [ ] Load database
  - [ ] Process input file
  - [ ] Handle exceptions

- [ ] **7.2** Error handling
  - [ ] Try-catch blocks for file operations
  - [ ] Try-catch blocks for parsing operations
  - [ ] Graceful error messages
  - [ ] **⚠️ CRITICAL: Continue processing after individual line errors**
  - [ ] **⚠️ Program must NOT stop execution before processing entire file**

### **Phase 8: Testing & Edge Cases** 🧪
- [ ] **8.1** Create test files
  - [ ] `input.txt` with various edge cases
  - [ ] Test all 19 edge cases identified
  - [ ] Test normal cases
  - [ ] Test boundary conditions
  - [ ] **⚠️ Create `input.csv` file for evaluation testing**

- [ ] **8.2** Edge case testing
  - [ ] **Date validation (5 cases)**
    - [ ] Invalid format, invalid months, invalid days
    - [ ] Leap year validation
    - [ ] Non-digit characters
  - [ ] **Value validation (7 cases)**
    - [ ] Negative values, values > 1000
    - [ ] String-based boundary checking
    - [ ] Multiple decimal points, leading/trailing decimals
    - [ ] Scientific notation
    - [ ] Empty values
  - [ ] **File handling (4 cases)**
    - [ ] File not found, empty file
    - [ ] Missing separator, extra characters
  - [ ] **Floating-point (3 cases)**
    - [ ] NaN/Inf detection (C++98 compliant)
    - [ ] Overflow/underflow detection

- [ ] **8.3** Evaluation-specific testing
  - [ ] **Empty file test**: Program must handle empty input file
  - [ ] **File with errors test**: Program must process entire file despite errors
  - [ ] **Wrong date test**: Invalid dates should be handled gracefully
  - [ ] **Value > 1000 test**: Must reject values greater than 1000
  - [ ] **Value < 0 test**: Must reject negative values
  - [ ] **input.csv test**: Must work with the evaluation file
  - [ ] **Nearest lower date test**: Must use closest previous date when exact match not found

### **Phase 9: Code Quality & Standards** ✨
- [ ] **9.1** Code formatting
  - [ ] Follow C++98 standards
  - [ ] Proper indentation and spacing
  - [ ] Consistent naming conventions
  - [ ] Clear variable names
  - [ ] **⚠️ NO `using namespace std`**

- [ ] **9.2** Documentation
  - [ ] Header comments for classes
  - [ ] Function documentation
  - [ ] Complex algorithm explanations
  - [ ] Edge case handling comments

- [ ] **9.3** Memory management
  - [ ] Proper destructors
  - [ ] No memory leaks
  - [ ] RAII principles
  - [ ] Exception safety

### **Phase 10: Final Testing & Validation** ✅
- [ ] **10.1** Compilation testing
  - [ ] Clean compilation with all flags: `-Wall -Wextra -Werror -std=c++98`
  - [ ] No warnings
  - [ ] Proper linking
  - [ ] **⚠️ MUST compile with `c++` compiler (not g++)**

- [ ] **10.2** Functional testing
  - [ ] Test with provided example
  - [ ] Test with edge cases
  - [ ] Test with large files
  - [ ] Test error conditions
  - [ ] **⚠️ Test with `input.csv` file**

- [ ] **10.3** Performance testing
  - [ ] Test with large datasets
  - [ ] Verify map lookup efficiency
  - [ ] Memory usage validation

- [ ] **10.4** Evaluation preparation
  - [ ] **Prepare explanation for container choice** (std::map)
  - [ ] **Test error handling robustness**
  - [ ] **Verify nearest lower date functionality**
  - [ ] **Create test cases for manual date comparison**

## 🚨 **CRITICAL IMPLEMENTATION NOTES**

### **Container Usage**
- **Primary Container**: `std::map<Date, float> _data`
- **Key Benefits**: Automatic sorting, efficient lookup with `lower_bound()`
- **No other containers**: This container cannot be reused in other exercises
- **⚠️ MUST explain container choice during evaluation**

### **C++98 Floating-Point Validation (CRITICAL)**
```cpp
// ❌ FORBIDDEN (C++11):
if (std::isnan(value) || std::isinf(value)) { ... }

// ✅ CORRECT (C++98):
if (value != value) { // NaN detection
    std::cerr << "Error: invalid value => " << valueStr << std::endl;
    return false;
}
if (value > FLT_MAX || value < -FLT_MAX) { // Inf detection
    std::cerr << "Error: invalid value => " << valueStr << std::endl;
    return false;
}
```

### **Error Handling Priority**
1. **File operations** (highest priority)
2. **Date validation** (critical for lookup)
3. **Value validation** (critical for calculations)
4. **Floating-point edge cases** (critical for robustness)
5. **⚠️ CRITICAL: Continue processing entire file despite errors**

### **Performance Considerations**
- Use `lower_bound()` for O(log n) date lookup
- Efficient string parsing
- Minimal memory allocations
- Exception-safe operations

### **Testing Strategy**
- Test each edge case individually
- Test combinations of edge cases
- Test with real data.csv file
- Test error recovery (continue after errors)
- **⚠️ Test with evaluation `input.csv` file**

## 📊 **Progress Tracking**

| Phase | Status | Priority | Estimated Time |
|-------|--------|----------|----------------|
| Phase 1 | ⏳ Pending | High | 30 min |
| Phase 2 | ⏳ Pending | High | 2 hours |
| Phase 3 | ⏳ Pending | High | 1.5 hours |
| Phase 4 | ⏳ Pending | High | 1 hour |
| Phase 5 | ⏳ Pending | High | 1 hour |
| Phase 6 | ⏳ Pending | High | 30 min |
| Phase 7 | ⏳ Pending | Medium | 30 min |
| Phase 8 | ⏳ Pending | Medium | 1 hour |
| Phase 9 | ⏳ Pending | Low | 30 min |
| Phase 10 | ⏳ Pending | High | 30 min |

**Total Estimated Time: ~9 hours**

## 🎯 **Success Criteria**

- [ ] Program compiles without warnings with `-Wall -Wextra -Werror -std=c++98`
- [ ] All 19 edge cases handled correctly
- [ ] Proper error messages for each failure case
- [ ] Efficient date lookup using map container
- [ ] Robust floating-point handling (C++98 compliant)
- [ ] Clean, readable code following C++98 standards
- [ ] No memory leaks
- [ ] Exception-safe operations
- [ ] **⚠️ NO forbidden functions used**
- [ ] **⚠️ Include guards in all headers**
- [ ] **⚠️ Orthodox Canonical Form compliance**
- [ ] **⚠️ Program processes entire file despite errors**
- [ ] **⚠️ Uses nearest lower date when exact match not found**
- [ ] **⚠️ Handles empty files and files with errors**

## 🚨 **FINAL WARNINGS**

### **Functions that will cause grade 0:**
- `printf()`, `scanf()`, `malloc()`, `free()`
- Function implementations in .hpp files
- Missing include guards

### **Functions that will cause grade -42:**
- `using namespace std`
- `friend` keyword
- `std::isnan()`, `std::isinf()` (C++11 functions)

### **C++98 Compliance:**
- Use `std::strtof` instead of `std::stof` (C++11)
- Manual NaN/Inf detection instead of `std::isnan()`/`std::isinf()`
- No `auto`, `nullptr`, range-based for loops

### **Evaluation Requirements:**
- **Must compile with `c++` compiler (not g++)**
- **Must use at least one container (std::map)**
- **Must explain container choice during evaluation**
- **Must handle empty files and files with errors**
- **Must process entire file before stopping**
- **Must use nearest lower date when exact match not found**
- **Must work with `input.csv` file provided by evaluator** 