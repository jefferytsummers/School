////Author:      Ryan Florida
////Project:     OLA3
////Due Date:    February 22, 2017
////Description: This is the implementation file for the card class.

#include "Card.h"
#include <iomanip>

using std::cout;
using std::left;
using std::setw;

//Default constructor definition.
Card::Card()
    :type(clubs), faceValue(0), pointValue(0)
{}

//Constructor that allows card customization.
Card::Card(int faceVal, suite selectedType)
{
    faceValue = faceVal;
    type      = selectedType;

    if(faceValue < 11)
        pointValue = faceValue;
    else if(faceValue >= 11 && faceValue < 14)
        pointValue = 10;
    else
        pointValue = 15;
}

//Overload << operator.
ostream& operator << (ostream& os, const Card& cd)
{
    switch(cd.faceValue)
    {
        case 11:
            os << 'J';
            break;
        case 12:
            os << 'Q';
            break;
        case 13:
            os << 'K';
            break;
        case 14:
            os << 'A';
            break;
        default:
            os << cd.faceValue;
    }

    cd.displaySuite();
    os << '[' << cd.pointValue << "] ";

    return os;
}

//Overload < operator.
bool Card::operator < (const Card& cd) const
{
    return (pointValue < cd.pointValue);
}

//Overload > operator.
bool Card::operator > (const Card& cd) const
{
    return (pointValue > cd.pointValue);
}

//Overload == operator.
bool Card::operator == (const Card& cd) const
{
    return (pointValue == cd.pointValue);
}

//Returns point value of card to caller.
int Card::getPointValue() const
{
    return pointValue;
}

//Returns face value of card to caller.
int Card::getFaceValue() const
{
    return faceValue;
}

//Displays suit of card.
void Card::displaySuite() const
{
    if(type == clubs)
        cout << ((char) 0x05);
    else if(type == spades)
        cout << ((char) 0x06);
    else if(type == hearts)
        cout << ((char) 0x03);
    else
        cout << ((char) 0x04);
    return;
}
