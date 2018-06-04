#include <iostream>
#include <unordered_map>
#include <stdlib.h>
#include <vector>

using std::cout;
using std::cin;
using std::unordered_map;
using std::vector;

typedef unordered_map<int, int>::iterator iter;

void GenMoves(unordered_map<int, vector<int> > &);
void Randomize(unordered_map<int, int> &, unordered_map<int, vector<int> > &,
        int);
void Display(unordered_map<int, int>);


int main(int argc, char* argv[])
{
    //Seed random function with first command-line argument.
    srand(atoi(argv[1]));

    //Local variable declarations.
    unordered_map<int, int>          board;
    unordered_map<int, vector<int> > moves;

    //Prompt user to enter value for random seed and number of random moves.
    for(int i = 0; i < 9; ++i)
        cin >> board[i];

    //Generate moveset for board.
    GenMoves(moves);

    //Randomize the board with respect to second command-line argument.
    Randomize(board, moves, atoi(argv[2]));

    //Print final configuration.
    Display(board);

    return 0;
}

//Store potential moves corresponding to a given location.
void GenMoves(unordered_map<int, vector<int> > &moves)
{
    for(int k = 0; k < 9; k++)
    {
        if(k%2 == 1)
        {
            moves[k].push_back(4);
            if(k < 4)
                moves[k].push_back(0);
            else
                moves[k].push_back(8);
            if(k == 1 || k == 5)
                moves[k].push_back(2);
            else
                moves[k].push_back(6);
        }

        else
        {
            if(k <= 4)
                moves[k].push_back(1);
            if(k >= 4)
                moves[k].push_back(7);
            if(k == 0 || k == 4 || k == 6)
                moves[k].push_back(3);
            if(k == 2 || k == 4 || k == 8)
                moves[k].push_back(5);
        }
    }

    return;
}

void Randomize(unordered_map<int, int> &board, unordered_map<int, vector<int> >
        &moves, int num_of_moves)
{
    //Randomly slide pieces around the board.
    for(int i = 0; i < num_of_moves; ++i)
    {
        //Identify current location of missing piece.
        iter pos = board.begin();
        while(pos->second != 0)
            ++pos;

        //Randomly select a legal piece to slide into empty position.
        int temp = moves[pos->first][rand()%moves[pos->first].size()];

        //Identify the randomly selected piece and slide it into the empty
        //position.
        iter dest          = board.find(temp);
        board[pos->first]  = board[temp];
        board[dest->first] = 0;
    }

    return;
}

//Print board.
void Display(unordered_map<int, int> board)
{
    cout << '\n';
    for(int j = 0; j < 9; ++j)
    {
        cout << board[j] << ' ';
        if(j%3 == 2)
            cout << '\n';
    }

    return;
}
