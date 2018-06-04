////Author:      Ryan Florida
////Project:     OLA4
////Due Date:    March 20, 2017
////Description: This program will demonstrate one of the many instances of
////             polymorphism in C++. This is accomplished by working with two
////             derived classes, Movie and Book, of the base class, StoreItem,
////             in which we will help a movie store keep control over their
////             inventory with relative ease.

#include "Book.h"
#include "Movie.h"
#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <typeinfo>
#include <cassert>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::list;
using std::ifstream;
using std::getline;
using std::stringstream;

//Aliasing for readability.
typedef StoreItem* store;
typedef list<store>::iterator iter;

//Functions declarations.
//*****************************************************************************
//1: This function loads the store inventory from an input file and initializes
//   the inventory list, which is passed into the function by reference.
void LoadInventory(list<store> &inventory);
//*****************************************************************************
//2: This function displays an interactive menu for the user to perform certain
//   actions, such as: 1) inquiring about a movie ; 2) Inquiring about a book;
//   3) Listing the store inventory; 4) Returning a movie/book to the store;
//   5) Checking out a movie/book form the store; 6) Qutting the menu.
void DisplayMenu(list<store> &inventory);
//*****************************************************************************
//1.1: Tests the relationship between two list items.
bool CompareItems(store inventoryItem1, store inventoryItem2);
//*****************************************************************************
//2.1: (Overloaded function 1/2) This function searches for a movie, by title,
//     in the inventory.
void SearchFor(string title, list<store> &inventory);
//*****************************************************************************
//2.2: (Overloaded function 2/2) This function searches for a book, by author,
//     in the inventory.
void SearchFor(list<store> &inventory, string author);
//*****************************************************************************
//2.3: This function simply lists the contents of the inventory.
void ListInventory(list<store> &inventory);
//*****************************************************************************
//2.4: This function returns a movie/book to the store, by inputting the
//     barcode of said item.
void Checkout(string barcode, list<store> &inventory);
//*****************************************************************************
//2.5: This functions checks out a movie/book from the store, by inputting the
//     barcode of said item.
void Return(string barcode, list<store> &inventory);

//*****************************************************************************
//0: Main
int main()
{
    //Declare list to maintain store inventory.
    list<store> inventory;

    //Function calls.
    LoadInventory(inventory);
    DisplayMenu(inventory);

    return 0;
}

//*****************************************************************************
//1: This function loads the store inventory from an input file and initializes
//   the inventory list, which is passed into the function by reference.
void LoadInventory(list<store> &inventory)
{
    //Local variable declarations.
    Movie  movie;
    Book   book;
    string info;
    store  storePtr;

    //Open and assert input file.
    ifstream inFile;
    inFile.open("inventory.txt");
    assert(inFile);

    //Determine which line of the input file will be used for creating a movie/
    //book object.
    while(getline(inFile, info))
    {
        //Create movie object from input string.
        if(info[1] == 'M')
        {
            storePtr = movie.createFromString(info);
            inventory.push_back(storePtr);
        }
        //Create book object from input string.
        else
        {
            storePtr = book.createFromString(info);
            inventory.push_back(storePtr);
        }
    }

    //Sort the list based on CompareItems (1.1) function.
    inventory.sort(CompareItems);

    //Close input file.
    inFile.close();

    return;
}

//*****************************************************************************
//2: This function displays an interactive menu for the user to perform certain
//   actions, such as: 1) inquiring about a movie ; 2) Inquiring about a book;
//   3) Listing the store inventory; 4) Returning a movie/book to the store;
//   5) Checking out a movie/book form the store; 6) Qutting the menu.
void DisplayMenu(list<store> &inventory)
{
    //Local variable declarations.
    char   command;
    string title,
           barcode;

    //Display interactive menu for user.
    while(true)
    {
        cout << "******************* MiniMovie Store *******************" << endl
             << "* Command                        Description          *" << endl
             << "*    M                     Inquire a movie by title   *" << endl
             << "*    B                     Inquire a book by author   *" << endl
             << "*    L                     List inventory             *" << endl
             << "*    R                     Return one movie           *" << endl
             << "*    C                     Check out                  *" << endl
             << "*    Q                     Quit the main menu         *" << endl
             << "*******************************************************" << endl
             << "Please enter your command: ";
        cin  >> command;
        cin.ignore();

        //Decide appropriate action to take based on input.
        switch(command)
        {
            case 'm':
            case 'M':
                cout << "Please enter the movie title: ";
                getline(cin, title);
                SearchFor(title, inventory);
                break;

            case 'b':
            case 'B':
                cout << "Please enter the book author: ";
                getline(cin, title);
                SearchFor(inventory, title);
                break;

            case 'r':
            case 'R':
                cout << "Please enter the item barcode: ";
                cin  >> barcode;
                cin.ignore();
                Return(barcode, inventory);
                break;

            case 'l':
            case 'L':
                ListInventory(inventory);
                break;

            case 'c':
            case 'C':
                cout << "Please enter the item barcode: ";
                cin  >> barcode;
                cin.ignore();
                Checkout(barcode, inventory);
                break;

            case 'q':
            case 'Q':
                return;

            default:
                cout << "Invalid input" << endl << endl;
        }
    }
    return;
}

//*****************************************************************************
//1.1: Tests a pre-determined relationship between two list items.
bool CompareItems(store inventoryItem1, store inventoryItem2)
{
    return(*inventoryItem1 < *inventoryItem2);
}

//*****************************************************************************
//2.1: (Overloaded function 1/2) This function searches for a movie, by title,
//     in the inventory.
void SearchFor(string title, list<store> &inventory)
{
    //Local variable declaration.
    Movie movie;

    //Searches for appropriate movie title, then prints the corresponding
    //object.
    for(iter it = inventory.begin(); it != inventory.end(); ++it)
    {
        Movie* moviePtr = (Movie*)(*it);
        if(typeid(*(*it)) == typeid(movie) && moviePtr->getTitle() == title)
        {
            moviePtr->printItem();
            return;
        }
    }

    //If the movie title is not in the inventory, the user is notified.
    cout << "There is no movie with the titled " << title << " in this store." 
         << endl;

    return;
}

//*****************************************************************************
//2.2: (Overloaded function 2/2) This function searches for a book, by author,
//     in the inventory.
void SearchFor(list<store> &inventory, string author)
{
    //Local variable declaration.
    Book book;

    //Searches for appropriate book author(s), then prints the corresponding
    //object.
    for(iter it = inventory.begin(); it != inventory.end(); ++it)
    {
        Book* bookPtr = (Book*)(*it);
        if(typeid(*(*it)) == typeid(book))
        {
            string authorString = bookPtr->getAuthor();
            string::size_type position = authorString.find(author, 0);

            if(position != string::npos)
            {
                bookPtr->printItem();
                return;
            }
        }
    }

    //Alert user if they typed in an invalid author.
    cout << "There is no book authored by " << author << " in this store." 
         << endl;

    return;
}

//*****************************************************************************
//2.3: This function simply lists the contents of the inventory.
void ListInventory(list<store> &inventory)
{
    for(iter it=inventory.begin(); it != inventory.end(); ++it)
        (*it)->printItem();

    return;
}

//*****************************************************************************
//2.4: This function returns a movie/book to the store, by inputting the
//     barcode of said item.
void Return(string barcode, list<store> &inventory)
{
    //Search through list to find the item with matching barcode to that which
    //was entered, then increments the number of copies of that item.
    for(iter it = inventory.begin(); it != inventory.end(); ++it)
    {
         if((*it)->getBarcode() == barcode)
        {
            (*it)->increaseCopy();
                cout << "One more copy with barcode " << barcode << " has been"
                     << " added." << endl;
            return;
        }
    }

    //Notifies user if they entered an invalid barcode.
    cout << barcode << " is not a valid barcode." << endl;

    return;
}

//*****************************************************************************
//2.5: This functions checks out a movie/book from the store, by inputting the
//     barcode of said item.
void Checkout(string barcode, list<store> &inventory)
{    
    //Search through list to find the item with matching barcode to that which
    //was entered. If the item is located and the number of copies of that item
    //is greater than zero, the user will be able to check-out the item. If the
    //item is located and the number of copies of that item is equal to zero,
    //then the user will be informed and the demand for the item will increase.
    for(iter it = inventory.begin(); it != inventory.end(); ++it)
    {
        if(((*it)->getBarcode() == barcode) && ((*it)->getCopy() > 0))
        {
            (*it)->decreaseCopy();
            (*it)->decreaseDemand();
            cout << "The item with barcode " << barcode << " has been checked"
                 << " out successfully!" << endl;
            return;
        }

        else if((*it)->getBarcode() == barcode && (*it)->getCopy() == 0)
        {
            (*it)->increaseDemand();
            cout << "The item with barcode " << barcode << " is currently out "
                 << "of stock." << endl;
            return;
        }
    }

    //Let user know if they entered and invalid barcode.
    cout << barcode << " is not a valid barcode." << endl;

    return;
}