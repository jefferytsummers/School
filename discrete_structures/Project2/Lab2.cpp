/*
  Author:      Ryan Florida
  Description: For this program, you will read in a two dimensional matrix and
               sort it. In order to perform the sort, you will need to read in
               the dimensions of the matrix (rows first, then columns), the
               matrix, and the column to sort on. The matrix should be no
               larger than 10X10.
*/

#include <iostream>

using std::cin;
using std::cout;

//Constant used for max array size.
const int MAX = 10;

//Declaring functions.
void GenerateMatrix(int &, int &, int [][MAX]);                             //1
void SortMatrix(int, int, int [][MAX]);                                     //2
void DisplayMatrix(int, int, int [][MAX]);                                  //3


//*****************************************************************************
//0: Main
int main()
{
    //Declaring variables.
    int inputArray[MAX][MAX];
    int row,
        column;

    //Function calls.
    GenerateMatrix(row, column, inputArray);
    SortMatrix(row, column, inputArray);
    DisplayMatrix(row, column, inputArray);

    return 0;
}


//*****************************************************************************
//1: Generate the [r x c] two-dimensional array based on user input.
void GenerateMatrix(int &row, int &column, int inputArray[][MAX])
{
    //Gather user input for row and column info.
    cout << "Input the rows and columns: ";
    cin  >> row >> column;

    cout << "Input the matrix:" << '\n';
    for(int i = 0; i < row; i++)
        for(int j = 0; j < column; j++)
            cin >> inputArray[i][j];

    return;
}


//*****************************************************************************
//2: Sort the array entered by the user according to the column of their
//   choosing.
void SortMatrix(int row, int column, int inputArray[][MAX])
{
    int minRow[MAX],
        tempVar,
        sortColumn;

    //Gather user input for sorting info.
    cout << "Input the sort column number:" << '\n';
    cin  >> sortColumn;

    for(int n = 0; n < row; n++)
    {
        for(int i = 0; i < column; i++)
            minRow[i] = inputArray[n][i];

        for(int i = n; i < row; i++)
        {
             if(inputArray[i][sortColumn - 1] < minRow[sortColumn - 1])
                for(int j = 0; j < column; j++)
                {
                    tempVar = inputArray[i][j];
                    inputArray[i][j] = minRow[j];
                    minRow[j] = tempVar;
                }

            if(minRow[sortColumn - 1] < inputArray[n][sortColumn - 1])
            for(int j = 0; j < column; j++)
                inputArray[n][j] = minRow[j];
        }
    }

    return;
}


//*****************************************************************************
//3: Display the sorted array.
void DisplayMatrix(int row, int column, int inputArray[][MAX])
{
    int newRowStart;

    cout << "The sorted matrix is:\n";
    for(int i = 0; i < row; i++)
    {
        newRowStart = 0;
        for(int j = 0; j < column; j++)
        {
            cout << inputArray[i][j] << " ";
            newRowStart++;
            if(newRowStart == column)
                cout << '\n';
        }
    }

    return;
}
