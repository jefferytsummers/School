/*
PROGRAMMER:          Ryan Florida
Assignment:          OLA 1
Class:               CSCI 2170 Section 001
Course Instructor:   Dr. Li
Due Date:            Midnight, Thursday, 7/7/2016

Description:         This program takes as its input the user's birthyear, or
                     any year they so choose to enter. Once the input is
                     received, the program will apply Zeller's Rule to said
                     input in order to let the user know which day of the week
                     they were born on. The user will also be informed if they
                     were born during a leap year.
*/

#include <iostream>
#include <stdlib.h>

using namespace std;

//0: Main
int main()
{
    //Declaring variables.
    int    day,                //This will store the value of the input day.
           month,              //This will store the value of the input month.
           year,               //This will store the value of the input year.
           century,            /*
                               This will store the value of the century for
                               Zellar's Rule.
                               */
           moddedYear,         /*
                               This will store the value of the modified year
                               for Zellar's Rule.
                               */
           dayOfWeekNumber;    /*
                               This will store the value calculated by applying
                               Zellar's Rule.
                               */
    string dayOfWeek;          /*
                               This will store the string which describes the
                               day of the week.
                               */
    bool   flag;               /*
                               This will store the truth value for the leap
                               year.
                               */

    //Some niceties to make the user feel at ease.
    cout << "Welcome!" << endl << "Just tell me your birth date, and I will"
         << " tell you on which day of the week your were born" << endl
         << "Let's get started ...\n" << endl << "Please tell me your birth"
         << " date in the form of: month day year" << endl;
    cin  >> month >> day  >> year;

    /*
    Safeguard against users entering invalid input, including invalid months,
    days, and years.
    */
    if ((day > 31 || day < 1) || (month < 1 || month > 12) || (year < 0 || year
       > 2016) || ((month == 4 || month == 6 || month == 9 || month == 11) &&
       day == 31) || (month == 2 && day > 29))
    {
        cout << "Your input value is not correct." << endl << "The computation"
             << " was not carried out." << endl;
        exit(-1);
    }

    /*
    Calculation to determine whether input year is a leap year; sets the value
    of the "flag" variable accordingly.
    */
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        flag = true;
    else
        flag = false;

    //A few conversions to make the input play nicely with Zellar's Rule.
    if (month < 3)
    {
        month += 10;
        year -= 1;
    }
    else
        month -= 2;

    moddedYear = year % 100;

    century    = year/100;

    /*
    Application of Zellar's Rule, then modding the output by 7 to get our
    desired day of the week.
    */
    dayOfWeekNumber = (day + ((13*month - 1)/5) + moddedYear + moddedYear/4 +
                      century/4 - 2*century) % 7;

    /*
    Converts any negative number, that was calculated above, into a usable
    result.
    */
    if (dayOfWeekNumber < 0)
        dayOfWeekNumber += 7;

    //Sets "dayOfWeek" variable to its proper string value.
    if (dayOfWeekNumber == 0)
        dayOfWeek = "Sunday";
    else if (dayOfWeekNumber == 1)
        dayOfWeek = "Monday";
    else if (dayOfWeekNumber == 2)
        dayOfWeek = "Tuesday";
    else if (dayOfWeekNumber == 3)
        dayOfWeek = "Wednesday";
    else if (dayOfWeekNumber == 4)
        dayOfWeek = "Thursday";
    else if (dayOfWeekNumber == 5)
        dayOfWeek = "Friday";
    else if (dayOfWeekNumber == 6)
        dayOfWeek = "Saturday";

    /*
    Tells user which day of the week they were born on and, if they were born
    during a leap year, they will be alerted.
    */
    if (flag)
        cout << "You were born on a " << dayOfWeek << ", during a leap year!"
             << endl;
    else
        cout << "You were born on a " << dayOfWeek << "." << endl;

    return 0;
}
