////Author:      Ryan Florida
////Project:     OLA3
////Due Date:    February 22, 2017
////Description: This program will implement three classes in order to play a
////             card game with a computer opponent. The rules of the card game
////             are as follows: The two players will start off by drawing two
////             cards from a shuffled deck. The two players will then start
////             the game by simultaneously playing a card from their
////             respective hands; whichever player played the card with the
////             higher point value will be deemed the winner of the hand and
////             the point values of the cards will be added to the total of
////             the winning player. If the hand results in a draw, each player
////             will have the points of their own cards added to their total
////             scores. The game will end when both players have empty hands.
////             The winner will be the player with the most points.



#include <iostream>
#include <iomanip>
#include "Player.h"

using std::cout;
using std::setw;

//1: This function is responsible for making sure each round of the game is
//   played correctly.
void PlayGame(Player& player1, Player& player2, Deck& newDeck);

//0: Main
int main()
{
    //Variable declarations.
    Player player1("Ryan"),
           player2("Computer");
    Deck   newDeck;

    //Shuffle deck before game begins..
    newDeck.Shuffle();

    //Play game until deck runs out of cards.
    do{
        PlayGame(player1, player2, newDeck);
        player1.drawCard(newDeck);
        player2.drawCard(newDeck);
    }while(!newDeck.isEmpty());

    //Play game until players run out of cards in their hands.
    do{
        PlayGame(player1, player2, newDeck);
    }while(!player1.emptyHand() && !player2.emptyHand());

    //Display the winner of the game.
    cout << "\n\n";
    if(player1.total() > player2.total())
        cout << player1.getName() << " wins with a score of " << player1.total()
             << '\n';
    else if(player2.total() > player1.total())
        cout << player2.getName() << " wins with a score of " << player2.total()
             << '\n';
    else
        cout << "The game resulted in a tie.\n";

    return 0;
}

//1: This function is responsible for making sure each round of the game is
//   played correctly.
void PlayGame(Player& player1, Player& player2, Deck& newDeck)
{
    //Local function declaration.
    static int roundNumber = 1;
    Card   p1Card,
           p2Card;

    //During the first round of the game, the players are dealt three cards.
    if(roundNumber == 1)
        for(int i = 0; i < 3; i++)
        {
            player1.drawCard(newDeck);
            player2.drawCard(newDeck);
        }

    //Display pre-round statistics.
    cout << "\n********************** Hand " << roundNumber << " *************"
         << "*********\n" << player1.getName() << "'s hand: ";
    player1.displayHand();
    cout << " with score " << player1.total() << "\n" << player2.getName()
         << "'s hand: ";
    player2.displayHand();
    cout << " with score " << player2.total() << "\n\n";

    //Players play their cards.
    p1Card = player1.playCard();
    p2Card = player2.playCard();

    cout << player1.getName() << " played card: " << p1Card << " --- "
         << player2.getName() << " played card: " << p2Card << "\n\n";

    //Determine winner of round based upon point value of cards played.
    if(p1Card > p2Card)
    {
        player1.addScore(p1Card);
        player1.addScore(p2Card);
        cout << player1.getName() << " takes this hand.\n";
    }
    else if(p1Card < p2Card)
    {
        player2.addScore(p1Card);
        player2.addScore(p2Card);
        cout << player2.getName() << " takes this hand.\n";
    }
    else
    {
        player1.addScore(p1Card);
        player2.addScore(p2Card);
        cout << "The result was a draw.\n";
    }

    //Display post-round statistics.
    cout << player1.getName() << "'s hand: ";
    player1.displayHand();
    cout << " With a score of: " << player1.total();
    cout << '\n' << player2.getName() << "'s hand: ";
    player2.displayHand();
    cout << " With a score of: " << player2.total();
    cout << '\n';

    //Increment to keep track of round number.
    roundNumber++;

    return;
}
