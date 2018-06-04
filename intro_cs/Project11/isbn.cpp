#include <fstream>
#include <iostream>
#include <cmath>
#include <cassert>
#include <string>

using namespace std;

//Declare functions.
bool isValidISBN(string isbn);  //1
int CheckDigit(string input);   //1.1

//Main
int main()
{
    //Declar variables.
    string     ISBN;
    ifstream   myIn;

    //Open input file.
    myIn.open("isbndata.dat");
    assert(myIn);

    /*
    Test each ISBN-13 number contained in the input file and let user know if
    how many of their ISBN's are valid.
    */
    while (myIn >> ISBN)
        {
            if (isValidISBN(ISBN))
                cout << ISBN << " is a valid ISBN number" << endl << endl;
            else
                cout << ISBN << " is not a valid ISBN number" << endl << endl;
        }

    //Close input file.
    myIn.close();

    return 0;
}


//1: Check to see if ISBN number is actually valid.
bool isValidISBN(string isbn)
{
    //Declare variable.
    bool isValid;

    //Call CheckDigit() funciton.
    if (CheckDigit(isbn) == (isbn[12] - '0'))
        isValid = true;
    else
        isValid = false;

    //Return ISBN number validity to main().
    return isValid;
}


/*
1.1: Perform mathematical calculations on the ISBN number to generate
theoretical check digit to compare against the check digit contained within the
ISBN number.
*/
int CheckDigit(string input)
{
    //Declare local variables.
    int    checkDigit,
           i,
           num,
           sum = 0;

    //Generate theoretical check-digit.
    for (i = 0; i < 12; i++)
    {
        num = input[i] - '0';
        if (i%2)
            sum += num*3;
        else
            sum += num;
    }
    sum %= 10;
    checkDigit = (10 - sum);
    if (checkDigit == 10)
        checkDigit = 0;

    //Return check-digit to calling function.
    return checkDigit;
}
