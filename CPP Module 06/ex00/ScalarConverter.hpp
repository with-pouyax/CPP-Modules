#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>
#include <iostream>
#include <limits>
#include <cstdlib>
#include <cmath>
#include <cerrno>
#include <cstdio>
#include <iomanip>

class ScalarConverter {
private:
    //constructor and destructor are private because we don't want to create an instance of the class
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
    //since the class is static(means we can't create an instance of the class)
    // using static for the methods we can call this methods without creating an instance of the class
    static void convert(const std::string& literal);
};

#endif 