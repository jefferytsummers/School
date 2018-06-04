#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <iomanip>

using namespace std;

//Declaring functions.
void OpenFile(ifstream &myIn);  //1
void ComputeStatistics(ifstream &myIn, int &cnt, int &large, int &small, float
                       &avg);   //2
void DisplayResults(int cnt, int large, int small, float avg);  //3

//0: Main
int main()
{
  //Declaring variables.
  int      smallestNum,
           count,
           largestNum;
  float    average;
  ifstream myIn;

  //Initializing variables.
  smallestNum = 2147483647;
  largestNum = -smallestNum;
  count = 0;

  //Call "OpenFile()".
  OpenFile(myIn);

  //Call "ComputeStatistics()".
  ComputeStatistics(myIn, count, largestNum, smallestNum, average);

  //Call "DisplayResults()".
  DisplayResults(count, largestNum, smallestNum, average);

  //Close file opened by "OpenFile()".
  myIn.close();

  return 0;
}


//1: Prompts user to input a file name, then opens said file.
void OpenFile(ifstream &myIn)
{
  //Declare local variable.
  string   userInput;

  //Prompt user for input and collect said input.
  cout << "Please enter the data file name: ";
  cin >> userInput;

  //Open file selected by the user.
  myIn.open(userInput.c_str());
  assert(myIn);

  //Pre-formatting for later.
  cout << "\n \n";

  return;
}


/*
2: Reads through file opened by "OpenFile()", finds the smallest and largest
integers contained within the file, and computes the average of all numbers
contained within the file. 
*/
void ComputeStatistics(ifstream &myIn, int &cnt, int &large, int &small, float
                       &avg)
{
  //Declare local variables.
  int   testNum;
  float sum;

  //Initialize sum.
  sum = 0;

  /*
  Display contents of file chosen by user, as well as sum the contents and
  determine the smallest and largest values contained within.
  */
  cout << "The values read are: " << endl;
  while (myIn >> testNum)
  {
    cnt++;
    cout << testNum << endl;
    if (large < testNum)
      large = testNum;
    if (small > testNum)
      small = testNum;
    sum += testNum;
  }
  cout << "\n";

  //Compute average of the values contained within the input file.
  avg = sum/cnt;

  return;
}


/*
3: Properly formats and displays the results obtained from "ComputeStatistics()"
*/
void DisplayResults(int cnt, int large, int small, float avg)
{
  //Formatting floats.
  cout << fixed << setprecision(1);

  //Orderly display of the results for the user.
  cout << "Total " << cnt << " numbers." << endl << "The largest number is "
       << large << ", and the smallest number is " << small << '.' << endl
       << "The average of these numbers is " << avg << '.' << endl;

  return;
}

