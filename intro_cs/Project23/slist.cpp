// Implementation file array-based list (“list.cpp”)

#include "slist.h"
#include  <iostream>
using namespace std;

SortedList::SortedList()
// Constructor
// Post: length == 0
{
    length     = 0;
    currentPos = 0;
}

// Copy constructor.
SortedList::SortedList(const SortedList& original)
{
    length = original.length;
    for(int i = 0; i < length; i++)
        data[i] = original.data[i];
}

bool SortedList::IsEmpty()  const
// Post: Return value is true if length is equal
//  to zero and false otherwise
{
      return (length == 0);
}

bool SortedList::IsFull()  const
// Post: Return value is true if length is equal
//  to MAX_LENGTH and false otherwise
{
      return (length == MAX_LENGTH);
}

int SortedList::Length()  const
// Post: Return value is length
{
      return  length;
}

void SortedList::Insert(/* in */  ItemType  item)
// Pre: length < MAX_LENGTH && item is assigned
// Post: data[length@entry] == item &&
//       length == length@entry + 1
{
    int index;

    index = length - 1;

    while (index >= 0 && item <= data[index])
    {
        data[index + 1] = data[index];
        index--;
    }

    if (index < 0)
        data[0] = item;
    else
        data[index + 1] = item;

    length++;
}


bool SortedList::IsPresent( /* in */ ItemType item) const
// Searches the list for item, reporting  whether found
// Post: Function value is true, if item is in
//   data[0 . . length-1] and is false otherwise
{
    int index  =  0;
    while (index < length && item != data[index])
          index++;

    return  (index < length);
}

void SortedList::Delete( /* in */  ItemType  item)
// Pre: length > 0  &&  item is assigned
// Post: IF item is in data array at entry
//      First occurrence of item is no longer
//   in array
//         && length == length@entry - 1
{
    bool found;
    int position,
        index;

    BinSearch(item, found, position);
    if (found)
    {
        for (index = position; index < length + 1; index++)
            data[index] = data[index + 1];

        length--;
    }
}

void SortedList::BinSearch(ItemType item, bool& found, int& position) const
{
    int middle,
        first = 0,
        last = length - 1;
    found = false;

    while (last >= first && !found)
    {
        middle = (first + last)/2;

        if (!(item > data[middle]) || (item != data[middle]))
            last = middle - 1;
        else if (item > data[middle])
            first = middle + 1;
        else
            found = true;
    }
    if (found)
        position = middle;
}


void SortedList::Reset()
// Post: currentPos has been initialized.
{
    currentPos = 0;
}

ItemType SortedList::GetNextItem()
// Pre: No transformer has been executed since last call
// Post:Return value is currentPos@entry
//   Current position has been updated
//   If last item returned, next call returns first item
{
    ItemType item;
    item = data[currentPos];
    if (currentPos == length - 1)
        currentPos = 0;
    else
        currentPos++;
    return item;
}

void  SortedList::SelSort()
// Sorts list into ascending order
{
    ItemType temp;
    int sIndx;
    int minIndx; // Index of minimum so far

    for (int passCount = 0; passCount < length - 1; passCount++) {

       minIndx = passCount;

       for (sIndx = passCount + 1; sIndx < length; sIndx++)
       {
           if (data[sIndx] < data[minIndx])
               minIndx = sIndx;
       }

       if (minIndx != passCount)
       {
           temp = data[minIndx];
           data[minIndx] = data[passCount];
           data[passCount] = temp;
       }
   }
}

std::ostream& operator<<(std::ostream& output, const ItemType& book)
{
  //  BookType book;
//    for (int i = 0; i < sL.length; i++)
 //   {
 //       book = sL.data[i];
        output << "Title: " << book.title << endl << "Author: " << book.author
               << endl << "Publication Year: " << book.publicationYear << endl
               << "Date borrowed: " << book.dateBorrowed.month << "/"
               << book.dateBorrowed.day << "/" << book.dateBorrowed.year << endl
               << endl;
  //  }

    return output;
}

void SortedList::Print() const
// display the list of items
{
    cout << "The list of items are: " << endl;
    for (int i = 0; i < length; i++)
        cout << data[i] << endl;
    cout << endl;
}

SortedList::~SortedList()
{
}
