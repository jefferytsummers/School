#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//Declar functions.
int  LinearSearch(const string a[], int aSize, string toFind);
void SelectionSort(string arr[], int n);

//Main
int main()
{
    //Declare variables.
    const int SIZE = 100;
    int       loc,
              count;
    string    line,
              entry,
              bookTitle[SIZE];
    ifstream  myFile;

    //Open "booktitles.dat" file.
    myFile.open("booktitles.dat");

    //Convert list of books to an array.
//    for (count = 0; (count < SIZE) && getline(myFile, line); count++)
//    {
//        bookTitle[count] = line;
//    }

    count = 0;
    while ((count < SIZE) && getline(myFile, bookTitle[count]))
        count++;

    //Sort the array generated above in ascending alphabetical order.
    SelectionSort(bookTitle, count);

    //Display the books in a numbered, ordered list for the user.
    cout << "Books in the collection:\n" << endl;
    for (int i = 0; i < count; i++)
        cout << i + 1 << " : "<< bookTitle[i] << endl;

    //Formatting.
    cout << endl;

    /*
    Prompts user to enter a book they would like to search for. Then returns
    the position in the list the desired book is at, if it is there at all.
    Press [return] to exit sequence.
    */
    while (true)
    {
        cout << "Enter a book title to search for: (Press [return] to escape) ";
        getline(cin, entry);
        if (entry == "")
            break;
        loc = LinearSearch(bookTitle, count, entry);
        if (loc > 0)
            cout << "The book is at location " << loc << '.' << endl << endl;
        else if (loc < 0)
            cout << "The book was not found. " << endl << endl;
    }

    myFile.close();

    return 0;
}


//Search through list for desired book, return position of book in list.
int LinearSearch(const string a[], int aSize, string toFind)
{
    for (int i = 0; i < aSize; i++)
    {
        if (a[i] == toFind)
            return i + 1;
    }
    return -1;
}


//Sort array in ascending alphabetical order.
void SelectionSort(string arr[], int n)
{
    int    i,
           j,
           minIndex;
    string tmp;

    for (i = 0; i < (n - 1); i++)
    {
        minIndex = i;
        for (j = (i + 1); j < n; j++)
        {
            if (arr[j] < arr[minIndex])
                minIndex = j;
        }
        if (minIndex != i)
        {
            tmp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = tmp;
        }
    }
    return;
}
