//// Author:      Ryan Florida
//// Project:     OLA1
//// Due Date:    January 30, 2017
//// Description: This program will read in a file containing a class roster
////              along with student c-numbers and the respective grades
////              associated with each student on the roster. The program will
////              then prompt the user to enter the c-number for a particular
////              student to so as to display this chosen student's information.
////              The program will then display the entire class and all of the
////              information associated with each student.

#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

//The MAX constant holds the value for the maximum number of students that can
//be held in the roster.
const int MAX = 30;
//The SCORE_TYPE constant holds the value for how many score types one can
//expect per student.
const int SCORE_TYPE = 6;

//This will make the code a bit more readable.
enum ScoreType{CLA, OLA, QUIZ, HOMEWORK, EXAM, BONUS};

//struct containing a students c-number and all of their grades.
struct Student
{
    string ID;
    int    score[SCORE_TYPE];
};

/////////////////////////////Function Declarations/////////////////////////////
//1: Generates a roster of students from a selected input file. The Roster[]
//   parameter is used to store all of the student information. The
//   NumberOfStudents parameter is used to count the number of student objects
//   were actually created and inserted into the roster.
void GenerateRoster(Student Roster[MAX], int& NumberOfStudents);
//2: The user is prompted to selected a student, then that student's
//   information is displayed on the screen. The first parameter contains the
//   roster generated in function (1). The second parameter holds the number of
//   students on the roster. These are used in combination for us to be able to
//   display some information within the roster array.
void PrintSelectedStudentInformation(const Student Roster[MAX], int
     NumberOfStudents);
//3: Lists all students and their associated information. The first parameter
//   contains the roster generated in function (1). The second parameter holds
//   the number of students on the roster. These are used in combination for us
//   to be able to display all of the information within the roster array.
void DisplayRosterInformation(const Student Roster[MAX], int NumberOfStudents);

//*****************************************************************************
//0: Main
int main()
{
    //Variable declarations.
    Student Roster[MAX];
    string  cNumber;
    int     NumberOfStudents;

    //Call function to fill the class roster..
    GenerateRoster(Roster, NumberOfStudents);

    //Call function to display a selected student's information.
    PrintSelectedStudentInformation(Roster, NumberOfStudents);

    //Call function to display the entire class along with their information.
    DisplayRosterInformation(Roster, NumberOfStudents);

    return 0;
}

//*****************************************************************************
//1: Generates a roster of students from a selected input file. The Roster[]
//   parameter is used to store all of the student information. The
//   NumberOfStudents parameter is used to count the number of student objects
//   were actually created and inserted into the roster.
void GenerateRoster(Student Roster[MAX], int& NumberOfStudents)
{
    //Open file.
    ifstream inFile;
    inFile.open("point.dat");
    assert(inFile);

    //Get rid of the first line of the file (containing ID   CLA   OLA ...etc)
    string trashCollect;
    getline(inFile, trashCollect);

    //Fill the roster, as well as count the number of students on the roster.
    for(NumberOfStudents = 0; inFile >> Roster[NumberOfStudents].ID;
            NumberOfStudents++)
        for(int scoreType = 0; scoreType < SCORE_TYPE; scoreType++)
            inFile >> Roster[NumberOfStudents].score[scoreType];

    //Close the input file.
    inFile.close();

    return;
}

//*****************************************************************************
//2: The user is prompted to selected a student, then that student's
//   information is displayed on the screen. The first parameter contains the
//   roster generated in function (1). The second parameter holds the number of
//   students on the roster. These are used in combination for us to be able to
//   display some information within the roster array.
void PrintSelectedStudentInformation(const Student Roster[MAX],int
     NumberOfStudents)
{
    string cNumber;

    //Collect information from user.
    cout << "Please enter the c-number of the student whose information you"
         << " would like to display: ";
    cin  >> cNumber;
    cout << '\n';

    //Search for selected student and display associated information.
    for(int i = 0; i < NumberOfStudents; i++)
        //If cNumber == Roster[i].ID evaluates to true, that is to say: if the
        //input c-number matches a student on the roster's c-number, then the
        //program will display all of the student's information for the user.
        if(cNumber == Roster[i].ID)
        {
            cout << "Here is the information for student " << cNumber << ":"
                 << '\n' << "ID" << setw(10) << "CLA" << setw(5) << "OLA"
                 << setw(6) << "Quiz" << setw(10) << "Homework" << setw(6)
                 << "Exam" << setw(7) << "Bonus" << setw(7) << "Total"
                 << setw(12) << "FinalGrade" << '\n' << "--------------------"
                 << "---------------------------------------------" << '\n'
                 << setw(9) << left << Roster[i].ID << right << setw(3)
                 << Roster[i].score[CLA] << setw(5) << Roster[i].score[OLA]
                 << setw(6) << Roster[i].score[QUIZ] << setw(10)
                 << Roster[i].score[HOMEWORK] << setw(6)
                 << Roster[i].score[EXAM] << setw(7) << Roster[i].score[BONUS]
                 << '\n' << '\n';

            return;
        }

    //Let the user know if they entered an invalid c-number.
    cout << "That is an invalid c-number.\n\n";

    return;
}

//*****************************************************************************
//3: Lists all students and their associated information. The first parameter
//   contains the roster generated in function (1). The second parameter holds
//   the number of students on the roster. These are used in combination for us
//   to be able to display all of the information within the roster array.
void DisplayRosterInformation(const Student Roster[MAX], int NumberOfStudents)
{
    cout << "Here is the information for the entire class: " << '\n'
         << "ID" << setw(10) << "CLA" << setw(5) << "OLA" << setw(6) << "Quiz"
         << setw(10) << "Homework" << setw(6) << "Exam" << setw(7) << "Bonus"
         << setw(7) << "Total" << setw(12) << "FinalGrade" << '\n'
         << "-----------------------------------------------------------------"
         << '\n';

    //Display formatted output for the user.
    for(int i = 0; i < NumberOfStudents; i++)
    {
        cout << setw(9) << left << Roster[i].ID << right << setw(3)
             << Roster[i].score[CLA] << setw(5) << Roster[i].score[OLA]
             << setw(6) << Roster[i].score[QUIZ] << setw(10)
             << Roster[i].score[HOMEWORK] << setw(6) << Roster[i].score[EXAM]
             << setw(7) << Roster[i].score[BONUS] << '\n';
    }

    return;
}
