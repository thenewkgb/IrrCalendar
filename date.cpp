#include "date.hpp"

using namespace std;

Date &default_date()
{
	static Date dd(2001, Jan, 1);
	return dd;
}

Date::Date()
{
	y = default_date().year();
	m = default_date().month();
	d = default_date().day();
}

bool Date::is_valid(int y, Month m, int d)
{
	if (y < 1583)
		return false; // gregorian start
	if (d < 0)
		return false;
	if (m < Jan || Dec < m)
		return false;

	days_in_month = 31;

	switch (m)
	{
	case Feb:
	{
		days_in_month = (leapyear(y)) ? 29 : 28;
		break;
	}
	case Apr:
	case Jun:
	case Sep:
	case Nov:
	{
		days_in_month = 30;
		break;
	}
	}

	if (days_in_month < d)
		return false;

	return true;
}

void Date::add_day()
{
	d++;

	if (d > days_in_month)
	{
		// d first 31>30
		d = 1;
		add_month();
	}
}

void Date::add_month()
{
	if (m == Dec)
	{
		m = Jan;
		//do not change day
		add_year(1);
	}
	else if (m == Jan && d == 29 && !leapyear(y))
	{
		// enums might be the wrong choice
		m = (Month)((int)m + 1);
		d = 28;
	}
	else
	{
		m = (Month)((int)m + 1);
	}
	// double check
	if (!is_valid(y, m, d))
	{
		throw Invalid();
	}
}

void Date::add_year(int n)
{
	if (m == Feb && d == 29 && !leapyear(y + n))
	{
		m = Mar;
		d = 1;
	}
	y += n;
}