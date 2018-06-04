/*
PROGRAMMER:          Ryan Florida
Assignment:          OLA 4
Class:               CSCI 2170 Section 001
Course Instructor:   Dr. Li
Due Date:            Midnight, Monday July 18 2016

Description:         This program generates a deck of playing cards, then
                     shuffles said deck of cards. Based on the number of
                     players, and how many cards each player gets (which really
                     depends on the game being played), the cards will be dealt
                     accordingly. There is a two-dimensional array, representing
                     the number of players and the amount of cards each player
                     is to receive, that the cards will be "dealt" into. Once
                     the cards have been dealt, the program will simulate the
                     players "sorting" their cards, by suit and value. When
                     this process is done, the players' cards will be displayed.
                     The specific card game simulated by this program is the
                     game of Hearts.
*/

#include <iostream>
#include <string>
#include <iomanip>
#include <time.h>
#include <stdlib.h>

using namespace std;

//Create type.
struct CardType
{
    string suit;
    int    value,
           points;
};

//Global constants.
const int SIZE        = 52,  //Stores size of deck array.
          PLAYERS     = 4,   //Stores number of players involved in game.
          CARDS_DEALT = 13;  //Stores number of cards dealt to each player.

//Declare Functions.
void FormCards(CardType arr[]);                                              //1
void ShuffleCards(CardType arr[]);                                           //2
void DealCards(const CardType arr[], CardType multArr[PLAYERS][CARDS_DEALT]);//3
void SortCards(CardType arr[PLAYERS][CARDS_DEALT]);                          //4
void PrintCards(const CardType multArr[PLAYERS][CARDS_DEALT]);               //5
void Swap(CardType &matrixEntry1, CardType &matrixEntry2);                 //2.1


//Main
int main()
{
    //Seed random number generator.
    srand(time(0));

    //Declare variable.
    CardType deck[SIZE],                      //Stores the cards in the deck.
             players[PLAYERS][CARDS_DEALT];   /*
                                              Stores the players and the cards
                                              in each players hand.
                                              */

    //Call functions.
    FormCards(deck);
    ShuffleCards(deck);
    DealCards(deck, players);
    SortCards(players);
    PrintCards(players);

    return 0;
}


/*
1: Assigns suit, value, and points to each card in the deck of cards. Takes
   input of type CardType.
*/
void FormCards(CardType arr[])
{
    //Declare local variables.
    int innerLoopCount  = 0,  //Stores number of iterations of the inner loop.
        outerLoopCount  = 0;  //Stores number of iterations of the outer loop.

    /*
    Generates deck. This loop satisfies all requirements the function set out to
    meet
    */
    for (int i = 0; i < 4; i++, outerLoopCount++)
    {
        for (int j = 0; j < 13; j++, innerLoopCount++)
        {
            arr[innerLoopCount].value = j + 1;
            if (outerLoopCount == 0)
            {
                arr[innerLoopCount].suit = "Diamond";
                if (j == 10)
                    arr[innerLoopCount].points = -100;
                else
                    arr[innerLoopCount].points = 0;
            }
            else if (outerLoopCount == 1)
            {
                arr[innerLoopCount].suit = "Club";
                arr[innerLoopCount].points = 0;
            }
            else if (outerLoopCount == 2)
            {
                arr[innerLoopCount].suit = "Heart";
                if (j < 9)
                    arr[innerLoopCount].points = 5;
                else
                    arr[innerLoopCount].points = 10;
            }
            else
            {
                arr[innerLoopCount].suit = "Spade";
                if (j == 11)
                    arr[innerLoopCount].points = 100;
                else
                    arr[innerLoopCount].points = 0;
            }
        }
    }

    return;
}


/*
2: Takes the array of cards generated above and randomly shuffles the entries.
   Takes input of type CardType.
*/
void ShuffleCards(CardType arr[])
{
    //Declare local variable.
    int      index;  //stores random number used for swapping.

    //Swaps each card in the input array with a random other card in the array.
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < 11011; j++)  //11011 was arbitrarily chosen.
        {
            index = rand()%51;
            Swap(arr[i], arr[index]);
        }
    }

    return;
}


/*
3: Distributes the cards, that were generated and shuffled above, to a two-
   dimensional array. This two-dimensional array represents the number of
   players (rows) and the amount of cards each player is to recieve (columns).
   Takes two inputs, each of type CardType.
*/
void DealCards(const CardType arr[], CardType multArr[PLAYERS][CARDS_DEALT])
{
    //Declare local variable.
    int card = 0;  //Stores the place number of the card being assigned.

    /*
    This loop was set up such that each player would recieve one card before
    anyone got their next card.
    */
    for (int col = 0; col < CARDS_DEALT; col++)
    {
        for (int row = 0; row < PLAYERS; row++)
        {
            multArr[row][col] = arr[card];
            card++;
        }
    }

    return;
}


/*
4: Sorts cards in each players hand based on card suit and then by value. Takes
   input of type CardType.
*/
void SortCards(CardType multArr[PLAYERS][CARDS_DEALT])
{
    //Declare local variables.
    int    minIndex1,  //Stores value of suit index we are working with.
           minIndex2;  //Stores value of value index we are working with.

    for (int i = 0; i < PLAYERS; i++)
    {
        for (int j = 0; j < (CARDS_DEALT - 1); j++)
        {
            //Initialize local variables.
            minIndex1 = j;
            minIndex2 = j;

            //Sort cards by suit.
            for (int k = (j + 1); k < CARDS_DEALT; k++)
            {
                if (multArr[i][k].suit < multArr[i][minIndex1].suit)
                    minIndex1 = k;
            }
            if (minIndex1 != j)
                Swap(multArr[i][j], multArr[i][minIndex1]);

            //Sort cards by value.
            for (int k = (j + 1); k < CARDS_DEALT; k++)
            {
                if ((multArr[i][k].suit == multArr[i][j].suit)
                    && (multArr[i][k].value > multArr[i][minIndex2].value))
                        minIndex2 = k;
            }
            if (minIndex2 != j)
                Swap(multArr[i][j], multArr[i][minIndex2]);
        }
    }

    return;
}


/*
5: Displays the players, and their cards, in an organized table. Takes input of
   type CardType.
*/
void PrintCards(const CardType multArr[PLAYERS][CARDS_DEALT])
{
    //Declare local variable.
    string display;  //Stores display string based on card value.

    //Display the cards, suits, values, points, contained in each player's hand.
    for (int i = 0; i < PLAYERS; i++)
    {
        //Display current player whose info is being displayed.
        cout << "PLAYER" << (i + 1) << endl << "  SUIT      VALUE      POINTS"
             << endl;

        //Display cards contained in each player's hand.
        for (int j = 0; j < CARDS_DEALT; j++)
        {
            //Convert value to proper display string.
            if (multArr[i][j].value > 1 && multArr[i][j].value < 10)
                display = multArr[i][j].value + '0';
            else if (multArr[i][j].value == 1)
                display = "A";
            else if (multArr[i][j].value == 10)
                display = "10";
            else if (multArr[i][j].value == 11)
                display = "J";
            else if (multArr[i][j].value == 12)
                display = "Q";
            else if (multArr[i][j].value == 13)
                display = "K";

            //Formatting
            if (multArr[i][j].suit == "Diamond")
            {
                cout << setw(8) << multArr[i][j].suit << setw(6) << " "
                     << left << setw(2) << display << setw(10) << " "
                     << setw(3) << multArr[i][j].points << endl;
            }
            else
            {
              cout << "  " << setw(5) << left << multArr[i][j].suit << setw(7)
                   << " " << setw(2) << display << setw(10) << " "
                   << setw(3) << multArr[i][j].points << endl;
            }
        }
        cout << endl;
    }

    return;
}


//2.1: Swap two input values, of type CardType, in an array with one another.
void Swap(CardType &matrixEntry1, CardType &matrixEntry2)
{
    //Declare local variable.
    CardType temp;  //Store temporary value.

    //Swap input values with one another.
    temp         = matrixEntry1;
    matrixEntry1 = matrixEntry2;
    matrixEntry2 = temp;

    return;
}
