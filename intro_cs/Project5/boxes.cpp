/*
PROGRAMMER:          Ryan Florida
Assignment:          OLA 3
Class:               CSCI 2170 Section 001
Course Instructor:   Dr. Li
Due Date:            Midnight, Thursday July 14 2016

Description:         This program takes in a file, "boxes.dat", and processes
                     the data contained within the file. In this processing, the
                     data is divided up into two different arrays, one of type
                     int and the other of type string. The int type array is
                     then searched through to find the highest value, and the
                     string type array is searched through, afterward, to find
                     the corresponding string associated with the value found in
                     the int type array. After this processing is complete, the
                     resultant data is output into an *ordered table for the
                     user to view. The highest value, and associated string, are
                     also displayed.

                     *A NOTE ON EXTRA CREDIT: The extra credit was completed
                      using the "AscendingSort" (3) below. However, special care
                      was taken to ensure that the program works seamlessly,
                      that is as it was normally supposed to, without the
                      implementation of this function.
*/

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cassert>

using namespace std;

//Declare functions.
//1
int    ReadData(ifstream &file, string strArray[], int intArray[]);
//2
string FindWinner(const string strArray[], const int intArray[],
                  int distinctClassNum);
//3
void   AscendingSort(string strArray[], int intArray[], int distinctClassNum);
//4
void   DisplayResults(const string strArray[], const int intArray[],
                      int distinctClassNum, string winClass);
//1.1
int    LinearSearch(const string strArray[], string name);

//Declare global constant.
const int SIZE = 1000;


//0: Main.
int main()
{
    //Declare variables.
    string    classNames[SIZE],    //Array to store class names.
              winningClass;        //Stores name of winning class.
    int       boxes[SIZE],         //Array to store boxes sold by classes.
              distinctClassCount;  //Stores number of distinct classes.
    ifstream  inFile;              //File object.

    //Open "boxes.dat" file.
    inFile.open("boxes.dat");
    assert(inFile);

    //Call functions and store values from value-returning functions.
    distinctClassCount = ReadData(inFile, classNames, boxes);
    winningClass       = FindWinner(classNames, boxes, distinctClassCount);
    AscendingSort(classNames, boxes, distinctClassCount);
    DisplayResults(classNames, boxes, distinctClassCount, winningClass);

    //Close file.
    inFile.close();

    return 0;
}


/*
1: Reads data from input file, processes said data, then places the data in two
   different arrays depending on the data's type. Thus, there will be a string
   type and an int type array filled. The processing, mentioned above, that
   takes place just filters out repeat class names and adds the number of boxes
   sold, corresponding to the repeat names, to the number of boxes sold
   corresponding to the first instance of that class name.
*/
int ReadData(ifstream &file, string strArray[], int intArray[])
{
    //Declare local variables.
    string name;
    int    amount,
           index,
           count = 0;

    //Assign file data to appropriate arrays.
    while (file >> name >> amount)
    {
        index = LinearSearch(strArray, name);
        if (index >= 0)
            intArray[index] += amount;
        else
        {
            strArray[count] = name;
            intArray[count] = amount;
            count++;
        }
    }

    //Return count to main.
    return count;
}


/*
2: Searches array containing information about how many boxes were sold for the
   highest amount of boxes sold. Upon discovery of the highest amount of boxes
   sold, the corresponding team name will be located and assigned to a string
   type variable "winner". This variable is then returned to main for later use.
*/
string FindWinner(const string strArray[], const int intArray[],
                  int distinctClassNum)
{
    //Declare local variables.
    string winner;   //Stores name of winning class.
    int    max = 0;  //Stores index of winning class.

    //Find max value within array.
    for (int j = 0; j < distinctClassNum; j++)
    {
        if (intArray[j] > intArray[max])
            max = j;
    }

    /*
    Assign winner the array entry in the string array corresponding to the
    maximum value array entry found above.
    */
    winner = strArray[max];

    //Return winner to main.
    return winner;
}


/*
*********************************EXTRA-CREDIT**********************************
3: Sort boxes array in ascending order by number of boxes sold, adjusts classes
   accordingly.
*******************************************************************************
*/
void AscendingSort(string strArray[], int intArray[], int distinctClassNum)
{
    //Declare local variables.
    int    minIndex,  //Stores index of lowest number of boxes sold.
           inttemp;   //Temporary variable to hold integer value.
    string strtemp;   //Temporary variable to hold string.

    //Sort list from low to high with regard to boxes sold.
    for (int i = 0; i < (distinctClassNum - 1); i++)
    {
        minIndex = i;
        for (int j = (i + 1); j < distinctClassNum; j++)
        {
            if (intArray[j] < intArray[minIndex])
                minIndex = j;
        }
        if (minIndex != i)
        {
            inttemp            = intArray[i];
            intArray[i]        = intArray[minIndex];
            intArray[minIndex] = inttemp;

            strtemp            = strArray[i];
            strArray[i]        = strArray[minIndex];
            strArray[minIndex] = strtemp;
        }
    }
    return;
}


/*
4: Displays a neat table of output for the user, as well as the name of the
   winning class and the corresponding number of boxes sold.
*/
void DisplayResults(const string strArray[], const int intArray[],
                    int distinctClassNum, string winClass)
{
    //Declare local variable.
    int numBoxes = intArray[LinearSearch(strArray, winClass)];  /*
                                                                Stores number of
                                                                boxes sold
                                                                corresponding
                                                                to the winning
                                                                class.
                                                                */

    //Display final results for user.
    cout << "The final results are:" << endl;
    for (int i = 0; i < distinctClassNum; i++)
    {
        cout << setw(8) << left << strArray[i] << setw(14) << right
             << intArray[i] << endl;
    }

    //Display name of winning class and corresponding number of boxes sold.
    cout << endl << "The winning class is " << winClass << ", with "
         << numBoxes << " boxes sold." << endl;

    return;
}


/*
1.1: Searches input string type array for specific string, returns
     corresponding index for use by main. If the string was found to not be in
     the input array, a value of -1 is returned to main.
*/
int LinearSearch(const string strArray[], string name)
{
    for(int i = 0; i < SIZE; i++)
    {
        if(strArray[i] == name)
            return i;
    }
    return -1;
}
