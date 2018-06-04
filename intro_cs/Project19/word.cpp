#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

//Main
int main()
{
  //Declare variables.
  int               wordCount;
  string::size_type position;
  string            line;

  //Prompt user for input.
  cout << "Please enter a line of text:\n";

  //Initialize variables.
  wordCount = 1;
  getline(cin, line);
  position = line.find(" ");

  //Read through input and keep count of number of words in the input.
  while (position != string::npos)
  {
    position = line.find(" ", position + 1);
    wordCount++;
  }

  //Display word count for the user.
  cout << "There are " << wordCount << " words in this sentence." << endl;

  return 0;
}
