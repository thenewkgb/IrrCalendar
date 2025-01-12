#include <iostream>

#define JAN "January"
#define FEB "February"
#define MAR "March"
#define APR "April"
#define MAY "May"
#define JUN "June"
#define JUL "July"
#define AUG "August"
#define SEP "September"
#define OCT "October"
#define NOV "November"
#define DEC "December"

#define MON "M"
// "Monday"
#define TUE "T"
// "Tuesday"
#define WED "W"
// "Wednesday"
#define THU "T"
// "Thursday"
#define FRI "F"
// "Friday"
#define SAT "S"
// "Saturday"
#define SUN "S"
// "Sunday"

enum Month
{
	Jan = 1,
	Feb,
	Mar,
	Apr,
	May,
	Jun,
	Jul,
	Aug,
	Sep,
	Oct,
	Nov,
	Dec
};

enum Day
{
	Sun = 0,
	Mon,
	Tue,
	Wed,
	Thu,
	Fri,
	Sat
};

/*
class Date
includes output to cout
can add days, months, years
and takes leap years into account
*/

class Date
{
  public:
	class Invalid
	{
	};
	Date();
	Date(int yy, Month mm, int dd)
	{
		y = yy;
		m = mm;
		d = dd;
		if (!is_valid(yy, mm, dd))
		{
			throw Invalid();
		}
	}

	int day() const { return d; };
	Month month() const { return m; };
	int year() const { return y; };
	int days() { return days_in_month; };

	void add_day();
	void add_month();
	void add_year(int n);

  private:
	int y;
	Month m;
	int d;
	int days_in_month;

	bool is_valid(int y, Month m, int d);
	bool leapyear(int y)
	{
		return (y % 4 == 0 && y % 100 != 0) || y % 400 == 0;
	}
};