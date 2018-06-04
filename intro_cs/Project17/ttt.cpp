#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <stdlib.h>

using namespace std;

const int SIZE=3;
// declare all the functions here
void InitializeBoard(char gameBoard [][SIZE]);
void Display(char gameBoard[][SIZE]);
bool BoardIsFull(char gameBoard[][SIZE]);
bool Assign(char gameBoard[][SIZE], int x, int y, char p);
char CheckWon(char gameBoard[][SIZE]);

int main()
{
   char turn;
   int x, y;
   char gameBoard[SIZE][SIZE];

   InitializeBoard(gameBoard);
   int t = rand()%2;
   if (t == 1)
   	   turn='X';
   else
     	 turn='O';
   cout << "Game Starts!" << endl;

   Display(gameBoard);
   while (!BoardIsFull(gameBoard) && (CheckWon(gameBoard)=='n'))
   {
       do
       {
          do
          {
              cout << "Player " << turn << " makes the next move."<<endl;
              cout << "Enter the x, y location, 0<=x<3, 0<=y<3: ";
              cin >> x >> y;
          } while (x > 2 || x < 0 || y > 2 || y < 0);
       } while (!Assign(gameBoard, x, y, turn));

       Display(gameBoard);

       if (turn == 'X')
       	   turn = 'O';
       else
           turn = 'X';
   }

   if (CheckWon(gameBoard) == 'X')
       cout << "Player X wins!" << endl;
   else if (CheckWon(gameBoard) == 'O')
       cout << "Player O wins!" << endl;
   else
       cout << "This is a Draw game!" << endl;

    return 0;
}

// This function initialize all the elements of the game board to blanks ' '
void InitializeBoard(char gameBoard [][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
            gameBoard[i][j] = ' ';
    }
    return;
}

// This function displays the game board as a 3 by 3 board
void Display(char gameBoard[][SIZE])
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

// This function checks to see if all the elements of the game board have been filled
bool BoardIsFull(char gameBoard[][SIZE])
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

// This function assigns character p to location (x, y) on the game board
// p is either 'X' or 'O'
bool Assign(char gameBoard[][SIZE], int x, int y, char p)
{
    if (gameBoard[x][y] == ' ')
    {
        gameBoard[x][y] = p;
        return true;
    }

    return false;
}

// check to see if the game is over by checking
// if any row, column or diagonal has the same character
// if 'X' is on all elements of a row, column, or diagonal, 'X' is returned
// if 'O' is ............................................., 'O' is returned
// otherwise, 'n' is returned.
char CheckWon(char gameBoard[][SIZE])
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
         p = 0;
    char won = 'n';

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
        if (gameBoard[1][y] == 'O')
            e++;
        if (gameBoard[y][1] == 'O')
            f++;
        if (gameBoard[y][y] == 'O')
            g++;
        if (gameBoard[y][2-y] == 'O')
            h++;
        if (gameBoard[1][y] == 'X')
            i++;
        if (gameBoard[2][y] == 'X')
            j++;
        if (gameBoard[y][1] == 'X')
            k++;
        if (gameBoard[y][2] == 'X')
            l++;
        if (gameBoard[1][y] == 'O')
            m++;
        if (gameBoard[2][y] == 'O')
            n++;
        if (gameBoard[y][1] == 'O')
            o++;
        if (gameBoard[y][2] == 'O')
            p++;

        if (a == 3 || b == 3 || c == 3 || d == 3 || i == 3 || j == 3 || k == 3
            || l == 3)
        {
            won = 'X';
            break;
        }
        else if (e == 3 || f == 3 || g == 3 || h == 3 || m == 3 || n == 3 ||
                 o == 3 || p == 3)
        {
            won = 'O';
            break;
        }
    }
    // write multiway if statement to check whether a win condition is met

    return won;
}
