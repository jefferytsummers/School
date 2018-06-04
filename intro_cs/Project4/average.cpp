#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <iomanip>

using namespace std;

int main()
{
  //Declaring variables.
  int      nums,
           largestNum,
           smallestNum,
           testNum;
  float    sum,
           average;
  ifstream myIn;

  //Initializing variables.
  smallestNum = 2147483647;
  largestNum = -smallestNum;

  //Opening input file.
  myIn.open("../lab5-1.dat");
  assert(myIn);

  cout << "The values read are: " << endl;

  /*
  Read through file, counting and summing the numbers contained within. Also
  identifies the smallest and largest numbers in the input file and displays
  file contents.
  */
  while (myIn >> testNum)
  {
    cout << testNum << endl;
    if (largestNum < testNum)
      largestNum = testNum;
    if (smallestNum > testNum)
      smallestNum = testNum;
    sum += testNum;
    nums++;
  }

  //Compute average of numbers collected from file.
  average = sum/nums;

  //Formatting.
  cout << fixed << setprecision(1);

  //Displays output.
  cout << endl << "Total " << nums << " numbers." << endl << "The largest"
       << " number is " << largestNum << ", and the smallest number is "
       << smallestNum << '.' << endl << "The average of these numbers is "
       << average << '.' << endl;

  //Close input file.
  myIn.close();

  return 0;
}
