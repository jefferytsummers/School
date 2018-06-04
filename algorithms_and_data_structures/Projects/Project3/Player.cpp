////Author:      Ryan Florida
////Project:     OLA3
////Due Date:    February 22, 2017
////Description: This is the implementation file for the player class.

#include "Player.h"

using std::cout;

//Constructor that allows for custom player names.
Player::Player(string newName)
{
    for(int i = 0; i < Max_Cards; i++)
        played[i] = true;
    name  = newName;
    score = 0;
}

//The player will play the highest value card in their hand.
Card Player::playCard()
{
    //Local variable declaration.
    int maxIndex;

    //Search for index of first card that has not yet been played.
    for(int i = 0; i < Max_Cards; i++)
        if(!played[i])
        {
            maxIndex = i;
            break;
        }

    //Search for index of card with highest point value.
    for(int i = 0; i < Max_Cards; i++)
        if((played[i] == false) && (hand[i].getPointValue() >
                    hand[maxIndex].getPointValue()))
            maxIndex = i;

    //Store card with highest point value.
    Card cd = hand[maxIndex];

    //Mark chosen card as played.
    played[maxIndex] = true;

    return cd;
}

//Player will draw card from the deck.
void Player::drawCard(Deck& dk)
{
    //Look for card that has been played. Once this card has been found, the
    //player will receive a new card and the element of the played array
    //corresponding to the new card will be set to false.
    for(int i = 0; i < Max_Cards; i++)
    {
        if(played[i])
        {
            hand[i] = dk.dealCard();
            played[i] = false;
            return;
        }
    }

    return;
}

//Increase the player's score.
void Player::addScore(Card acard)
{
    //Add value of card to the total running score.
    score += acard.getPointValue();
    return;
}

//Return the total player score to the caller.
int Player::total() const
{
    return score;
}

//Return the player name to the caller.
string Player::getName() const
{
    return name;
}

//Returns true if player's hand is empty, false otherwise.
bool Player::emptyHand() const
{
    for(int i = 0; i < Max_Cards; i++)
    {
        if(played[i] == false)
            return false;
    }

    return true;
}

//Display the player's current hand for the caller.
void Player::displayHand() const
{
    for(int i = 0; i < Max_Cards; i++)
    {
        //Displays only those cards in the players hand that have not yet been
        //played.
        if(!played[i])
        {
            switch(hand[i].getFaceValue())
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
                    cout << hand[i].getFaceValue();
            }

            hand[i].displaySuite();
            cout << '[' << hand[i].getPointValue() << "] ";
        }

        //Display blank slot if card has been played to indicate the card is no
        //longer in the player's hand.
        else
            cout << "_____ ";
    }

    return;
}

//Overload << operator.
ostream& operator << (ostream& os, const Player& player)
{
    os << player.name << '\n' << player.hand[0] << " " << player.hand[1]
       << " " << player.hand[2] << '\n';

    return os;
}
