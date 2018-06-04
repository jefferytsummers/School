#include <iostream>
#include "ttt.h"
#include <iomanip>

using namespace std;

//Initialize each square of the gameboard to ''
TTT::TTT()
{
    for (int row = 0; row < SIZE; row++)
    {
        for (int col = 0; col < SIZE; col++)
        {
            gameBoard[row][col] = ' ';
        }
    }
}

//Display the 3x3 gameboard on the screen.
void TTT::Display() const
{
        cout << gameBoard[0][0] << setw(2) << "|" << " " << " "
             <<  gameBoard[0][1] << setw(2) << "|" << " " << " "
             << gameBoard[0][2] << " " << endl << "___________" << endl
             << gameBoard[1][0] << setw(2) << "|" << " " << " "
             << gameBoard[1][1] << setw(2) << "|" << " " << " "
             << gameBoard[1][2] << " " << endl << "___________" << endl
             << gameBoard[2][0] << setw(2) << "|" << " " << " "
             << gameBoard[2][1] << setw(2) << "|" << setw(3) << gameBoard[2][2]
             << endl;

    return;
}

/*
Check whether one player won:
if player 'X' wins, return 'X',
if player 'O' wins, return 'O',
if no player wins, return 'N'.
*/
char TTT::CheckWon() const
{
    int  a = 0,
         b = 0,
         c = 0,
         d = 0,
         e = 0,
         f = 0,
         g = 0,
         h = 0,
         i = 0,
         j = 0,
         k = 0,
         l = 0,
         m = 0,
         n = 0,
         o = 0,
         p = 0,
         q = 0,
         r = 0;
    char won = 'N';

    for (int y = 0; y < SIZE; y++)
    {
        if (gameBoard[0][y] == 'X')
            a++;
        if (gameBoard[y][0] == 'X')
            b++;
        if (gameBoard[y][y] == 'X')
            c++;
        if (gameBoard[y][2-y] == 'X')
            d++;
        if (gameBoard[1][y] == 'X')
            e++;
        if (gameBoard[2][y] == 'X')
            f++;
        if (gameBoard[y][1] == 'X')
            g++;
        if (gameBoard[y][2] == 'X')
            h++;
        if (gameBoard[1][y] == 'O')
            i++;
        if (gameBoard[y][1] == 'O')
            j++;
        if (gameBoard[y][y] == 'O')
            k++;
        if (gameBoard[y][2-y] == 'O')
            l++;
        if (gameBoard[y][0] == 'O')
            m++;
        if (gameBoard[0][y] == 'O')
            n++;
        if (gameBoard[2][y] == 'O')
            o++;
        if (gameBoard[y][2] == 'O')
            p++;

        if (a == 3 || b == 3 || c == 3 || d == 3 || e == 3 || f == 3 || g == 3
            || h == 3)
        {
            won = 'X';
            break;
        }
        else if (i == 3 || j == 3 || k == 3 || l == 3 || m == 3 || n == 3 ||
                 o == 3 || p == 3)
        {
            won = 'O';
            break;
        }
    }

    return won;
}

/*
If the gameboard position row x and col y already has a piece on it,
operation "Assign" fails, return false.
Otherwise, assign player ('X' or 'O') at gameboard position row x and col
y; then return true.
x (IN): row number to assign to next piece.
y (IN): column number to assign the next piece.
player (IN): 'X' or 'O'.
*/
bool TTT::Assign(int x, int y, char player)
{
    if (gameBoard[x][y] == ' ')
    {
        gameBoard[x][y] = player;
        return true;
    }
    return false;
}

/*
Check to see if there is any blank square left on the gameboard (to
continue to play).
Returns true or false, depending on whether the gameboard is full or not.
*/
bool TTT::BoardFull() const
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (gameBoard[i][j] == ' ')
                return false;
        }
    }
    return true;
}
