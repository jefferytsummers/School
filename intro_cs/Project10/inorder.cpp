#include <iostream>

using namespace std;

int main()
{
    //Declaring variables.
    int value1,
        value2,
        value3,
		temp;

    //Ask user for 3 integral values.
    cout << "Please enter three integer values: ";

    //Get input from user.
    cin >> value1 >> value2 >> value3;

    //If value1 is larger than value2, then their respective values will be swapped.
    if (value1 > value2)
    {
		temp   = value1;
        value1 = value2;
        value2 = temp;
    }

    //If value2 is larger than value3, then their respective values will be swapped.
    if (value2 > value3)
    {
        temp   = value2;
        value2 = value3;
        value3 = temp;
    }

    //If new value1 is larger than new value2, then their respective values will be swapped.
    if (value1 > value2)
    {
        temp   = value1;
        value1 = value2;
        value2 = temp;
    }

    //Displays the input values, in ascending order, for the user.
    cout << "The three values in ascending order are: " << value1
    << ' ' << value2 << ' ' << value3 << endl;
	
	return 0;
}
