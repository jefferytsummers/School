#include <iostream>
#include "mycomplexclass.h"

using namespace std;

MyComplexClass ComplexSum(MyComplexClass num1, MyComplexClass num2);
void DisplayArr(const MyComplexClass arr[]);

//Main
int main()
{
    MyComplexClass cNum1,
                   cNum2(1, -3);

    cin >> cNum1;

    cNum1.Display();

    cout << cNum2;

    if (cNum1.EqualTo(cNum2))
        cout << "The numbers are equal." << endl;
    else
        cout << "The numbers are not equal." << endl;

    MyComplexClass cNum3(cNum2);

    MyComplexClass cNumArray[20];

    MyComplexClass cNum4 = ComplexSum(cNum1, cNum2);

    cNum4.Display();

    DisplayArr(cNumArray);

    return 0;
}

MyComplexClass ComplexSum(MyComplexClass num1, MyComplexClass num2)
{
    MyComplexClass temp(num1.GetReal() + num2.GetReal(), num1.GetIm() +
                        num2.GetIm());

    return temp;
}

void DisplayArr(const MyComplexClass arr[])
{
    for (int i=0; i < 20; i++)
        cout << arr[i] << endl;

    return;
}
