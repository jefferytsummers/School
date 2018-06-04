#ifndef TTT_H
#define TTT_H

const int SIZE = 3;

class TTT
{
  public:

      //Initialize each square of the gameboard to ''
      TTT();

      //Display the 3x3 gameboard on the screen.
      void Display() const;

      /*
      Check whether one player won:
      if player 'X' wins, return 'X',
      if player 'O' wins, return 'O',
      if no player wins, return 'N'.
      */
      char CheckWon() const;

      /*
      If the gameboard position row x and col y already has a piece on it,
      operation "Assign" fails, return false.
      Otherwise, assign player ('X' or 'O') at gameboard position row x and col
      y; then return true.
      x (IN): row number to assign to next piece.
      y (IN): column number to assign the next piece.
      player (IN): 'X' or 'O'.
      */
      bool Assign(int x, int y, char player);

      /*
      Check to see if there is any blank square left on the gameboard (to
      continue to play).
      Returns true or false, depending on whether the gameboard is full or not.
      */
      bool BoardFull() const;

  private:

      char gameBoard[SIZE][SIZE];
};

#endif
