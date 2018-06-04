#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//Declare global constant.
const int SIZE = 100;

//Declare functions.
void ArrayGen(ifstream &file, string arr[], int &aSize); //1
void DisplayTitles(const string arr[], int aSize);       //2
void AppendBook(string arr[], int &aSize);               //3

//Main
int main()
{
    //Declare variables.
    int       count;
    string    bookTitle[SIZE];
    ifstream  myFile;

    //Open file.
    myFile.open("booktitles.dat");

    //Calling functions.
    ArrayGen(myFile, bookTitle, count);
    DisplayTitles(bookTitle, count);
    AppendBook(bookTitle, count);

    //Close file.
    myFile.close();

    return 0;
}

//1: Generates array which comprises the data in the input file.
void ArrayGen(ifstream &file, string arr[], int &aSize)
{
    //Declare local variable.
    string line;

    //Generate array.
    for (aSize = 0; (aSize < SIZE) && getline(file, line); aSize++)
        arr[aSize] = line;

    return;
}


//2: Displays list of book titles.
void DisplayTitles(const string arr[], int aSize)
{
    //Display contents of array for the user.
    cout << "Books in the collection:\n" << endl;
    for (int i = 0; i < aSize; i++)
        cout << i + 1 << " : " << arr[i] << endl;
    cout << endl;
    return;
}


/*
3: Prompts user to enter new book title and location in the array in which they
would like to place said book title, then updates array to satisfy the user.
*/
void AppendBook(string arr[], int &aSize)
{
    //Declare local variables.
    string newBookTitle,
           scapeGoat;    /*
                         The scapeGoat variable's use is to buffer the
                         whitespace characters left behind after cin collects
                         an integer.
                         */
    int    location;
    bool   pass;

    /*
    This is where the magic happens. The user will be prompted to enter a book
    title that they would like to add to the current running list of books. If
    the book already exists, in the list, the user will be alerted and prompted
    to enter another book. If the user happens to enter an invalid list position
    they will be notified and the prompt will reset. If the user enters a new
    book title and a valid list position, the list will be updated with the
    input book title inserted into the desired position.

    ---------------------------------tl;dr-------------------------------------
    User will be asked to enter a new book title and location, if both are
    determined to be acceptable inputs, the array will be updated.
    */
    while (true)
    {
        pass = true;
        cout << "Please enter the title to add to the collection: (Press "
                    << "[return] to escape.) ";
            getline(cin, newBookTitle);

            //If user presses [return], the prompt will end.
            if (newBookTitle == "")
                break;

            //Compares input title to every other title in the list.
            for (int i = 0; i < aSize; i++)
            {
                if (newBookTitle == arr[i])
                {
                    cout << "The book is already in the collection. Insertion "
                         << "not carried out." << endl << endl;
                    pass = false;
                }
            }

            /*
            If input title was not already in the list, the user will be asked
            where they would like to store the new title.
            */
            if (pass == true)
            {
                //Ask user where they would like to place new title.
                cout << "Please enter the location to add the new book: ";
                cin  >> location;
                getline(cin, scapeGoat);  //scapeGoat putting in work.
                cout << endl;

                //Updates array with new title in dsired position.
                if (((location - 1) <= aSize) && ((location - 1) >= 0) && (aSize
                    < SIZE))
                {
                    for (int i = aSize; i > location - 1; i--)
                        arr[i] = arr[i - 1];

                    arr[location - 1] = newBookTitle;

                    aSize++;
                }

                //Lets user know if their location input was invalid.
                else
                {
                    cout << "That is an invalid location." << endl;
                    continue;
                }

                //Updated list is displayed.
                cout << "After insertion ..." << endl;
                DisplayTitles(arr, aSize);
            }
    }
   return;
}
