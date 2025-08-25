#include "../include/BitcoinExchange.hpp"
#include "../include/Date.hpp"

// ============================================================================
// BitcoinExchange Class Implementation
// ============================================================================

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _data(other._data) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
		_data = other._data;
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

// Phase 3: Value Validation
bool BitcoinExchange::isValidValue(const std::string& valueStr, float& value) const
{
	// Check for empty value
	if (valueStr.empty())
	{
		std::string errorMsg = valueStr.empty() ? "' '" : valueStr;
		printError("bad input => " + errorMsg);
		return false;
	}
	
	// String-based precision check for 1000 boundary before float conversion
	bool hasNonZeroAfter1000 = false;
	if (valueStr.length() >= 4 && valueStr.substr(0, 4) == "1000")
	{
		// Check if there's a decimal point after "1000"
		if (valueStr.length() > 4 && valueStr[4] == '.')
		{
			// Check all digits after the decimal point
			for (size_t i = 5; i < valueStr.length(); ++i)
			{
				if (std::isdigit(valueStr[i]) && valueStr[i] != '0')
				{
					hasNonZeroAfter1000 = true;
					break;
				}
			}
		}
	}
	
	// Parse the float value first to handle NaN/Inf appropriately
	char* endPtr;
	value = std::strtof(valueStr.c_str(), &endPtr);  // we convert the valueStr to float and save it in value
	                                                              // second argument is the end pointer
																  // if conversion is successful, endPtr will point to the last character of the string
																  // if conversion is not successful, endPtr will point to the first non-digit character

	
	// Check if entire string was consumed
	if (endPtr != valueStr.c_str() + valueStr.length())     //valueStr.c_str() is the pointer of first character of valueStr + valueStr.length() we move to the end of the string
	{
		std::string errorMsg = valueStr.empty() ? "' '" : valueStr;
		printError("bad input => " + errorMsg);
		return false;
	}
	
	// Handle NaN (not a valid number)
	if (value != value) // NaN detection
	{
		std::string errorMsg = valueStr.empty() ? "' '" : valueStr;
		printError("bad input => " + errorMsg);
		return false;
	}
	
	// Handle negative values including negative zero and negative infinity
	// String-based check for negative zero to handle IEEE 754 -0 == 0 issue
	if ((valueStr[0] == '-' && valueStr != "-0") || value < 0)
	{
		printError("not a positive number.");
		return false;
	}
	
	// Normalize -0 to 0
	if (valueStr == "-0")
	{
		value = 0.0f;
	}
	
	// Handle positive infinity and values > 1000
	if (value > FLT_MAX || value > 1000.0f || hasNonZeroAfter1000) //FLT_MAX is the largest positive float value
	{
		printError("too large a number.");
		return false;
	}
	
	return true;
}



// Phase 4: CSV Database Loading
void BitcoinExchange::loadDatabase(const std::string& filename)
{
	std::ifstream file(filename.c_str());     //make a object of ifstream which is used to open the file
	if (!file.is_open())
		throw std::runtime_error("could not open database file"); //c++98
	
	std::string line;                           // we use line to store each line of the file
	bool firstLine = true;                      // we use this bool to skip the first line of the file
	
	while (std::getline(file, line))    // read the file line by line until the end of the file
	{
		// Skip header line always because we assume that the first line is the header
		if (firstLine)
		{
			firstLine = false;
			continue;                           // continue will skip the rest of loop and go to next iteration
		}
		
		if (line.empty()) 	                    // if we have empty line, we skip it and go to next iteration
			continue;
		
		// Parse CSV line: date,exchange_rate
		size_t commaPos = line.find(',');    // we find the position of the comma in the line
		if (commaPos == std::string::npos)
			continue;                           // if we don't have comma, we skip it and go to next iteration
		
		std::string dateStr = line.substr(0, commaPos);    // we save the before comma part of the line to dateStr
		std::string rateStr = line.substr(commaPos + 1);     // we save the after comma part of the line to rateStr

		// Trust the data format since exercise guarantees data.csv will never change
		Date date(dateStr); // we make a date object and parse the dateStr and save it in date object
		                    // we parse and save the date in date object
							//now we saved the date in date object, in _year, _month, _day
		float rate = std::atof(rateStr.c_str()); // we convert the rateStr to float and save it in rate
		_data[date] = rate; //date(object) will be the key and rate will be the value in the _data, which is a map
	}
	
	file.close(); 				// we close the file
	
	if (_data.empty())  		//this happen only if we have no data in data.csv
		throw std::runtime_error("no valid data loaded from database");
}




// Phase 6: Date Lookup & Calculation
float BitcoinExchange::getExchangeRate(const Date& date) const
{
	if (_data.empty())
		throw std::runtime_error("no data available");
	
	// Use lower_bound for efficient lookup
	std::map<Date, float>::const_iterator it = _data.lower_bound(date); //lower_bound will return an iterator to the first element in the map that is equal or greater than date
                                                                           //if date is after the last element, it will return _data.end()
                                                                           //if we need to access the last date we should do it--; ,
	
	if (it != _data.end() && it->first == date) //if we are not at the end (we found the date or lower bound) and the key of the element is equal to date
	                                            
	{
		// Exact match found
		return it->second; // we return the value of the element
	}
	
	// if the date is before the first date in the map, we nevr go to above if condition
    // because it->first will never equal to date
	if (it == _data.begin())
		throw std::runtime_error("no earlier data available");
	
    // since subject asked to go to previous date, we do it--, in case of not finding exact date
	--it; // Move to previous entry
	return it->second;
}

void BitcoinExchange::printResult(const Date& date, float value, float rate) const
{
	std::cout << date.getYear() << "-";
	if (date.getMonth() < 10) std::cout << "0";
	std::cout << date.getMonth() << "-";
	if (date.getDay() < 10) std::cout << "0";
	std::cout << date.getDay() << " => " << value << " = " << (value * rate) << std::endl;
}
// ******exercise asked to print everything in standard output*********
void BitcoinExchange::printError(const std::string& message) const
{
	std::cout << "Error: " << message << std::endl;
}

// Helper function to trim whitespace from both ends of a string
std::string BitcoinExchange::trimWhitespace(const std::string& str) const
{
	size_t start = str.find_first_not_of(" \t\r\n"); //find the first non-whitespace character
	if (start == std::string::npos) // if we don't find any non-whitespace character
		return ""; // return empty string
	size_t end = str.find_last_not_of(" \t\r\n"); //find the last non-whitespace character
	return str.substr(start, end - start + 1); // return the substring between the first and last non-whitespace character
}

void BitcoinExchange::processLine(const std::string& line) const
{
	if (line.empty())
		return;
	
	// Strictly enforce "date | value" format: exactly one space before and after '|', and no extra spaces
	size_t pipePos = line.find('|');
	if (pipePos == std::string::npos || //if we don't find pipe
	    pipePos == 0 ||                 //if pipe is at the beginning of the line
		pipePos == line.length() - 1 || //if pipe is at the end of the line
	    line[pipePos - 1] != ' ' ||     //if there is no space before the pipe
		 line[pipePos + 1] != ' ')      //if there is no space after the pipe
	{
		printError("bad input => " + line);
		return;
	}

	// Check for multiple spaces or any whitespace before or after the pipe
	if ((pipePos >= 2 && std::isspace(line[pipePos - 2])) ||
	    (pipePos + 2 < line.length() && std::isspace(line[pipePos + 2])))
	{
		printError("bad input => " + line);
		return;
	}

	std::string dateStr = line.substr(0, pipePos - 1);
	std::string valueStr = line.substr(pipePos + 2);
	
	// Trim whitespace from both date and value strings
	dateStr = trimWhitespace(dateStr);                   // we trim the whitespace from both sides of the dateStr
	valueStr = trimWhitespace(valueStr);                  // we trim the whitespace from both sides of the valueStr
	
	// Validate date
	Date date;         // we create a date object
	try
	{
		date = Date(dateStr); // Default date constructor will parse the dateStr and save it in date object
	}
	catch (const std::exception& e)
	{
		std::string errorMsg = dateStr.empty() ? "' '" : dateStr;
		printError("bad input => " + errorMsg);
		return;
	}
	
	// Validate value
	float value;
	if (!isValidValue(valueStr, value)) // validate valueStr and save it in value
		return; // Error already printed
	
	// Get exchange rate and calculate result
	try
	{
		float rate = getExchangeRate(date);
		printResult(date, value, rate);
	}
	catch (const std::exception& e)
	{
		printError(e.what());
	}
}

// Phase 5: Input File Processing
void BitcoinExchange::processInputFile(const std::string& filename)
{
	std::ifstream file(filename.c_str());                // we open the file
	if (!file.is_open())
		throw std::runtime_error("could not open file.");
	
	std::string line;                                       // we use this string to store each line of the file
	bool foundHeader = false;                               // we use this bool to check if we found the header
	bool hasAnyData = false;                                // we use this bool to check if we have any data
	bool headerErrorReported = false;                       // we use this bool to check if we reported the header error
	
	while (std::getline(file, line))              //loop through all lines in the file
	{
		// Skip empty lines
		if (line.empty()) // if the line is empty, we skip the rest of the loop
			continue;
		
		// Look for header on first non-empty line
		if (!foundHeader && !headerErrorReported) //if we didn't find the header and we didn't reported the header error
		{
			std::string trimmed = trimWhitespace(line);  // trim the whitespace from the line and save it in trimmed
			if (trimmed == "date | value")                   // if the trimmed line is equal to "date | value"
			{
				foundHeader = true;                          // we set foundHeader to true
				continue; // go to next iteration            // we skip the rest of the loop and go to next iteration
			}
			else // if the trimmed line is not equal to "date | value"
			{
				// Wrong header format - report error and skip this line
				printError("invalid header format: expected 'date | value'");
				headerErrorReported = true;                   // we set headerErrorReported to true
				continue;
			}
		}
		
		// Process as data line (either after valid header or after header error)
		processLine(line);
		hasAnyData = true;
	}
	
	// Check if we found any data
	if (!hasAnyData)
	{
		printError("no data found in file");
		return;
	}
	
	file.close();
} 