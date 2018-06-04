/*
PROGRAMMER:          Ryan Florida
Assignment:          OLA5
Class:               CSCI 2170 Section 001
Course Instructor:   Dr. Li
Due Date:            Midnight, July 21 2016

Description:         This program simulates a friendly match of the popular game
                     tic-tac-toe with the use of object-oriented programming.
*/

#include <iostream>
#include "ttt.h"
#include <stdlib.h>
#include <ctime>

using namespace std;


//Main
int main()
{
    //Declare variables and object.
    TTT  board;  //Stores initialized tic-tac-toe board.
    int  row,    //Stores value for row of board array.
         col,    //Stores value for column of board array.
         t;      //Stores value determining who will go first.
    char turn;   //Stores whose turn it is.

    //Seed random function.
    srand(0);

    //Decide, at random, who will move first.
    t = rand()%2;
    if (t == 1)
    	   turn='X';
    else
      	 turn='O';

    //Let user(s) know that the game has started.
    cout << "Game Starts!" << endl;

    //Display initialized board.
    board.Display();

    /*
    Allow players to fill the board with X's and O's until there is a decided
    winner, or until the game has resulted in a tie.
    */
    while (!board.BoardFull() && (board.CheckWon() == 'N'))
    {
       /*
       Prompt players to enter a proper row and column to place their respective
       characters (X's and O's) in. The loop exits when a proper input has been
       received.
       */
        do
        {
           do
           {
               cout << "Player " << turn << " makes the next move." << endl;
               cout << "Enter the x, y location, 0 <= x < 3, 0 <= y < 3: ";
               cin >> row >> col;
           } while (row > 2 || row < 0 || col > 2 || col < 0);
        } while (!board.Assign(row, col, turn));

        //Display updated board for players.
        board.Display();

        //Switch to other player's turn.
        if (turn == 'X')
        	   turn = 'O';
        else
            turn = 'X';
    }

    //Display winner, if one exists, for the user.
    if (board.CheckWon() == 'X')
        cout << "Player X wins!" << endl;
    else if (board.CheckWon() == 'O')
        cout << "Player O wins!" << endl;
    else
        cout << "This is a Draw game!" << endl;

     return 0;
}
