////Author:      Ryan Florida
////Project:     OLA2
////Due Date:    February 15, 2017
////Description: This program will implement two classes in order to maintain a
////             roster of students with associated information about those
////             students (c-number, grades, etc). In this particular file, the
////             user can label the roster however they please, choose their
////             desired input file, then they are prompted to enter a specific
////             student's c-number so as to see that student's information.
////             Once all of this is done, the entire roster (ie all of the
////             student information) is displayed for the user.
////
////             A note on the .h files: I did not include headers there,
////             except at the locations I declared methods because I did not
////             think it was reasonable to say I authored those files.


#include <iostream>
#include "Roster.h"
#include <string>

//Constant declared to provide an upper-bound on the number of students in a
//particular roster.
const int MAX = 30;

//0: Main.
int main()
{
    //Variable declarations.
    std::string c_number;
    Roster      adsRoster("CSCI 3110"); //Input string will determine roster
                                        //name.

    //Calling method to read in data file containing information about
    //students. Input string will determine input file.
    adsRoster.readStudentRecord("point.dat");

    //Prompting user to input student's c-number so as to display the desired
    //student's information.
    std::cout << "Please input a valid c-number: ";
    std::cin  >> c_number;
    std::cout << std::endl;
    adsRoster.printStudentInformation(c_number);

    //Prints the information of all students to standard out.
    adsRoster.printRoster();

    return 0;
}

