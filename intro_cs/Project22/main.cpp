#include <iostream>
#include "list.h"
#include <string>

using namespace std;

void BuildList(List& list);   //1
void DisplayList(List& list); //2

int main()
{
    //Use default constructor to declare list1.
    List list1;

    //Call BuildList() to build "list1".
    BuildList(list1);

    //Call DisplayList() to display values in "list1".
    DisplayList(list1);

    //Use copy constructor to declare list2.
    List list2 = list1;

    //Prompt user to enter a(n) item/value to be deleted from list2.
    cout << "Enter value to delete: ";
    ItemType var;
    cin.clear();
    cin >> var;
    cout << endl;
    if (list2.IsPresent(var))
        list2.DeleteAll(var);
    cout << endl;

    //Call Display to display values in "list2".
    DisplayList(list2);

    return 0;
}

//1: Inserts values, for standard input, into the input list.
void BuildList(List& list)
{
    //Declare variables.
    string   str;
    ItemType value;

    //This is where the value insertion takes place.
    cout << "Enter a value to add: (type done to stop)" << endl;

    cin >> str;
    do
    {
        value = stoi(str);
        list.AddAtFront(value);

    } while (cin >> str);

    cin.clear();
    cout << endl;

    return;
}

//2: Display contents of list.
void DisplayList(List& list)
{
    cout << list.Length() << " values in the list:" << endl;

    list.Reset();
    for (int i = 0; i < list.Length(); i++)
        cout << list.GetNextItem() << endl;
    cout << endl;
    return;
}
