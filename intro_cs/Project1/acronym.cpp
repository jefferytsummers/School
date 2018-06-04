/*
PROGRAMMER:          Ryan Florida
Assignment:          OLA2, Problem 2
Class:               CSCI 2170 Section 001
Course Instructor:   Dr. Li
Due Date:            Midnight Monday, 7/11/2016

Description:         This program takes input from a file containing strings and
                     converts each string, making up a line of the file, into an
                     acronym that is capitalized and representative of the
                     string. It will then display, to standard output, the
                     original string, on its own line, followed by an arrow and
                     the string's corresponding acronym.
*/

#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <string>

using namespace std;

//Declare function.
string acronymGenerator(string someString);


//Main
int main()
{
    //Declare variables.
    string   line,
             acronym;
    ifstream myIn;

    //Open Acronym.dat data file.
    myIn.open("Acronym.dat");

    /*
    Send each line of input file into acronym generation function, then display,
    for the user, each line with its corresponding acronym.
    */
    while (getline(myIn, line))
    {
        acronym = acronymGenerator(line);
        cout << line << " -> " << acronym << endl;
    }

    //Close myIn.
    myIn.close();

    return 0;
}


/*
1: This function takes as its input a string and creates a capitalized acronym
corresponding to that string.
*/
string acronymGenerator(string someString)
{
    //Declare local variables.
    string             acronym;  //Stores the newly created acronym string.
    string::size_type  locale;   //Stores the current location within the string

    //Initialize local variables.
    acronym = toupper(someString[0]);  /*
                                       Initialize acronym to uppercase first
                                       letter of the first word in a string.
                                       */
    locale  = someString.find(" ");     /*
                                       Initialize locale to first instance of
                                       whitespace that appears in the string.
                                       */

    /*
    Concatenates a capitalized version of the first letter of each word, from
    the input string, together in order to create a new string that forms an
    acronym corresponding to the input string.
    */
    while (locale != string::npos)
    {
        acronym += toupper(someString[locale + 1]);
        locale   = someString.find(" ", locale + 1);
    }

    //Return newly formed acronym back to main for output.
    return acronym;
}
