//This program was written to compare the time-efficiency of three different
//ways of performing the same computation.
#include <iostream>

using std::cout;
using std::cin;

//1: Recursive sum.
int SRec(int);
//2: Iterative sum.
int SIter(int);
//3: Formulaic sum.
int SFormula(int);

//0: Main.
int main()
{
    int n;

    cout << "Enter a value for n: ";
    cin >> n;

    clock_t start;
    double duration1,
           duration2,
           duration3;

    start = clock();
    SRec(n);
    duration1 = (double) (clock() - start)/ CLOCKS_PER_SEC;

    start = clock();
    SIter(n);
    duration2 = (double) (clock() - start)/ CLOCKS_PER_SEC;

    start = clock();
    SFormula(n);
    duration3 = (double) (clock() - start)/ CLOCKS_PER_SEC;

    cout << "duration for recursive call: " << duration1 << '\n'
         << "duration for iterative call: " << duration2 << '\n'
         << "duration for formulaic call: " << duration3 << '\n';
    return 0;
}

//1
int SRec(int n)
{
    if(n == 1)
        return 1;

    return SRec(n - 1) + n;
}

//2
int SIter(int n)
{
    int sum = 0;

    for(int i = 1; i < (n+1); i++)
        sum += i;

    return sum;
}

//3
int SFormula(int n)
{
    return n*(n+1)/2;
}
