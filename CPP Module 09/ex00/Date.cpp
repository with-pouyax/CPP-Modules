#include "Date.hpp"

// ============================================================================
// Date Class Implementation
// ============================================================================

Date::Date() : _year(-1), _month(-1), _day(-1) {} // we use -1 to indicate that the date is not valid

Date::Date(const std::string& dateStr) : _year(-1), _month(-1), _day(-1)
{
	parseDate(dateStr);
    //if we dont throw exception above, mean we have valid date and we saved it in _year, _month, _day
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
	if (dateStr.length() != 10) // we check if the length of the dateStr is 10
		return false;
	
	// Check hyphens at positions 4 and 7
	if (dateStr[4] != '-' || dateStr[7] != '-')
		return false;
	
	// Check all other characters are digits
	for (size_t i = 0; i < dateStr.length(); ++i) // we check if all other characters are digits
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
		case 2: //in case of february
			return isLeapYear(year) ? 29 : 28;
		case 4: case 6: case 9: case 11:
			return 30;
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
			return 31;
		default: //in case of invalid month
			return 0;
	}
}

bool Date::isValidDate() const
{
	// Validate year (must not be negative)
	if (_year < 0)
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
	if (_year != other._year)                 //if year is not equal, we compare year
		return _year < other._year;
	// we only reach here if year is equal
	if (_month != other._month)               //if month is not equal, we compare month
		return _month < other._month;
	// we only reach here if year and month are equal
	return _day < other._day;               //if day is not equal, we compare day
}

bool Date::operator==(const Date& other) const
{
	return _year == other._year && _month == other._month && _day == other._day;
}

// Getters
int Date::getYear() const { return _year; }
int Date::getMonth() const { return _month; }
int Date::getDay() const { return _day; } 