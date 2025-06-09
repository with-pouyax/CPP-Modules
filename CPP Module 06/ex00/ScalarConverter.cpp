#include "ScalarConverter.hpp"


//#############################   IMPLEMENTATION   #############################
//
//   we conver everything using static_cast because in subject it asked:
//   to convert input explicitly to the three other data types
//   - the benefit of using static_cast is that it is a safe way to convert between different data types
//   - Even when we uppercast, although we can do it implicitly, it is better to use static_cast to be explicit
//##############################################################################


//----------------------------------------------------------------------------------------
// constructor, copy constructor, assignment operator and destructor are private because we don't want to create an instance of the class
// so we just write the function declaration and not the implementation

ScalarConverter::ScalarConverter() {} //constructor is private so we don't need to implement it
ScalarConverter::ScalarConverter(const ScalarConverter& other) { (void)other; }
ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other) { (void)other; return *this; }
ScalarConverter::~ScalarConverter() {}

//----------------------------------------------------------------------------------------



bool ScalarConverter::isInt(const std::string& literal) {
    if (literal.empty()) return false;                 //if the literal is empty, return false
    size_t i = 0;
    if (literal[0] == '-' || literal[0] == '+') {      //if the literal starts with a minus or a plus
        if (literal.length() == 1) return false;       //if the literal has only one character, return false because it's not a valid int
        i++;
    }

    for (; i < literal.length(); i++) {                //loop through the literal
        if (!isdigit(literal[i])) return false;        //if the character is not a digit, return false
    }
    return true;                                        //return true if the literal is a valid int
}

//----------------------------------------------------------------------------------------


bool ScalarConverter::isChar(const std::string& literal) {

    // it is for "'c'" case
    if (literal.length() == 3 && literal[0] == '\'' && literal[2] == '\'')      //if the literal length is 3 and the first and third characters are quotes means we recieved a char in the form of 'c'
        return true;
    if (literal.length() == 1 && isprint(literal[0]))                           //if the literal length is 1 and the character is printable, return true
        return true;
    return false;
}

//----------------------------------------------------------------------------------------


bool ScalarConverter::isFloat(const std::string& literal) {
    if (literal == "-inff" || literal == "+inff" || literal == "nanf") return true; //if the literal is -inff, +inff or nanf, return true
    if (literal.empty() || literal[literal.length() - 1] != 'f') return false;      //if the literal is empty or the last character is not an f, return false
    
    bool hasDot = false;                                                            //to check if the literal has a dot
    bool hasDigit = false;                                                          //to check if the literal has a digit
    size_t i = 0;
    if (literal[0] == '-' || literal[0] == '+') i++;                                //if the literal starts with a minus or a plus, go to the next character
    
    //; at the beginning means to use the old value of i
    for (; i < literal.length() - 1; i++) {                                        // we loop through the literal until the second last character
        if (literal[i] == '.') {                                                   //if the character is a dot
            if (hasDot) return false;                                                    // if we already have a dot, return false
            hasDot = true;                                                               // set hasDot to true
        } else if (isdigit(literal[i])) {                                          // else if the character is a digit, set hasDigit to true
            hasDigit = true;                                                            // set hasDigit to true
        } else {                                                                   //else return false
            return false;
        }
    }
    return hasDot && hasDigit;                                                     //if we finished the loop and both hasDot and hasDigit are true, return true
}


//----------------------------------------------------------------------------------------


bool ScalarConverter::isDouble(const std::string& literal) {
    if (literal == "-inf" || literal == "+inf" || literal == "nan") return true; //if the literal is -inf, +inf or nan, return true
    if (literal.empty()) return false;                                           //if the literal is empty, return false
    
    bool hasDot = false;                                                         //to check if the literal has a dot
    bool hasDigit = false;                                                       //to check if the literal has a digit
    size_t i = 0;
    if (literal[0] == '-' || literal[0] == '+') i++;                             //if the literal starts with a minus or a plus, go to the next character
    
    for (; i < literal.length(); i++) {                                        // we loop through the literal until the second last character
        if (literal[i] == '.') {                                               //if the character is a dot
            if (hasDot) return false;                                               // if we already have a dot, return false
            hasDot = true;                                                          // set hasDot to true
        } else if (isdigit(literal[i])) {                                      // else if the character is a digit, set hasDigit to true
            hasDigit = true;                                                    
        } else {                                                               //else return false
            return false;
        }
    }
    return hasDot && hasDigit;                                                     //if we finished the loop and both hasDot and hasDigit are true, return true
}

//----------------------------------------------------------------------------------------


void ScalarConverter::convertInt(const std::string& literal) {

    long l = std::atol(literal.c_str());                                                //convert the literal to a long
    if (l > std::numeric_limits<int>::max() || l < std::numeric_limits<int>::min()) {   //if l is greater than the max int or less than the min int
        std::cout << "char: impossible" << std::endl;                                   //print impossible for char
        std::cout << "int: impossible" << std::endl;                                    //print impossible for int
        std::cout << "float: " << static_cast<float>(l) << ".0f" << std::endl;                              
        std::cout << "double: " << static_cast<double>(l) << ".0" << std::endl;                              
        return;                                                                         //return because we don't want to continue the function
    }

    int i = static_cast<int>(l);                                                        //we static cast the long to an int because it is a downcast
    float f = static_cast<float>(i);                                                   //we static cast the int to a float because it is a downcast
    double d = static_cast<double>(i);                                                 //we static cast the int to a double because it is a downcast

    if (i < 0 || i > 127)                                                                  //if i is not in the range ascii values
        std::cout << "char: impossible" << std::endl;                                      //print impossible for char
    else if (!isprint(i))                                                                  //else if i is not printable (not in the range of printable ascii values)
        std::cout << "char: Non displayable" << std::endl;                                 //print Non displayable for char
    else                                                                                   //else
        std::cout << "char: '" << static_cast<char>(i) << "'" << std::endl;                     // cast the int to a char and print it
    
    std::cout << "int: " << i << std::endl;                                                //print the int
    std::cout << std::fixed << std::setprecision(1) << "float: " << f << "f" << std::endl;  //using setprecision(1) we print the float with 1 decimal place
    std::cout << std::fixed << std::setprecision(1) << "double: " << d << std::endl;
}

//----------------------------------------------------------------------------------------



void ScalarConverter::convertChar(const std::string& literal) {
    
    char c;

    if (literal.length() == 3)                                                               //if the literal length is 3 means we recieved a char in the form of 'c'
        c = literal[1];                                                                      //the char is the second character
    else                                                                                     //else
        c = literal[0];                                                                      //the char is the first character
    
    int i = static_cast<int>(c);
    float f = static_cast<float>(c);
    double d = static_cast<double>(c);

    std::cout << "char: '" << c << "'" << std::endl;
    std::cout << "int: " << i << std::endl;
    std::cout << "float: " << f << ".0f" << std::endl;
    std::cout << "double: " << d << ".0" << std::endl;
}

//----------------------------------------------------------------------------------------


void ScalarConverter::convertFloat(const std::string& literal) {
    if (literal == "-inff" || literal == "+inff" || literal == "nanf") {                      //if the literal is -inff, +inff or nanf
        std::cout << "char: impossible" << std::endl;                                         //print impossible for char
        std::cout << "int: impossible" << std::endl;                                          //print impossible for int
        std::cout << "float: " << literal << std::endl;                                       //print the literal itself (nanf, inff, -inff)
        std::cout << "double: " << literal.substr(0, literal.length() - 1) << std::endl;      //using substr we remove the f from the end of the literal
        return;
    }

    std::string numStr = literal.substr(0, literal.length() - 1);                             //using substr we remove the f from the end of the literal from the literal first
    double d = std::atof(numStr.c_str());                                                     //atof converts the string to a double although the name is confusing
    
    // Convert max float to string for comparison
    char maxFloatStr[50];                                                                     //max float is 3.40282346638528859811704183484516925440e+38 which is 50 characters long so we need to allocate 50 characters
    
    //snprintf is a safer version of sprintf because it takes a size parameter
    //so first argument is the buffer that we want to fill
    //second argument is the size of the buffer
    //third argument is the format string, here it is %.0f which means print the float with 0 decimal places means no decimal places
    //fourth argument is the value that we want to print, here it is the max float
    //so at the end we filled maxFloatStr with the max float as a string without decimal places
    std::snprintf(maxFloatStr, sizeof(maxFloatStr), "%.0f", std::numeric_limits<float>::max());
    std::string maxFloat(maxFloatStr);                                                        //here we convert the char array(maxFloatStr) to a string called maxFloat
    
    // Remove decimal point and trailing zeros for comparison
    size_t dotPos = numStr.find('.');                                                        //using find we find the position of the dot in the numStr
    if (dotPos != std::string::npos) {                                                       //std::string::npos == -1, and find returns -1 if the dot is not found
        numStr = numStr.substr(0, dotPos);                                                   //if the dot is found, we remove the dot and everything after it
    }
    
    //if the length of the numStr is greater than the length of the maxFloat means the number is too big
    //if the length of the numStr is equal to the length of the maxFloat and the numStr is greater than the maxFloat means the number is too big
    if (numStr.length() > maxFloat.length() || 
        (numStr.length() == maxFloat.length() && numStr > maxFloat)) { // if the length of the numStr is equal to the length of but the numStr is greater than the maxFloat means the number is too big
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: impossible" << std::endl;
        std::cout << "double: " << d << ".0" << std::endl;
        return;
    }

    float f = static_cast<float>(d);

    if (std::isnan(f) || std::isinf(f)) { //an extra check for overflow and underflow and nan and inf                         
        std::cout << "char: impossible" << std::endl;                                      //print impossible for char
        std::cout << "int: impossible" << std::endl;                                       //print impossible for int
    } else {
        if (f > std::numeric_limits<int>::max() || f < std::numeric_limits<int>::min()) {  //if the float is greater than the max int or less than the min int
            std::cout << "char: impossible" << std::endl;
            std::cout << "int: impossible" << std::endl;
        } else {                                                                           //if the float is in the range of int
            int i = static_cast<int>(f);                                                   //we static cast the float to an int because it is a downcast
            if (i < 0 || i > 127)                                                          //if the int is not in the range of ascii values
                std::cout << "char: impossible" << std::endl;                               //print impossible for char
            else if (!isprint(i))                                                          //else if the int is not printable (not in the range of printable ascii values)
                std::cout << "char: Non displayable" << std::endl;                           //print Non displayable for char
            else                                                                             //else
                std::cout << "char: '" << static_cast<char>(i) << "'" << std::endl;         // else means the int is in the range of printable ascii values
            std::cout << "int: " << i << std::endl;
        }
    }
    std::cout << std::fixed << std::setprecision(1) << "float: " << f << "f" << std::endl;  //using setprecision(1) we print the float with 1 decimal place plus the f at the end
    std::cout << std::fixed << std::setprecision(1) << "double: " << d << std::endl;        //using setprecision(1) we print the double with 1 decimal place
}

//----------------------------------------------------------------------------------------

void ScalarConverter::convertDouble(const std::string& literal) {

    if (literal == "-inf" || literal == "+inf" || literal == "nan") { // we handle nan, inf and -inf first
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: " << literal << "f" << std::endl;
        std::cout << "double: " << literal << std::endl;
        return;
    }

    std::string numStr = literal;                                    //we copy the literal to a string called numStr
    if (numStr[0] == '-') {                                          //if the first character is a minus
        numStr = numStr.substr(1);                                       // Remove minus sign for length check
    }
    
    size_t dotPos = numStr.find('.');                               // using find we find the position of the dot in the numStr
    if (dotPos != std::string::npos) {                              // if the dot is found
        numStr = numStr.substr(0, dotPos);                          // we remove the dot and everything after it
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

    double d = std::atof(literal.c_str()); // atof converts the string to a double although the name is confusing
    // if literal is bigger than double range, atof returns inf or nan and later we handle it in following code
    
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
    if (isInt(literal))                      // Int
        convertInt(literal);
    else if (isChar(literal))                // Char
        convertChar(literal);
    else if (isFloat(literal))               // Float
        convertFloat(literal);
    else if (isDouble(literal))              // Double
        convertDouble(literal);
    else                                     // Invalid input format(not int, char, float or double)
        std::cout << "Invalid input format" << std::endl;
} 