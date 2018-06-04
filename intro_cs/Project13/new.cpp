#include <iostream>

using namespace std;

int main()
{
    typedef int* intPtr;

    intPtr p,q;
    int x =3, y=6;

    p = &y;
    q = p;
    *q=*p +1;
    x = *q;
    y = x + 1;

    cout << x << " " << y << " " << *p << " " << *q << endl;

    p = new int;
    *p = 5;
    *q = *p + 2;
    x = *q;

    cout << x << " " << y << " " << *p << " " << *q << endl;

    q = new int;
    delete p;
    p = q;
    delete p;
    p = NULL;
    q = NULL;

    cout << x << " " << y << " " << p << " " << endl;

    return 0;
}
