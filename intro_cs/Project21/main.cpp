#include <iostream>
#include "fraction.h"

using namespace std;


//Main
int main()
{
    //Use default constructor to declar frac1.
    Fraction frac1;

    //Use the >> operator to read from keyboard and assign num and denom values
    cout << "Enter values for numerator and denominator: ";
    cin >> frac1;

    //Use the << operator to display frac1.
    cout << "Fraction 1: " << frac1 << endl << endl;

    //Declare frac2 using copy constructor.
    Fraction frac2 = frac1;

    //Use SetDenominator method to change denom off frac2 to 5.
    frac2.SetDenominator(5);

    //Use the > operator to determine which fraction is larger.
    if (frac1 > frac2)
        cout << frac1 << " is larger than " << frac2 << endl << endl;
    else if (!(frac1 != frac2))
        cout << frac1 << " and " << frac2 << " are equivalent" << endl << endl;
    else
        cout << frac2 << " is larger than " << frac1 << endl << endl;

    //Use default constructor to declare frac3.
    Fraction frac3;

    //Use the Add method to add frac1 and frac2, assign value to frac3.
    frac3 = frac1.Add(frac2);

    //Use the << operator to display frac3.
    cout << "Fraction 3: " << frac3 << endl;

    return 0;
}
