#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include "deck.h"
#include "card.h"

using std::ostream;
using std::string;

class Player
{
public:
    static const int Max_Cards = 3; // # of cards a player can have in a hand

    // constructor - player's name defaults to "unknown" if not supplied
	Player(string name="unknown");

    // Simulates player removing one card from hand and playing it - returns the card
    // You may use whatever strategy you'd like here: choose a card randomly, 
	// choose the card with the largest value, choose the first card, or other approaches
	Card playCard();

    // draw top card from the deck
	void drawCard(Deck& dk);

    // add the point value of the card to the player's score
	void addScore(Card acard);

    // return the score the player has earned so far
	int getScore() const;

    // return the name of the player
    string getName() const; 

    // return true if the player's hand is out of cards
	bool emptyHand() const;

    // overload the << operator to display all cards in player's hand
    friend std::ostream& operator << (std::ostream&, const Player&);

private:
	string  name;					// the player's name
	int     score;					// the player's score
	Card    hand[Max_Cards];		// array holding the cards currently in the player's hand
	bool    hasPlayed[Max_Cards];	// hasPlayed[i] indicates that hand[i] (i.e., ith card in player's hand)
									// has been played
};

#endif

