/*
PROGRAMMER:              Ryan Florida
Assignment:              OLA 2, Problem 1
Class:                   CSCI 2170 Section 001
Course Instructor:       Dr. Li
Due Date:                Midnight, Monday, 7/11/2016

Description:             This program takes as its input, from standard input,
                         a natural number. The number is then tested to see if
                         it meets the criteria of being considered a perfect
                         number. If the number happens to meet this criteria,
                         the user will be notified, in standard output, that the
                         number is perfect. Otherwise, the user will be alerted
                         that their input was not perfect.
*/

#include <iostream>

using namespace std;

//Declaring functions.
int  getUserInput(); //1

bool isPerfect(int num); //2


//0: Main
int main()
{
    //Declaring variable.
    int testNum;       //Used to store value from getUserInput().

    //Set variable value.
    testNum = getUserInput();

    /*
    Displays appropriate message to the user, dependent upon truth value
    returned by isPerfect(testNum).
    */
    if (isPerfect(testNum))
        cout << testNum << " is a perfect number." << endl;
    else
        cout << testNum << " is not a perfect number, Nicomachus would be sad."
             << endl;

    return 0;
}


/*
1: Gets positive integer (natural number) input from the user. The prompt
   will not cease until the proper input is received. The input integer is
   returned to main().
*/
int getUserInput()
{
    //Declaring variable.
    int integer; //This variable will store the value input by the user.

    /*
    Prompts the user to input a positive integer. If the user enters an invalid
    number, that is a non-integral/positive number, then the user will be
    prompted repeatedly for the proper input.
    */
    do
    {
        cout << "Please enter a natural number that you would like to test for"
             << " perfection: " << endl;
        cin  >> integer;
    } while (integer <= 0);

    //Returns natural number value for use by main().
    return integer;
}


/*
2: The input to this function is a type int variable. The function will
   iterate through all numbers up to, and including, half the value of the
   input integer; in a contemporaneous manner, the function will determine
   which of the numbers are proper divisors of the input integer. The numbers,
   which are determined to be divisors of the input integer, will then be
   summed and the resultant sum will dictate whether the number is perfect or
   not. The function will return "true" if the integer is perfect or "false" if
   the integer is non-perfect.
*/
bool isPerfect(int num)
{
    //Declaring variables.
    int  divisor,      //Used to store value of all potential divisor values.
         divisorSum;   //Used to store a running total of all divisor values.

    bool perfect;      //Used to store truth.

    /*
    Iterate through all potential proper divisors, select proper divisors, and
    sum them. Truth value only set to true if the sum of the number's proper
    divisors is equal to the number itself.
    */
    for (divisor = 1, divisorSum = 0, perfect = false; divisor <= num/2;
         divisor++)
    {
        if (num % divisor == 0)
        {
            divisorSum += divisor;
            if (divisorSum == num)
                perfect = true;
        }
    }
    //Returns truth value for use by main().
    return perfect;
}
