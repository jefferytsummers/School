////Author:      Ryan Florida
////Program:     OLA5
////Due Date:    3/22/2017
////Description: This program illustrates the use of recursion in C++. There
////             are four functions implemented, each of which use recursion to
////             solve seemingly different problems.

#include "parameters.h"
#include <iostream>
#include <string>
#include <sstream>

using std::cout;
using std::endl;
using std::string;
using std::stringstream;
using std::getline;

//1: Computes a certain number of terms of the Fibonacci sequence, the number of
//   terms is set by the numberOfTerms parameter.
int fibonacci(int numberOfTerms);
//*****************************************************************************
//2: Computes the sum of the first n natural numbers, where n is set by the
//   parameter seedValue.
int sum(int seedValue);
//*****************************************************************************
//3: Finds the longest sequence of natural numbers in an array and returns a
//   number that is representative of the length of this sequence.
int longest(const int intArray[]);
//*****************************************************************************
//4: Finds the length of the shortest word in the input string and returns a
//   number that is representative of the length of this word.
int shortest(string inputString);

//0: Main.
int main()
{
    //Call to Fibonacci function and output the appropriate value.
    int value = fibonacci(FibVal);
    std::cout << "The " << FibVal << "th value of the Fibonacci sequence is: "
              << value << std::endl;

    //Call to sum function and output the appropriate value.
    int numSum = sum(SumVal);
    std::cout << "The sum of the first " << SumVal << " natural numbers is: "
              << numSum << std::endl;

    //Call to longest function and output the appropriate value.
    int longestSequence = longest(LongestVal);
    std::cout << "Length of the longest sequence of natural numbers in the "
              << "input array: " << longestSequence << std::endl;

    //Call to shortest function and output the appropriate value.
    int wordLength = shortest(SentenceVal);
    std::cout << "The shortest word in the input sentence has length: "
              << wordLength << std::endl;

    return 0;
}

//*****************************************************************************
//1: Compute a certain number of terms of the Fibonacci sequence, the number of
//   terms is set by the numberOfTerms parameter.
int fibonacci(int numberOfTerms)
{
    //Base case.
    if(numberOfTerms == 0)
        return 0;
    if(numberOfTerms == 1)
        return 1;

    //Recursive step.
    return (fibonacci(numberOfTerms - 2) + fibonacci(numberOfTerms - 1));
}

//*****************************************************************************
//2: Computes the sum of the first n natural numbers, where n is set by the
//   parameter seedValue.
int sum(int seedValue)
{
    //Base Case.
    if(seedValue == 1)
        return 1;

    //Recursive step.
    return(sum(seedValue - 1) + seedValue);
}

//*****************************************************************************
//3: Finds the longest sequence of natural numbers in an array and returns a
//   number that is representative of the length of this sequence.
int longest(const int intArray[])
{
    //Local variable declaration.
    int sequenceLength = 0,
        startIndex     = 0,
        longestSubSeq,
        newArray[20];
    //Static variable to keep track of the length of the current array.
    static int length = 13;

    //Base case.
    if(length == 1)
        return(intArray[0] > 0)?1:0;

    //Identify longest sequence of positive values in current array and
    //determine the starting index for the next subarray.
    for(int i = 0; i < length; i++)
        if(intArray[i] <= 0)
        {
            sequenceLength = i;
            startIndex = i + 1;
            break;
        }

    //Set length of the next subarray.
    length -= startIndex;

    //Construct next subarray.
    for(int i = 0; i < length ;++i)
        newArray[i] = intArray[startIndex + i];

    //Recursive step:

    //Set value for comparison to current longest sequence length.
    longestSubSeq = longest(newArray);
    //Determine largest sequence length.
    return(sequenceLength > longestSubSeq)?sequenceLength:longestSubSeq;
}

//*****************************************************************************
//4: Finds the length of the shortest word in the input string and returns a
//   number that is representative of the length of this word.
int shortest(std::string inputString)
{
    //Local variable declaration.
    stringstream        ss(inputString);
    string              currentWord,
                        subString;
    int                 shortestWordLength;
    //Static variable to keep track of shortest word length.
    static unsigned int currentShortestLength = 99999;

    //Considers first word in the current string.
    ss >> currentWord;

    //Base case.
    if(currentWord == "\0")
        return currentShortestLength;

    //Set shortest word length to the length of the current word if the length
    //of the current word happens to be shorter than the current shortest word
    //length.
    if(currentWord.size() < currentShortestLength)
        currentShortestLength = currentWord.size();

    //Form substring of the current string to feed back into the shortest
    //function.
    getline(ss, subString);

    //Recursive step.
    shortestWordLength = shortest(subString);
    return shortestWordLength;
}
