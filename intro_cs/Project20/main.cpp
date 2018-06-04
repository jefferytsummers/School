#include <iostream>
#include "dateClass.h"

using namespace std;

//Main.
int main()
{
    //Initialize objects.
    dateClass date1;
    dateClass date2(5, 15, 2015);

    //Set date for first object.
    date1.SetDate(3, 17, 2016);

    //Display object information.
    date1.Display();
    date2.Display();

    return 0;
}
