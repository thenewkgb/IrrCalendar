#include <iostream>
#include <ctime>
#include <cstdio>
#include <sstream>

#include "date.hpp"


using namespace std;


//
// time point
//

/*
check mktime still gives a valid date
make a new Date from puttime and check
would a standard library function go wrong?

if getDayOfWeek returns an int
if tm returns possibly -1
can i link back to a date?
*/

tm makeTM(
	Date date)
{
	// must initialise with {} or it is garbage
	tm get_tm = {};
	string sd;
	int d = date.day();
	int m = (int)date.month();
	int y = date.year();

	get_tm.tm_year = y - 1900;
	get_tm.tm_mon = m - 1;
	get_tm.tm_mday = d;

	// works with this
	mktime(&get_tm);

	return get_tm;
}

//bloody google
static int stoi(string &s)
{
	int i;
	istringstream(s) >> i;
	return i;
}

// find Sun-Sat from Date string
int getDayOfWeek(const Date date)
{
	tm get_day = makeTM(date);
	// we dont check it

	char c[10];
	strftime(c, sizeof(c), "%w", &get_day);
	string my_day = c;
	int iday = stoi(my_day);

	return iday;
}


//
// print
//

string printMonth(Date &d)
{
	switch (d.month())
	{
	case Jan:
		return JAN;
	case Feb:
		return FEB;
	case Mar:
		return MAR;
	case Apr:
		return APR;
	case May:
		return MAY;
	case Jun:
		return JUN;
	case Jul:
		return JUL;
	case Aug:
		return AUG;
	case Sep:
		return SEP;
	case Oct:
		return OCT;
	case Nov:
		return NOV;
	case Dec:
		return DEC;
	default:
		return "mmm";
	}
}

/*
printf included for c++98
*/
void printHeader(
	const Date date)
{
	cout << "==========" << endl;
	tm title = makeTM(date);
	cout << asctime(&title);
	cout << "==========" << endl;

	printf("|");
	printf("%-3s|", SUN);
	printf("%-3s|", MON);
	printf("%-3s|", TUE);
	printf("%-3s|", WED);
	printf("%-3s|", THU);
	printf("%-3s|", FRI);
	printf("%-3s|", SAT);
	printf("\n\n");
}

void printWeek(const Date date)
{
	// we want the beginning of the month
	Date begin(date.year(),
			   date.month(),
			   1);
			   
	// which enum?
	int first_day = getDayOfWeek(begin);
	Day day = (Day)((int)first_day);

	printf("|");

	// fill last month
	for (int i = 0; i < first_day; ++i)
	{
		printf("%-3s|", "X");
	}

	// number days
	// warning, using begin
	// using begin was an error
	for (int i = 0; i < date.days(); ++i)
	{
		// use the argument
		// quick way to show it
		if (i + 1 == date.day())
		{
			printf("%-3s|", "_");
		}
		else
		{
			printf("%-3i|", begin.day());
		}

		switch (day)
		{
		case Sun:
			day = Mon;
			break;
		case Mon:
			day = Tue;
			break;
		case Tue:
			day = Wed;
			break;
		case Wed:
			day = Thu;
			break;
		case Thu:
			day = Fri;
			break;
		case Fri:
			day = Sat;
			break;
		case Sat:
		{
			day = Sun;
			printf("\n|");
		}
		}

		begin.add_day();
	}

	Date finish(date.year(),
				date.month(),
				date.days());

	int zero_sunday = 6;
	int end = zero_sunday - getDayOfWeek(finish);

	for (int i = 0; i < end; ++i)
	{
		printf("%-3s|", "X");
	}
}

//
// main
//

int main(int argc, char *argv[])
{
	Date date(2025, Feb, 17);

	// make the calendar
	printHeader(date);
	printWeek(date);

	cout << "\n\n";

	return 0;
}
