/*
   Author:      Ryan Florida
   Professor:   Dr. Pettey
   Program:     Lab 4
   Description: This program emulates a finite state machine that recognizes
                strings represented by the following regular expression:

                    a*b*ab
                *To run, make sure to use a text file.
*/
#include <iostream>

using namespace std;

// States.
const int S0                = 0;
const int S1                = 1;
const int S2                = 2;
const int S3                = 3;
const int S4                = 4;
const int S5                = 5;
const int S6                = 6;

// Output.
const int OUTPUT            = 3;

// Lookup Table Dimensions.
const int NUMBER_OF_STATES  = 7;
const int NUMBER_OF_COLUMNS = 4;

//0: Main.
int main()
{
    // Variable declaration and initialization.
    int  currentState = S0;    // Initialize current state to S0.
    char inputCharacter;       // Stores the input character.

/*  transitionTable[State][Input] -> next state.
    transitionTable[State][Output] -> outputs 0 if not recognizing state,
    outputs 1 if recognizing state.                                          */
    int transitionTable[NUMBER_OF_STATES][NUMBER_OF_COLUMNS] =
    {
/*                      Inputs
                       a      b
           States     New States    Outputs
          __________________________________
                                                                             */
          { S0,       S1,     S3,      0, },
          { S1,       S1,     S2,      0, },
          { S2,       S4,     S3,      1, },
          { S3,       S4,     S3,      0, },
          { S4,       S6,     S5,      0, },
          { S5,       S6,     S6,      1, },
          { S6,       S6,     S6,      0, }
    };

    // Outputs a zero for when the machine turns on.
    cout << transitionTable[currentState][OUTPUT];

    // States transition to different states depending on input character.
    while(cin.peek() != '\n')
    {
        // Get a character to input into the finite state machine.
        inputCharacter = cin.get();

        // Update the current state of the machine based on the input character.
        currentState = transitionTable[currentState][inputCharacter - 'a' + 1];

        // Output whether the current state is a recognizing state or not.
        cout << transitionTable[currentState][OUTPUT];
    }

    return 0;

}
