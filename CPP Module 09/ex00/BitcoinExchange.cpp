#include "BitcoinExchange.hpp"
#include "Date.hpp"

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
bool BitcoinExchange::isValidFloat(const std::string& valueStr, float& value) const
{
	if (valueStr.empty())
		return false;
	
	char* endPtr;
	value = std::strtof(valueStr.c_str(), &endPtr);
	
	// Check if entire string was consumed
	if (endPtr != valueStr.c_str() + valueStr.length())
		return false;
	
	// C++98 compliant NaN/Inf detection
	if (value != value) // NaN detection
		return false;
	
	// Check for infinity (overflow) - C++98 compatible
	if (value > FLT_MAX || value < -FLT_MAX)
		return false;
	
	return true;
}

bool BitcoinExchange::isInRange(float value) const
{
	return value >= 0.0f && value <= 1000.0f;
}

bool BitcoinExchange::isValidValue(const std::string& valueStr, float& value) const
{
	// Check for empty value
	if (valueStr.empty())
	{
		printError("bad input => " + valueStr);
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
	value = std::strtof(valueStr.c_str(), &endPtr);
	
	// Check if entire string was consumed
	if (endPtr != valueStr.c_str() + valueStr.length())
	{
		printError("bad input => " + valueStr);
		return false;
	}
	
	// Handle NaN (not a valid number)
	if (value != value) // NaN detection
	{
		printError("bad input => " + valueStr);
		return false;
	}
	
	// Handle negative values including negative zero and negative infinity
	// String-based check for negative zero to handle IEEE 754 -0 == 0 issue
	if (valueStr[0] == '-' || value < 0)
	{
		printError("not a positive number.");
		return false;
	}
	
	// Handle positive infinity and values > 1000
	if (value > FLT_MAX || value > 1000.0f || hasNonZeroAfter1000)
	{
		printError("too large a number.");
		return false;
	}
	
	return true;
}

// Phase 4: CSV Database Loading
void BitcoinExchange::loadDatabase(const std::string& filename)
{
	std::ifstream file(filename.c_str());
	if (!file.is_open())
		throw std::runtime_error("could not open database file");
	
	std::string line;
	bool firstLine = true;
	
	while (std::getline(file, line))
	{
		// Skip header line
		if (firstLine)
		{
			firstLine = false;
			continue;
		}
		
		if (line.empty())
			continue;
		
		// Parse CSV line: date,exchange_rate
		size_t commaPos = line.find(',');
		if (commaPos == std::string::npos)
			continue; // Skip malformed lines
		
		std::string dateStr = line.substr(0, commaPos);
		std::string rateStr = line.substr(commaPos + 1);
		
		try
		{
			Date date(dateStr);
			float rate;
			if (isValidFloat(rateStr, rate) && rate >= 0)
			{
				_data[date] = rate;
			}
		}
		catch (const std::exception& e)
		{
			// Skip invalid entries
			continue;
		}
	}
	
	file.close();
	
	if (_data.empty())
		throw std::runtime_error("no valid data loaded from database");
}

// Phase 6: Date Lookup & Calculation
float BitcoinExchange::getExchangeRate(const Date& date) const
{
	if (_data.empty())
		throw std::runtime_error("no data available");
	
	// Use lower_bound for efficient lookup
	std::map<Date, float>::const_iterator it = _data.lower_bound(date);
	
	if (it != _data.end() && it->first == date)
	{
		// Exact match found
		return it->second;
	}
	
	// No exact match, use closest previous date
	if (it == _data.begin())
		throw std::runtime_error("no earlier data available");
	
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

void BitcoinExchange::printError(const std::string& message) const
{
	std::cerr << "Error: " << message << std::endl;
}

// Helper function to trim whitespace from both ends of a string
std::string BitcoinExchange::trimWhitespace(const std::string& str) const
{
	size_t start = str.find_first_not_of(" \t\r\n");
	if (start == std::string::npos)
		return "";
	size_t end = str.find_last_not_of(" \t\r\n");
	return str.substr(start, end - start + 1);
}

void BitcoinExchange::processLine(const std::string& line) const
{
	if (line.empty())
		return;
	
	// Strictly enforce "date | value" format: exactly one space before and after '|', and no extra spaces
	size_t pipePos = line.find('|');
	if (pipePos == std::string::npos ||
	    pipePos == 0 || pipePos == line.length() - 1 ||
	    line[pipePos - 1] != ' ' || line[pipePos + 1] != ' ')
	{
		printError("bad input => " + line);
		return;
	}

	// Check for multiple spaces before or after the pipe
	if ((pipePos >= 2 && line[pipePos - 2] == ' ') ||
	    (pipePos + 2 < line.length() && line[pipePos + 2] == ' '))
	{
		printError("bad input => " + line);
		return;
	}

	std::string dateStr = line.substr(0, pipePos - 1);
	std::string valueStr = line.substr(pipePos + 2);
	
	// Trim whitespace from both date and value strings
	dateStr = trimWhitespace(dateStr);
	valueStr = trimWhitespace(valueStr);
	
	// Validate date
	Date date;
	try
	{
		date = Date(dateStr);
	}
	catch (const std::exception& e)
	{
		printError("bad input => " + dateStr);
		return;
	}
	
	// Validate value
	float value;
	if (!isValidValue(valueStr, value))
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
	std::ifstream file(filename.c_str());
	if (!file.is_open())
		throw std::runtime_error("could not open file.");
	
	std::string line;
	bool firstLine = true;
	
	while (std::getline(file, line))
	{
		// Skip header line if present
		if (firstLine && line == "date | value")
		{
			firstLine = false;
			continue;
		}
		firstLine = false;
		
		processLine(line);
	}
	
	file.close();
} 