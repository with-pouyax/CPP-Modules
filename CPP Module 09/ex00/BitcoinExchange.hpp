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
# include "Date.hpp"


class BitcoinExchange
{
private:
	std::map<Date, float> _data;                                  // Database of exchange rates(date, rate)

public:
	//----------- Orthodox Canonical Form ------------
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange& other);
	BitcoinExchange& operator=(const BitcoinExchange& other);
	~BitcoinExchange();

	// --------- Core functionality ---------
	void loadDatabase(const std::string& filename);
	void processInputFile(const std::string& filename);
	float getExchangeRate(const Date& date) const;

	// --------- Validation methods ---------
	bool isValidValue(const std::string& valueStr, float& value) const;
	bool isValidFloat(const std::string& valueStr, float& value) const;
	bool isInRange(float value) const;

	// --------- Helper methods ---------
	void processLine(const std::string& line) const;
	void printResult(const Date& date, float value, float rate) const;
	void printError(const std::string& message) const;
	std::string trimWhitespace(const std::string& str) const;
};

#endif 