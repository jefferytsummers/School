#include <iostream>
#include "slist.h"
#include <fstream>
#include <string>

using namespace std;

int main()
{
    //Declare variables and objects.
    string     author;
    int        size = 0;
    BookType   aBook,
               book;
    ifstream   myIn;
    SortedList list;

    //Open data file "books.dat".
    myIn.open("books.dat");

    //Read contents of file into list object.
    while (size < MAX_LENGTH && getline(myIn, aBook.title))
    {
        getline(myIn, aBook.author);
        myIn >> aBook.publicationYear;
        myIn >> aBook.dateBorrowed.month;
        myIn >> aBook.dateBorrowed.day;
        myIn >> aBook.dateBorrowed.year;
        myIn.ignore(100, '\n');

        list.Insert(aBook);
        size++;
    }

    //Reset list for future iteration.
    list.Reset();

    //Sort books by date published.
    list.SelSort();

    //Reset list for future iteration.
    list.Reset();

    //Print list for user..
    cout << "The list of books are:" << endl << endl;
    for (int i = 0; i < list.Length(); i++)
        cout << list.GetNextItem();

    //Prompt user to enter author name for search.
    cout << "Please enter the name of the author: ";
    getline(cin, author);
    cout << endl << "The list of books are:" << endl << endl;

    //Reset list for future iteration.
    list.Reset();

    //Search for, and display, all books by the requested author.
    for (int i = 0; i < list.Length(); i++)
    {
        book = list.GetNextItem();
        if (book.author == author)
            cout << book;
    }

    return 0;
}
