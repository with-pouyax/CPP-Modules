#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter& other) { (void)other; }
ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other) { (void)other; return *this; }
ScalarConverter::~ScalarConverter() {}

bool ScalarConverter::isChar(const std::string& literal) {
    return literal.length() == 3 && literal[0] == '\'' && literal[2] == '\'';
}

bool ScalarConverter::isInt(const std::string& literal) {
    if (literal.empty()) return false;
    size_t i = 0;
    if (literal[0] == '-' || literal[0] == '+') i++;
    for (; i < literal.length(); i++) {
        if (!isdigit(literal[i])) return false;
    }
    return true;
}

bool ScalarConverter::isFloat(const std::string& literal) {
    if (literal == "-inff" || literal == "+inff" || literal == "nanf") return true;
    if (literal.empty() || literal[literal.length() - 1] != 'f') return false;
    
    bool hasDot = false;
    size_t i = 0;
    if (literal[0] == '-' || literal[0] == '+') i++;
    
    for (; i < literal.length() - 1; i++) {
        if (literal[i] == '.') {
            if (hasDot) return false;
            hasDot = true;
        } else if (!isdigit(literal[i])) return false;
    }
    return hasDot;
}

bool ScalarConverter::isDouble(const std::string& literal) {
    if (literal == "-inf" || literal == "+inf" || literal == "nan") return true;
    if (literal.empty()) return false;
    
    bool hasDot = false;
    size_t i = 0;
    if (literal[0] == '-' || literal[0] == '+') i++;
    
    for (; i < literal.length(); i++) {
        if (literal[i] == '.') {
            if (hasDot) return false;
            hasDot = true;
        } else if (!isdigit(literal[i])) return false;
    }
    return hasDot;
}

void ScalarConverter::convertChar(const std::string& literal) {
    char c = literal[1];
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
        std::cout << "float: impossible" << std::endl;
        std::cout << "double: impossible" << std::endl;
        return;
    }

    int i = static_cast<int>(l);
    char c = static_cast<char>(i);
    float f = static_cast<float>(i);
    double d = static_cast<double>(i);

    if (i < 32 || i > 126)
        std::cout << "char: Non displayable" << std::endl;
    else
        std::cout << "char: '" << c << "'" << std::endl;
    
    std::cout << "int: " << i << std::endl;
    std::cout << "float: " << f << ".0f" << std::endl;
    std::cout << "double: " << d << ".0" << std::endl;
}

void ScalarConverter::convertFloat(const std::string& literal) {
    if (literal == "-inff" || literal == "+inff" || literal == "nanf") {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: " << literal << std::endl;
        std::cout << "double: " << literal.substr(0, literal.length() - 1) << std::endl;
        return;
    }

    float f = std::atof(literal.c_str());
    char c = static_cast<char>(f);
    int i = static_cast<int>(f);
    double d = static_cast<double>(f);

    if (std::isnan(f) || std::isinf(f)) {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
    } else {
        if (i < 32 || i > 126)
            std::cout << "char: Non displayable" << std::endl;
        else
            std::cout << "char: '" << c << "'" << std::endl;
        std::cout << "int: " << i << std::endl;
    }
    std::cout << "float: " << f << "f" << std::endl;
    std::cout << "double: " << d << std::endl;
}

void ScalarConverter::convertDouble(const std::string& literal) {
    if (literal == "-inf" || literal == "+inf" || literal == "nan") {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: " << literal << "f" << std::endl;
        std::cout << "double: " << literal << std::endl;
        return;
    }

    double d = std::atof(literal.c_str());
    char c = static_cast<char>(d);
    int i = static_cast<int>(d);
    float f = static_cast<float>(d);

    if (std::isnan(d) || std::isinf(d)) {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
    } else {
        if (i < 32 || i > 126)
            std::cout << "char: Non displayable" << std::endl;
        else
            std::cout << "char: '" << c << "'" << std::endl;
        std::cout << "int: " << i << std::endl;
    }
    std::cout << "float: " << f << "f" << std::endl;
    std::cout << "double: " << d << std::endl;
}

void ScalarConverter::convert(const std::string& literal) {
    if (isChar(literal))
        convertChar(literal);
    else if (isInt(literal))
        convertInt(literal);
    else if (isFloat(literal))
        convertFloat(literal);
    else if (isDouble(literal))
        convertDouble(literal);
    else {
        std::cout << "Invalid input format" << std::endl;
    }
} 