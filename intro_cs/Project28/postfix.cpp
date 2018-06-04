#include <iostream>
#include <stack>
#include <string>
#include <stdio.h>
#include <ctype.h>

using namespace std;

void SkipSpaces();

//Main
int main()
{
    stack<string> myStack;
    string        input,
                  string1 = " ",
                  string2 = " ";
    char          char1,
                  char2;
    int           int1,
                  int2;
    string       intStr;

    cout << "Please enter a postfix expression: ";
    getline(cin, input);

    for (int i = 0; i < (input.length() - 1); i++)
    {
        char1 = input[i];
        while (char1 != ' ')
        {
            for (int j = i + 1; j < input.length(); j++)
            char1 = input[j];
            string1 += char1;
            cout << "OH NO" << endl;
        }
        char2 = input[i];
        while (char2 != ' ')
        {
            for (int j = i + 1; j < input.length(); j++)
            char2 = input[j];
            string2 += char2;
            cout << "OH NO" << endl;
        }

        if (string1 == "+")
        {
            int2 = stoi(myStack.top());
            myStack.pop();
            int1 = stoi(myStack.top());
            intStr = to_string(int1 + int2);
            myStack.push(intStr);
        }

        else if (string1 == "-")
        {
            int2 = stoi(myStack.top());
            myStack.pop();
            int1 = stoi(myStack.top());
            intStr = to_string(int1 - int2);
            myStack.push(intStr);
        }
        else if (string1 == "*")
        {
            int2 = stoi(myStack.top());
            myStack.pop();
            int1 = stoi(myStack.top());
            intStr = to_string(int1 * int2);
            myStack.push(intStr);
        }

        else if (string1 == "/")
        {
            int2 = stoi(myStack.top());
            myStack.pop();
            int1 = stoi(myStack.top());
            intStr = to_string(int1 / int2);
            myStack.push(intStr);
        }

        myStack.push(string1);
        myStack.push(string2);
    }

    return 0;
}
