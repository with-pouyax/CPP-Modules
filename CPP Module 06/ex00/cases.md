# ScalarConverter Test Cases

## Basic Number Tests
```bash
./convert 10
char: Non displayable
int: 10
float: 10.0f
double: 10.0

./convert 10.0
char: Non displayable
int: 10
float: 10.0f
double: 10.0

./convert 42
char: '*'
int: 42
float: 42.0f
double: 42.0

./convert 0
char: Non displayable
int: 0
float: 0.0f
double: 0.0

./convert -0
char: Non displayable
int: 0
float: 0.0f
double: 0.0

./convert 1
char: Non displayable
int: 1
float: 1.0f
double: 1.0

./convert 32
char: ' '
int: 32
float: 32.0f
double: 32.0

./convert 127
char: Non displayable
int: 127
float: 127.0f
double: 127.0
```

## Integer Edge Cases
```bash
./convert +00042
char: '*'
int: 42
float: 42.0f
double: 42.0

./convert -00042
char: impossible
int: -42
float: -42.0f
double: -42.0

./convert 2147483647
char: impossible
int: 2147483647
float: 2147483648.0f
double: 2147483647.0

./convert -2147483648
char: impossible
int: -2147483648
float: -2147483648.0f
double: -2147483648.0
```

## Float Tests
```bash
./convert 42.0f
char: '*'
int: 42
float: 42.0f
double: 42.0

./convert 0.0f
char: Non displayable
int: 0
float: 0.0f
double: 0.0

./convert -0.0f
char: Non displayable
int: 0
float: -0.0f
double: -0.0

./convert +inff
char: impossible
int: impossible
float: +inff
double: +inf

./convert -inff
char: impossible
int: impossible
float: -inff
double: -inf

./convert nanf
char: impossible
int: impossible
float: nanf
double: nan

./convert 999999999999999999999999999.0f
char: impossible
int: impossible
float: 999999988484154753734934528.0f
double: 1000000000000000013287555072.0
```

## Double Tests
```bash
./convert 42.0
char: '*'
int: 42
float: 42.0f
double: 42.0

./convert 0.0
char: Non displayable
int: 0
float: 0.0f
double: 0.0

./convert -0.0
char: Non displayable
int: 0
float: -0.0f
double: -0.0

./convert +inf
char: impossible
int: impossible
float: +inff
double: +inf

./convert -inf
char: impossible
int: impossible
float: -inff
double: -inf

./convert nan
char: impossible
int: impossible
float: nanf
double: nan

./convert 999999999999999999999999999.0
char: impossible
int: impossible
float: 999999988484154753734934528.0f
double: 1000000000000000013287555072.0
```

## Character Tests
```bash
./convert a
char: 'a'
int: 97
float: 97.0f
double: 97.0

./convert '*'
char: '*'
int: 42
float: 42.0f
double: 42.0

./convert ' '
char: ' '
int: 32
float: 32.0f
double: 32.0

./convert '~'
char: '~'
int: 126
float: 126.0f
double: 126.0

./convert 'Z'
char: 'Z'
int: 90
float: 90.0f
double: 90.0

./convert '+'
char: '+'
int: 43
float: 43.0f
double: 43.0

./convert '-'
char: '-'
int: 45
float: 45.0f
double: 45.0
```

## Weird but Legal Formats
```bash
./convert 42.
char: '*'
int: 42
float: 42.0f
double: 42.0

./convert .0
char: Non displayable
int: 0
float: 0.0f
double: 0.0

./convert .0f
char: Non displayable
int: 0
float: 0.0f
double: 0.0

./convert +00042.00f
char: '*'
int: 42
float: 42.0f
double: 42.0

./convert -00042.00
char: impossible
int: -42
float: -42.0f
double: -42.0
```

## Invalid Inputs (should show "Invalid input format")
```bash
./convert 4.2e1
Invalid input format

./convert 0x2A
Invalid input format

./convert ''
Invalid input format

./convert 'ab'
Invalid input format

./convert "   42"
Invalid input format
```

## Invalid Float/Double Formats
```bash
./convert .f
Invalid input format

./convert .0f.
Invalid input format
```




## Max Values and Overflow Tests
```bash
# Integer Max Values
./convert 2147483647
char: impossible
int: 2147483647
float: 2147483648.0f
double: 2147483647.0

./convert -2147483648
char: impossible
int: -2147483648
float: -2147483648.0f
double: -2147483648.0


# Integer Overflow
./convert 2147483648
char: impossible
int: impossible
float: 2147483648.0f
double: 2147483648.0

./convert -2147483649
char: impossible
int: impossible
float: -2147483649.0f
double: -2147483649.0



# Float Max Values
./convert 340282346638528859811704183484516925440.0f
char: impossible
int: impossible
float: 340282346638528859811704183484516925440.0f
double: 340282346638528859811704183484516925440.0

./convert -340282346638528859811704183484516925440.0f
char: impossible
int: impossible
float: -340282346638528859811704183484516925440.0f
double: -340282346638528859811704183484516925440.0


# Float Overflow
./convert 340282346638528859811704183484516925441.0f
char: impossible
int: impossible
float: impossible
double: 340282346638528859811704183484516925441.0

./convert -340282346638528859811704183484516925441.0f
char: impossible
int: impossible
float: impossible
double: -340282346638528859811704183484516925441.0


# Double Max Values
./convert 179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.0
char: impossible
int: impossible
float: impossible
double: 179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.0

./convert -179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.0
char: impossible
int: impossible
float: impossible
double: -179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.0

# Double Overflow
./convert 179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858369.0
char: impossible
int: impossible
float: impossible
double: impossible

./convert -179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858369.0
char: impossible
int: impossible
float: impossible
double: impossible