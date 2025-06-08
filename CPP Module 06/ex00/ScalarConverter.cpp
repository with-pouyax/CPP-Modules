#include "ScalarConverter.hpp"
#include <iomanip>

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter& other) { (void)other; }
ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other) { (void)other; return *this; }
ScalarConverter::~ScalarConverter() {}

bool ScalarConverter::isChar(const std::string& literal) {
    if (literal.length() == 3 && literal[0] == '\'' && literal[2] == '\'')
        return true;
    if (literal.length() == 1 && isprint(literal[0]))
        return true;
    return false;
}

bool ScalarConverter::isInt(const std::string& literal) {
    if (literal.empty()) return false;
    size_t i = 0;
    if (literal[0] == '-' || literal[0] == '+') {
        if (literal.length() == 1) return false;
        i++;
    }
    for (; i < literal.length(); i++) {
        if (!isdigit(literal[i])) return false;
    }
    return true;
}

bool ScalarConverter::isFloat(const std::string& literal) {
    if (literal == "-inff" || literal == "+inff" || literal == "nanf") return true;
    if (literal.empty() || literal[literal.length() - 1] != 'f') return false;
    
    bool hasDot = false;
    bool hasDigit = false;
    size_t i = 0;
    if (literal[0] == '-' || literal[0] == '+') i++;
    
    for (; i < literal.length() - 1; i++) {
        if (literal[i] == '.') {
            if (hasDot) return false;
            hasDot = true;
        } else if (isdigit(literal[i])) {
            hasDigit = true;
        } else {
            return false;
        }
    }
    return hasDot && hasDigit;
}

bool ScalarConverter::isDouble(const std::string& literal) {
    if (literal == "-inf" || literal == "+inf" || literal == "nan") return true;
    if (literal.empty()) return false;
    
    bool hasDot = false;
    bool hasDigit = false;
    size_t i = 0;
    if (literal[0] == '-' || literal[0] == '+') i++;
    
    for (; i < literal.length(); i++) {
        if (literal[i] == '.') {
            if (hasDot) return false;
            hasDot = true;
        } else if (isdigit(literal[i])) {
            hasDigit = true;
        } else {
            return false;
        }
    }
    return hasDot && hasDigit;
}

void ScalarConverter::convertChar(const std::string& literal) {
    char c;
    if (literal.length() == 3)
        c = literal[1];
    else
        c = literal[0];
    
    int i = static_cast<int>(c);
    float f = static_cast<float>(c);
    double d = static_cast<double>(c);

    std::cout << "char: '" << c << "'" << std::endl;
    std::cout << "int: " << i << std::endl;
    std::cout << "float: " << f << ".0f" << std::endl;
    std::cout << "double: " << d << ".0" << std::endl;
}

void ScalarConverter::convertInt(const std::string& literal) {
    long l = std::atol(literal.c_str());
    if (l > std::numeric_limits<int>::max() || l < std::numeric_limits<int>::min()) {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: " << static_cast<float>(l) << ".0f" << std::endl;
        std::cout << "double: " << static_cast<double>(l) << ".0" << std::endl;
        return;
    }

    int i = static_cast<int>(l);
    float f = static_cast<float>(i);
    double d = static_cast<double>(i);

    if (i < 0 || i > 127)
        std::cout << "char: impossible" << std::endl;
    else if (!isprint(i))
        std::cout << "char: Non displayable" << std::endl;
    else
        std::cout << "char: '" << static_cast<char>(i) << "'" << std::endl;
    
    std::cout << "int: " << i << std::endl;
    std::cout << std::fixed << std::setprecision(1) << "float: " << f << "f" << std::endl;
    std::cout << std::fixed << std::setprecision(1) << "double: " << d << std::endl;
}

void ScalarConverter::convertFloat(const std::string& literal) {
    if (literal == "-inff" || literal == "+inff" || literal == "nanf") {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: " << literal << std::endl;
        std::cout << "double: " << literal.substr(0, literal.length() - 1) << std::endl;
        return;
    }

    std::string numStr = literal.substr(0, literal.length() - 1); // Remove 'f'
    double d = std::atof(numStr.c_str());
    
    // Convert max float to string for comparison
    char maxFloatStr[50];
    std::sprintf(maxFloatStr, "%.0f", std::numeric_limits<float>::max());
    std::string maxFloat(maxFloatStr);
    
    // Remove decimal point and trailing zeros for comparison
    size_t dotPos = numStr.find('.');
    if (dotPos != std::string::npos) {
        numStr = numStr.substr(0, dotPos);
    }
    
    if (numStr.length() > maxFloat.length() || 
        (numStr.length() == maxFloat.length() && numStr > maxFloat)) {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: impossible" << std::endl;
        std::cout << "double: " << d << ".0" << std::endl;
        return;
    }

    float f = static_cast<float>(d);

    if (std::isnan(f) || std::isinf(f)) {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
    } else {
        if (f > std::numeric_limits<int>::max() || f < std::numeric_limits<int>::min()) {
            std::cout << "char: impossible" << std::endl;
            std::cout << "int: impossible" << std::endl;
        } else {
            int i = static_cast<int>(f);
            if (i < 0 || i > 127)
                std::cout << "char: impossible" << std::endl;
            else if (!isprint(i))
                std::cout << "char: Non displayable" << std::endl;
            else
                std::cout << "char: '" << static_cast<char>(i) << "'" << std::endl;
            std::cout << "int: " << i << std::endl;
        }
    }
    std::cout << std::fixed << std::setprecision(1) << "float: " << f << "f" << std::endl;
    std::cout << std::fixed << std::setprecision(1) << "double: " << d << std::endl;
}

void ScalarConverter::convertDouble(const std::string& literal) {
    if (literal == "-inf" || literal == "+inf" || literal == "nan") {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: " << literal << "f" << std::endl;
        std::cout << "double: " << literal << std::endl;
        return;
    }

    // Check if the number is too long to be a valid double
    std::string numStr = literal;
    if (numStr[0] == '-') {
        numStr = numStr.substr(1); // Remove minus sign for length check
    }
    
    // Remove decimal point and trailing zeros
    size_t dotPos = numStr.find('.');
    if (dotPos != std::string::npos) {
        numStr = numStr.substr(0, dotPos);
    }
    
    // If the number is longer than 308 digits (DBL_MAX is approximately 1.8e308),
    // it's definitely beyond double range
    if (numStr.length() > 308) {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: impossible" << std::endl;
        std::cout << "double: impossible" << std::endl;
        return;
    }

    double d = std::atof(literal.c_str());
    
    // Check if the value is beyond float range
    if (d > std::numeric_limits<float>::max() || d < -std::numeric_limits<float>::max()) {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: impossible" << std::endl;
        std::cout << "double: " << d << ".0" << std::endl;
        return;
    }

    float f = static_cast<float>(d);

    if (std::isnan(d) || std::isinf(d)) {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
    } else {
        if (d > std::numeric_limits<int>::max() || d < std::numeric_limits<int>::min()) {
            std::cout << "char: impossible" << std::endl;
            std::cout << "int: impossible" << std::endl;
        } else {
            int i = static_cast<int>(d);
            if (i < 0 || i > 127)
                std::cout << "char: impossible" << std::endl;
            else if (!isprint(i))
                std::cout << "char: Non displayable" << std::endl;
            else
                std::cout << "char: '" << static_cast<char>(i) << "'" << std::endl;
            std::cout << "int: " << i << std::endl;
        }
    }
    std::cout << std::fixed << std::setprecision(1) << "float: " << f << "f" << std::endl;
    std::cout << std::fixed << std::setprecision(1) << "double: " << d << std::endl;
}

void ScalarConverter::convert(const std::string& literal) {
    if (isInt(literal))
        convertInt(literal);
    else if (isChar(literal))
        convertChar(literal);
    else if (isFloat(literal))
        convertFloat(literal);
    else if (isDouble(literal))
        convertDouble(literal);
    else {
        std::cout << "Invalid input format" << std::endl;
    }
} 