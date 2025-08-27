#ifndef DATE_HPP
# define DATE_HPP

//# include <string>
# include <stdexcept>
# include <cstdlib>

//# include <new>

// Macro to simulate new allocation failure for testing
// Usage: std::string dateStr = FNNEW();//line.substr(0, commaPos);
//# define FNNEW() (throw std::bad_alloc(), std::string())

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
	bool operator<(const Date& other) const; // we expect left side of '<' to be type of Date and right side to be type of Date
	                                         // we need this for std::map to work, because it uses this operator to sort the elements
	
	
	bool operator==(const Date& other) const; //for exact date comparison, where we do it->first == date

	// --------- Getters ---------
	int getYear() const;
	int getMonth() const;
	int getDay() const;

	// --------- Helper methods ---------
	bool isLeapYear(int year) const;
	int getDaysInMonth(int year, int month) const;
};

#endif 