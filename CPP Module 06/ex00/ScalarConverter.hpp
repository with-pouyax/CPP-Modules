#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>
#include <iostream>
#include <limits>
#include <cstdlib>
#include <cmath>
#include <cerrno>
#include <cstdio>

class ScalarConverter {
private:
    ScalarConverter();
    ScalarConverter(const ScalarConverter& other);
    ScalarConverter& operator=(const ScalarConverter& other);
    ~ScalarConverter();

    static bool isChar(const std::string& literal);
    static bool isInt(const std::string& literal);
    static bool isFloat(const std::string& literal);
    static bool isDouble(const std::string& literal);
    
    static void convertChar(const std::string& literal);
    static void convertInt(const std::string& literal);
    static void convertFloat(const std::string& literal);
    static void convertDouble(const std::string& literal);

public:
    static void convert(const std::string& literal);
};

#endif 