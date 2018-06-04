#include <iostream>
#include <stack>
#include <string>
#include <fstream>
#include <cassert>

using namespace std;


//Main
int main()
{
    //Declare variables.
    stack<string>  myStack1,
                   myStack2;
    string         name;
    ifstream       myIn;

    //Open and assert data file.
    myIn.open("names.dat");
    assert(myIn);

    //Read in names to stack.
    while (getline(myIn, name))
        myStack1.push(name);

    //Print reverse-order list whilst, simultaneously, empyting the first stack
    //and filling the second stack.
    cout << "The list of " << myStack1.size() << " names in reverse order:"
         << endl;
    while (!myStack1.empty())
    {
        name = myStack1.top();
        myStack2.push(name);
        cout << myStack1.top() << endl;
        myStack1.pop();
    }

    //Print original-order list whilst emptying second stack.
    cout << endl << endl << "The list of " << myStack2.size() << " names in the"
         << " original order:" << endl;
    while (!myStack2.empty())
    {
        cout << myStack2.top() << endl;
        myStack2.pop();
    }

    return 0;
}
