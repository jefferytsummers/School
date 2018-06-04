#include <iostream>
#include <fstream>
#include <cassert>
#include "list.h"

using namespace std;

void FindSum(List);

int main()
{
    List     list;
    ifstream myIn;
    int      value;

    myIn.open("integers.dat");
    assert(myIn);

    while ((!list.IsFull())&&(myIn >> value))
        list.Insert(value);

    FindSum(list);

    return 0;
}

void FindSum(List randList)
{
    int sum = 0;

    randList.Reset();

    for(int i = 0; i < randList.Length(); i++)
        sum += randList.GetNextItem();

    cout << "The sum is: " << sum << endl;

    return;
}
