#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

//Create type.
struct CardType
{
    string suit;
    int    value,
           points;
};

//Declare functions.
void FormCards(CardType arr[]);
void DisplayCards(CardType arr[]);

//Main
int main()
{
    //Declare variable.
    CardType deck[52];

    //Call functions.
    FormCards(deck);
    DisplayCards(deck);

    return 0;
}

//1: Forms deck of cards.
void FormCards(CardType arr[])
{
    //Declare locale variables.
    int count = 0,
        node = 0;

    //Generate deck.
    for (int i = 0; i < 4; i++, node++)
    {
        for (int j = 0; j < 13; j++)
        {
            arr[count].value = j + 1;
            if (node == 0)
            {
                arr[count].suit = "Diamond";
                if (j == 10)
                    arr[count].points = -100;
                else
                    arr[count].points = 0;
            }
            else if (node == 1)
            {
                arr[count].suit = "Club";
                arr[count].points = 0;
            }
            else if (node == 2)
            {
                arr[count].suit = "Heart";
                if (j < 9)
                    arr[count].points = 5;
                else
                    arr[count].points = 10;
            }
            else
            {
                arr[count].suit = "Spade";
                if (j == 11)
                    arr[count].points = 100;
                else
                    arr[count].points = 0;
            }
            count++;
        }
    }

    return;
}

//2: Display cards, value, and points for user.
void DisplayCards(CardType arr[])
{
    //Declar local variable.
    string displayCharacter;

    //Display Deck of cards.
    cout << "Here is the deck of cards:" << endl << endl << setw(6) << "SUIT"
         << setw(16) << "VALUE" << setw(14) << "POINTS" << endl;
    for (int i = 0; i < 52; i++)
    {
        if (arr[i].value > 1 && arr[i].value < 10)
            displayCharacter = arr[i].value + '0';
        else if (arr[i].value == 1)
            displayCharacter = 'A';
        else if (arr[i].value == 10)
            displayCharacter = "10";
        else if (arr[i].value == 11)
            displayCharacter = 'J';
        else if (arr[i].value == 12)
            displayCharacter = 'Q';
        else
            displayCharacter = 'K';
        if (arr[i].suit == "Diamond")
        {
            cout << setw(8) << arr[i].suit << setw(12) << displayCharacter
                 << setw(14) << arr[i].points << endl;
        }
        else
        {
            cout << "  " << setw(5) << left << arr[i].suit << setw(13) << right
                 << displayCharacter << setw(14) << arr[i].points << endl;
        }
    }
    return;
}
