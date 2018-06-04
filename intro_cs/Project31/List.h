// Specification file array-based list (“list.h”)
#ifndef List_H
#define List_H

#include <iostream>
#include <string>

//Forward declaration of struct.
struct SongType;

//Declare global constant.
const   int      MAX_LENGTH = 500;

//Create alias for struct.
typedef SongType ListItemType;

//Create struct.
struct SongType
{
    //Struct fields.
    std::string artist,
                title;
    int         rank,
                year;

    //Overload != operator.
    bool operator !=(SongType rhs)
    {
        return (!((rhs.title == title) && (rhs.artist == artist)
		            && (rhs.rank == rank) && (rhs.year == year)));
    }

    //Overload < operator.
    bool operator <(SongType rhs)
    {
        return (artist < rhs.artist);
    }
};

//Overload << operator.
std::ostream& operator<<(std::ostream&, const ListItemType&);

class List           // Declares a class data type
{

public:               // Public member functions

    List();           // constructor

    List(const List&);      // Copy constructor

    bool IsEmpty() const;
    // Post: Return value is true if length is equal
    //  to zero and false otherwise

    bool IsFull() const;
    // Post: Return value is true if length is equal
    //  to MAX_LENGTH and false otherwise

    int Length() const; // Returns length of list
    // Post: Return value is length

    void Insert(ListItemType item);
    // Pre: length < MAX_LENGTH && item is assigned
    // Post: data[length@entry] == item &&
    //       length == length@entry + 1

    void Delete(ListItemType item);
    // Pre: length > 0  &&  item is assigned
    // Post: IF item is in data array at entry
    //      First occurrence of item is no longer
    //   in array
    //         && length == length@entry - 1
    //      ELSE
    //       length and data array are unchanged

    bool IsPresent(ListItemType item)  const;
    // Post: currentPos has been initialized.

    void SelSort();
    // Sorts list into ascending order

    void Reset();
    // Post: currentPos has been initialized.

    ListItemType GetNextItem();
    // Pre: No transformer has been executed since last call
    // Post:Return value is currentPos@entry
    //   Current position has been updated
    //   If last item returned, next call returns first item

    //Destructor
    ~List();
private:                            // Private data members
    int          length;            // Number of values currently stored
    ListItemType data[MAX_LENGTH];  // Array that stores list entries.
    int          currentPos;        // Used in iteration
};

#endif
