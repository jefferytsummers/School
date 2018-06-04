#include "dateClass.h"
#include <iostream>

using namespace std;

dateClass::dateClass()
{
    month = 1;
    day   = 1;
    year  = 1970;
}

dateClass::dateClass(int m, int d, int y)
{
    if (month > 0 && month < 13)
        month = m;
    else
        month = 1;
    if (day > 0 && ((day < 31 && (month == 4 || month == 6 || month == 9 ||
        month == 11)) || (day < 32 && (month == 1 || month == 3 || month == 5 ||
        month == 7 || month == 8 || month == 10 || month == 12)) || (day < 30
        && month == 2)))
        day   = d;
    else
        day = 1;
    if (year > 0)
        year  = y;
    else
        year = 1970;
}

void dateClass::SetDate(int m, int d, int y)
{
    month = m;
    day   = d;
    year  = y;
}

void dateClass::Display() const
{
    cout << "The date is: (m/d/y)" << endl;
    if (month < 10)
        cout << '0';
    cout << month << "\\";

    if (day < 10)
        cout << '0';
    cout << day << "\\";

    if (year > 0)
        cout << year;

    cout << endl << endl;
}

void dateClass::SetMonth(int m)
{
    month = m;
    return;
}

void dateClass::SetDay(int d)
{
    day = d;
    return;
}

void dateClass::SetYear(int y)
{
    year = y;
    return;
}

int dateClass::GetMonth()
{
    return month;
}

int dateClass::GetDay()
{
    return day;
}

int dateClass::GetYear()
{
    return year;
}

