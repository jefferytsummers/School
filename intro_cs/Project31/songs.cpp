/*
PROGRAMMER:          Ryan Florida
Assignment:          OLA6
Class:               CSCI 2170 Section 001
Course Instructor:   Dr. Li
Due Date:            Midnight, July 26 2016.

Description:         This program displays an interactive menu for its users in
                     which they can see song statistics for the four years
                     2012-2015. The user has the ability to see all songs that
                     made the list by an artist of their choice. The user can
                     also add, and delete, songs to, and from, the list. They
                     have they option to print all songs from a certain year, if
                     that is what they wish. When the user is done with the
                     program, they can terminate it with the push of a button
                     (the button 5 to be precise).
*/

#include <iostream>
#include "List.h"
#include <fstream>
#include <cassert>
#include <iomanip>
#include <stdlib.h>
#include <string>

using namespace std;

void BuildList(List&, ifstream&);   //1
int  DisplayMenu();                 //2
void DisplaySong(List randomList);  //3
void AddSong(List& randomList);     //4
void DeleteSong(List& randomList);  //5
void DisplayYear(List randomList);  //6

//Main
int main()
{
    //Declare variables and object.
    ifstream myIn;
    List     list;
    int      selection;

    //Open and assert file "topsongs.dat".
    myIn.open("topsongs.dat");
    assert(myIn);

    //Read the info from a data file and build a list.
    BuildList(list, myIn);

   do
   {
     //Display a menu and store menu choice inside selection variable.
    selection = DisplayMenu();

    //Prompt user for name of an artist and display songs by this artist.
    if (selection == 1)
        DisplaySong(list);

    //Prompt user for the title of a song and add the song to the list.
    else if (selection == 2)
        AddSong(list);

    //Prompt user for the title of a song and delete the song.
    else if (selection == 3)
        DeleteSong(list);

    //Print the list.
    else if (selection == 4)
        DisplayYear(list);

    //Exit program.
    else if (selection == 5)
        exit(1);

   } while (true);

    return 0;
}


//1: Read information from input data file and build a list out of that info.
void BuildList(List& randomList, ifstream& file)
{
    //Declare local variables.
    ListItemType song;

    //Fill in struct fields.
    while (randomList.Length() < MAX_LENGTH && file >> song.rank)
    {
        file.ignore(100, '\n');
        getline(file, song.artist);
        getline(file, song.title);
        file >> song.year;
        file.ignore(100, '\n');

        randomList.Insert(song);
    }

    return;
}


//2: Display interactive menu for the user.
int DisplayMenu()
{
    //Declare variables.
    int choice = 0;

    //Ask user for input until they are done with the program.
    do
    {
        cout << setw(10) << " " << "Billboard Top Song (2012-2015) Management"
            << endl << endl << " Please Select from the following menu choices:"
            << setw(10) << endl << endl << "1.  Look up an artist" << endl
            << "2.  Add a song" << endl << "3.  Delete a song" << endl
            << "4.  Print" << endl << "5.  Exit" << endl;

        cin >> choice;
        cin.ignore(100, '\n');

        if ((choice <= 0) || (choice >= 6))
            cout << "Please make a valid choice." << endl << endl;

    } while ((choice <= 0) || (choice >= 6));

    //Return the value of choice to main.
    return choice;
}


//3: Prompt the user for the name of an artist and display the songs by them.
void DisplaySong(List randomList)
{
    //Declare local variables.
    std::string  artistName; //Store input artist name.
    ListItemType someSong;   //Store next item in list.
    int          flag = 0;   //Store non-zero value if artist is in list.

    //Display choice for user.
    cout << setw(10) << " " << "1.  Look up an artist" << endl << endl;

    //Reset list for traversal.
    randomList.Reset();

    //Promput user for input.
    cout << "Please enter the name of the artist: ";
    getline(cin, artistName);
    cout << endl;

    //Traverse list.
    for (int i = 0; i < randomList.Length(); i++)
    {
        someSong = randomList.GetNextItem();
        if (someSong.artist == artistName)
            flag++;
    }

    //Alerts user if artist is not in the list.
    if (!flag)
    {
        cout << "That artist is not in this list." << endl << endl;
        return;
    }

    //Reset list for traversal.
    randomList.Reset();

    //Display songs by input artist.
	  cout << "Here are the songs by " << artistName << endl << endl << "Title"
         << setw(53) << "Rank" << setw(7) << right << "Year" << endl
         << string(65, '-') << endl;
    for (int i = 0; i < randomList.Length(); i++)
        {
            someSong = randomList.GetNextItem();
            if (someSong.artist == artistName)
            {
                cout << setw(54) << left << someSong.title << setw(3)
                     << someSong.rank << setw(8) << right << someSong.year
                     << endl;
            }
		    }
    cout << string(65, '-') << endl << endl;

    return;
}

//4: Prompts the user for the title of a song and adds the song to the list.
void AddSong(List& randomList)
{
    //Declare local variables.
    std::string  artist,    //Stores input artist name.
                 songName;  //Stores input song name.
    ListItemType newSong;   //Stores new Song-type object
    int          rank,      //Stores input song rank.
                 year;      //Stores input song year.

    //Display choice for user.
    cout << setw(10) << " " << "2.  Add a song" << endl << endl;

    //Alert user that the list is full, thus no songs may be added.
    if (randomList.IsFull())
    {
        cout << "The list is full." << endl << endl;
        return;
    }

    //Reset list for iteration.
    randomList.Reset();

    //Prompts user to enter new song data.
    cout << "Please enter appropriate info for the song: " << endl << "Artist: "
         ;
    getline(cin, artist);
    cout << "Title: ";
    getline(cin, songName);
    cout << "Rank: ";
    cin >> rank;
    do //Repeatedly ask for year until an appropriate year is supplied.
    {
        cout << "Year: ";
        cin  >> year;
        if ((year > 2015) || (year < 2012))
        {
            cout << "This list can only accept years between 2012 and 2015."
                 << endl;
        }
    } while ((year > 2015) || (year < 2012));

    //Fill in all fields of new Song-Type object.
    newSong.artist = artist;
    newSong.title  = songName;
    newSong.rank   = rank;
    newSong.year   = year;

    //Check to see if song is already in list.
    for (int i = 0; i < randomList.Length(); i++)
    {
        if (randomList.IsPresent(newSong))
        {
            cout << "That song is already in the list." << endl;
            return;
        }
    }

    //Add new item to list.
    randomList.Insert(newSong);

    //Lets the user know their add was successful.
    cout << endl << string(97, '-') << endl <<  "Congratulations! Your song: "
         << endl << songName << " by " << artist << " has been added to the "
         << "list." << endl << string(97, '-') << endl << endl;

    return;
}

//5: Prompts the user for the title of a song and deletes the song from the list
void DeleteSong(List& randomList)
{
    //Declare local variables.
    std::string  artist,        //Stores song's artist's name.
                 songName;      //Stores song name.
    ListItemType someSong,      //Stores next song-type object in list.
                 rejectedSong;  //Stores song-type object to be deleted.
	  int          i;             /*
                                Used in for loop and is used to determine if
                                song is present in the list.
                                */

    //Display choice for user.
    cout << setw(10) << " " << "3.  Delete a song" << endl << endl;

    //Lets the user know if the list is empty, thus nothing may be deleted.
    if (randomList.IsEmpty())
    {
        cout << "The list is empty, there is nothing to delete.";

        return;
    }

    //Reset list for iteration.
    randomList.Reset();

    //Prompt user to enter relevent song information for deletion.
    cout << "Please enter appropriate info for the song: " << endl << "Artist: "
         ;
    getline(cin, artist);
    cout << "Title: ";
    getline(cin, songName);
    cout << endl;

    //Deletes the song if it was found.
    for (i = 0; i < randomList.Length(); i++)
    {
        someSong = randomList.GetNextItem();
        if ((someSong.title == songName) && (someSong.artist == artist))
        {
            randomList.Delete(someSong);
            cout << string(97, '-') << endl << "Deleting: " << endl << songName
                 << " by " << artist << endl << '.' << endl << '.' << endl
                 << '.' << endl << "Deletion complete." << endl
                 << string(97, '-') << endl << endl;

            return;
        }
    }

  //Alerts user if the song they entered was not in the list.
	if (i == randomList.Length())
		cout << "That song is not in the list." << endl << endl;

    return;
}

/*
6: Prompts the user for the year value and displayes all the top songs from that
   year.
*/
void DisplayYear(List randomList)
{
    //Declare local variables.
    int          year;      //Stores value of year to be displayed.
    ListItemType someSong;  //Stores next song-type object in list.

    //Display choice for user.
    cout << setw(10) << " " << "4.  Print" << endl << endl;

    //Prompts the user to enter they value of the year they would like to see.
    cout << "Please enter the year of songs you would like to see: ";
    cin  >> year;
    cin.ignore(100, '\n');
    cout << endl << endl;

    //Lets user know if they have entered an undesirable year.
    if ((year > 2015) || (year < 2012))
    {
        cout << "There are no songs from that year in this list.\n" << endl;

        return;
    }

    //Display songs corresponding to input year.
    cout << setw(52) << "Top songs from " << year << ":\n" << endl << setw(42)
         << left << "Artist" << setw(51) << "Title" << setw(6) << "Rank" << endl
         << string(97, '-') << endl;
    randomList.Reset();
    for (int i = 0; i < randomList.Length(); i++)
    {
        someSong = randomList.GetNextItem();
        if (someSong.year == year)
            cout << someSong;
    }
    cout << string(97, '-') << endl << endl;

    return;
}
