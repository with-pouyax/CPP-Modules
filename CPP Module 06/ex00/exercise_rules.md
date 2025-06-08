# Exercise 00: Conversion of scalar types

## Turn-in Requirements
- Directory: `ex00/`
- Files to turn in: `Makefile`, `*.cpp`, `*.{h, hpp}`
- Allowed functions: Any function to convert from a string to an int, a float, or a double

## Task Description
Create a class `ScalarConverter` that will:
- Contain only one static method "convert"
- Take a string parameter representing a C++ literal
- Output its value in the following scalar types:
  - char
  - int
  - float
  - double

## Class Requirements
- The class must not be instantiable by users
- Except for char parameters, only decimal notation will be used

## Input Types to Handle

### Char Literals
- Examples: 'c', 'a', ...
- Non-displayable characters should not be used as inputs
- If conversion to char is not displayable, print an informative message

### Int Literals
- Examples: 0, -42, 42...

### Float Literals
- Examples: 0.0f, -4.2f, 4.2f...
- Must handle pseudo-literals: -inff, +inff, nanf

### Double Literals
- Examples: 0.0, -4.2, 4.2...
- Must handle pseudo-literals: -inf, +inf, nan

## Program Requirements
1. Detect the type of the literal passed as parameter
2. Convert it from string to its actual type
3. Convert it explicitly to the three other data types
4. Display the results

## Error Handling
- If a conversion doesn't make sense or overflows, display a message indicating the type conversion is impossible
- Include necessary headers to handle numeric limits and special values

## Example Outputs

```
./convert 0
char: Non displayable
int: 0
float: 0.0f
double: 0.0

./convert nan
char: impossible
int: impossible
float: nanf
double: nan

./convert 42.0f
char: '*'
int: 42
float: 42.0f
double: 42.0
``` 