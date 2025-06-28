#ifndef DATE_HPP
# define DATE_HPP

# include <string>
# include <stdexcept>
# include <cctype>
# include <cstdlib>

class Date{

private:
	int _year;
	int _month;
	int _day;

public:
	//----------- Orthodox Canonical Form ------------
	
	Date();
	Date(const std::string& dateStr);
	Date(const Date& other);
	Date& operator=(const Date& other);
	~Date();
	//------------------------------------------------


	// --------- Validation methods ---------
	bool isValidFormat(const std::string& dateStr) const;
	bool isValidDate() const;
	void parseDate(const std::string& dateStr);

	// --------- Comparison operators for std::map ---------
	bool operator<(const Date& other) const;
	bool operator<=(const Date& other) const;
	bool operator==(const Date& other) const;
	bool operator!=(const Date& other) const;
	bool operator>(const Date& other) const;
	bool operator>=(const Date& other) const;

	// --------- Getters ---------
	int getYear() const;
	int getMonth() const;
	int getDay() const;

	// --------- Helper methods ---------
	bool isLeapYear(int year) const;
	int getDaysInMonth(int year, int month) const;
};

#endif 