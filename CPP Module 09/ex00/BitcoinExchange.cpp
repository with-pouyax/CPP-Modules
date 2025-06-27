#include "BitcoinExchange.hpp"

// ============================================================================
// Date Class Implementation (Phase 2)
// ============================================================================

Date::Date() : _year(1900), _month(1), _day(1) {}

Date::Date(const std::string& dateStr) : _year(1900), _month(1), _day(1)
{
	parseDate(dateStr);
}

Date::Date(const Date& other) : _year(other._year), _month(other._month), _day(other._day) {}

Date& Date::operator=(const Date& other)
{
	if (this != &other)
	{
		_year = other._year;
		_month = other._month;
		_day = other._day;
	}
	return *this;
}

Date::~Date() {}

bool Date::isValidFormat(const std::string& dateStr) const
{
	// Check length (exactly 10 characters)
	if (dateStr.length() != 10)
		return false;
	
	// Check hyphens at positions 4 and 7
	if (dateStr[4] != '-' || dateStr[7] != '-')
		return false;
	
	// Check all other characters are digits
	for (size_t i = 0; i < dateStr.length(); ++i)
	{
		if (i != 4 && i != 7 && !std::isdigit(dateStr[i]))
			return false;
	}
	
	return true;
}

bool Date::isLeapYear(int year) const
{
	// Years divisible by 400 are leap years
	if (year % 400 == 0)
		return true;
	// Years divisible by 4 but not 100 are leap years
	if (year % 4 == 0 && year % 100 != 0)
		return true;
	return false;
}

int Date::getDaysInMonth(int year, int month) const
{
	switch (month)
	{
		case 2:
			return isLeapYear(year) ? 29 : 28;
		case 4: case 6: case 9: case 11:
			return 30;
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
			return 31;
		default:
			return 0;
	}
}

bool Date::isValidDate() const
{
	// Validate year range (reasonable bounds) - but allow data.csv range
	if (_year < 1900 || _year > 2100)
		return false;
	
	// Validate month (1-12)
	if (_month < 1 || _month > 12)
		return false;
	
	// Validate day for specific month
	int maxDays = getDaysInMonth(_year, _month);
	if (_day < 1 || _day > maxDays)
		return false;
	
	return true;
}

void Date::parseDate(const std::string& dateStr)
{
	if (!isValidFormat(dateStr))
		throw std::runtime_error("invalid date format");
	
	// Extract year, month, day from string
	std::string yearStr = dateStr.substr(0, 4);
	std::string monthStr = dateStr.substr(5, 2);
	std::string dayStr = dateStr.substr(8, 2);
	
	_year = std::atoi(yearStr.c_str());
	_month = std::atoi(monthStr.c_str());
	_day = std::atoi(dayStr.c_str());
	
	if (!isValidDate())
		throw std::runtime_error("invalid date");
}

// Comparison operators for std::map
bool Date::operator<(const Date& other) const
{
	if (_year != other._year)
		return _year < other._year;
	if (_month != other._month)
		return _month < other._month;
	return _day < other._day;
}

bool Date::operator<=(const Date& other) const
{
	return *this < other || *this == other;
}

bool Date::operator==(const Date& other) const
{
	return _year == other._year && _month == other._month && _day == other._day;
}

bool Date::operator!=(const Date& other) const
{
	return !(*this == other);
}

bool Date::operator>(const Date& other) const
{
	return !(*this <= other);
}

bool Date::operator>=(const Date& other) const
{
	return !(*this < other);
}

// Getters
int Date::getYear() const { return _year; }
int Date::getMonth() const { return _month; }
int Date::getDay() const { return _day; }

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

void BitcoinExchange::processLine(const std::string& line) const
{
	if (line.empty())
		return;
	
	// Parse format: "date | value"
	size_t pipePos = line.find(" | ");
	if (pipePos == std::string::npos)
	{
		printError("bad input => " + line);
		return;
	}
	
	std::string dateStr = line.substr(0, pipePos);
	std::string valueStr = line.substr(pipePos + 3);
	
	// Trim whitespace from valueStr
	size_t start = valueStr.find_first_not_of(" \t\r\n");
	if (start == std::string::npos)
	{
		printError("bad input => ");
		return;
	}
	size_t end = valueStr.find_last_not_of(" \t\r\n");
	valueStr = valueStr.substr(start, end - start + 1);
	
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