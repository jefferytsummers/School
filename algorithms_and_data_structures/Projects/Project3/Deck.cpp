////Author:      Ryan Florida
////Project:     OLA3
////Due Date:    February 22, 2017
////Description: This is the implementation file for the Deck class.

#include "Deck.h"
#include <ctime>
#include <cstdlib>
#include <iomanip>

using std::cout;
using std::setw;
using std::left;

//Constructor.
Deck::Deck()
    :topCard(0)
{
    //Initialize entire deck.
    for(int i = 0; i < 13; ++i)
    {
        theDeck[i]      = *(new Card(i + 2, clubs));
        theDeck[i + 13] = *(new Card(i + 2, hearts));
        theDeck[i + 26] = *(new Card(i + 2, diamonds));
        theDeck[i + 39] = *(new Card(i + 2, spades));
    }
}

//Remove the top card from the deck and return it.
Card Deck::dealCard()
{
    int currentTop = topCard++;

    return theDeck[currentTop];
}

//Shuffle the cards in the deck.
void Deck::Shuffle()
{
    //Output the default deck configuration.
    cout << "The original deck has the following cards: \n";
    for(int i = 0; i < Card_Num; i++)
    {
        if(i != 0 && i%13 == 0)
            cout << '\n';

        switch(theDeck[i].getFaceValue())
        {
            case 11:
                cout << 'J';
                break;
            case 12:
                cout << 'Q';
                break;
            case 13:
                cout << 'K';
                break;
            case 14:
                cout << 'A';
                break;
            default:
                cout << theDeck[i].getFaceValue();
        }

        theDeck[i].displaySuite();
        cout << '[' << theDeck[i].getPointValue() << ']' << left << setw(3)
             << ' ';
    }

    //Shuffle based on random seed value.
    srand((unsigned)time(0));

    Card temp;
    int randomIndex1,
        randomIndex2,
        randomNumber = rand()%10000 + 1000000;

    //Perform a healthy shuffle.
    for(int i = 0; i < randomNumber; i++)
    {
        randomIndex1 = rand()%52;
        do
        {
            randomIndex2 = rand()%52;
        }while(randomIndex2 == randomIndex1);

        temp                  = theDeck[randomIndex1];
        theDeck[randomIndex1] = theDeck[randomIndex2];
        theDeck[randomIndex2] = temp;
    }

    //Display the newly shuffled deck.
    cout << "\n\nThe shuffled deck has the following cards: \n";
    for(int i = 0; i < Card_Num; i++)
    {
        if(i != 0 && i%13 == 0)
            cout << '\n';

        switch(theDeck[i].getFaceValue())
        {
            case 11:
                cout << 'J';
                break;
            case 12:
                cout << 'Q';
                break;
            case 13:
                cout << 'K';
                break;
            case 14:
                cout << 'A';
                break;
            default:
                cout << theDeck[i].getFaceValue();
        }

        theDeck[i].displaySuite();
        cout << '[' << theDeck[i].getPointValue() << ']' << left << setw(3)
             << ' ';
    }

    cout << '\n';

    return;
}

//Return true if the deck has run out of cards. Return false otherwise.
bool Deck::isEmpty()
{
    return (topCard == Card_Num);
}
