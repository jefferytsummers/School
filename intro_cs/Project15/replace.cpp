#include <iostream>
#include <string>
#include <cctype>

using namespace std;


//Main
int main()
{
  //Declare variables.
  string            line,
                    newstring;
  string::size_type position,
                    locale;

  //Prompt User for input.
  cout << "Enter text: ";

  //Initialize variables.
  getline(cin, line);
  position = line.find("think");
  locale = 0;

  /*
  Reads through string, ignoring all instances of "think", and replaces said
  instances with "answer".
  */
  for (position = line.find("think"); position != string:: npos; locale =
       position + 5, position = line.find("think", locale))
  {
      newstring += line.substr(locale, position - locale) + "answer";
  }
      newstring += line.substr(locale);

  //Display new, and improved, string for the user.
  cout << "\nModified text: " << newstring << endl;

  return 0;
}
