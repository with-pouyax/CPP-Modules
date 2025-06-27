#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <map>
# include <algorithm>
# include <cstdlib>
# include <climits>
# include <cfloat>
# include <limits>

class Date
{
private:
	int _year;
	int _month;
	int _day;

public:
	// Orthodox Canonical Form
	Date();
	Date(const std::string& dateStr);
	Date(const Date& other);
	Date& operator=(const Date& other);
	~Date();

	// Validation methods
	bool isValidFormat(const std::string& dateStr) const;
	bool isValidDate() const;
	void parseDate(const std::string& dateStr);

	// Comparison operators for std::map
	bool operator<(const Date& other) const;
	bool operator<=(const Date& other) const;
	bool operator==(const Date& other) const;
	bool operator!=(const Date& other) const;
	bool operator>(const Date& other) const;
	bool operator>=(const Date& other) const;

	// Getters
	int getYear() const;
	int getMonth() const;
	int getDay() const;

	// Helper methods
	bool isLeapYear(int year) const;
	int getDaysInMonth(int year, int month) const;
};

class BitcoinExchange
{
private:
	std::map<Date, float> _data;

public:
	// Orthodox Canonical Form
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange& other);
	BitcoinExchange& operator=(const BitcoinExchange& other);
	~BitcoinExchange();

	// Core functionality
	void loadDatabase(const std::string& filename);
	void processInputFile(const std::string& filename);
	float getExchangeRate(const Date& date) const;

	// Validation methods
	bool isValidValue(const std::string& valueStr, float& value) const;
	bool isValidFloat(const std::string& valueStr, float& value) const;
	bool isInRange(float value) const;

	// Helper methods
	void processLine(const std::string& line) const;
	void printResult(const Date& date, float value, float rate) const;
	void printError(const std::string& message) const;
	std::string trimWhitespace(const std::string& str) const;
};

#endif 