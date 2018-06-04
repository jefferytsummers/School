#include <iostream>
#include <string>

using namespace std;


//Main
int main()
{
    //Declaring variables.
    int    count,
           frequency[26],
           i,
           m;
    string text;
    char   letter[26];

    //Prompt user for input.
    cout << "Enter text: ";

    /*
    The outer loop collects user input and initializes variables and arrays. The
    inner loop then compares each lowercase English alphabet character, which
    comprise the "letter" array, to a lowercase version of each character in the
    user's input. During this comparison, if two characters are found to match,
    the "count" variable will be incremented so as to keep a running total of
    the number of occurences of each letter contained in the user's input. The
    results will then be displayed for the user by showing each character in the
    alphabet and its corresponding amount of appearences in the user's input.
    */
    for (getline(cin, text), i = 0, count = 0; i < 26; i++, count = 0)
    {
        frequency[i] = 0;
        letter[i] = char('a' + i);

        for (m = 0; m < text.length(); m++)
        {
            if (isupper(text[m]))
                text[m] = tolower(text[m]);

            if (text[m] == letter[i])
                count++;
            frequency[i] = count;
        }

        cout << letter[i] << " : " << frequency[i] << endl;
    }

    return 0;
}
