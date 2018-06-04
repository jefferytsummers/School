//// Author:      Ryan Florida
//// Project:     OLA2
//// Due Date:    February 15, 2017
//// Description: **See ola2.cpp for most of the description.** In this file,
////              the methods of the Roster class are implemented.


#include "Roster.h"
#include "Student.h"
#include <cassert>
#include <iostream>
#include <iomanip>

//*****************************************************************************
//Constructor.
Roster::Roster(std::string courseName)
    :m_courseName(courseName)
{
}

//*****************************************************************************
//Define method that reads in student record based on input file (from
//ola2.cpp).
void Roster::readStudentRecord(std::string inputFile)
{
    //Variable declarations.
    int           cla,
                  ola,
                  quiz,
                  homework,
                  exam,
                  bonus;
    std::ifstream inFile;
    std::string   id,
                  trash;

    //Open and assert file.
    inFile.open(inputFile);
    assert(inFile);
    std::getline(inFile, trash);

    //Read in contents of file to modify student data.
    for(m_studentNum = 0; m_studentNum < MAX_NUM && inFile >> id;
            m_studentNum++)
    {
        inFile >> cla >> ola >> quiz >> homework >> exam >> bonus;
        m_students[m_studentNum].setID(id);
        m_students[m_studentNum].changeScore(Student::CLA, cla);
        m_students[m_studentNum].changeScore(Student::OLA, ola);
        m_students[m_studentNum].changeScore(Student::QUIZ, quiz);
        m_students[m_studentNum].changeScore(Student::HOMEWORK, homework);
        m_students[m_studentNum].changeScore(Student::EXAM, exam);
        m_students[m_studentNum].changeScore(Student::BONUS, bonus);
        m_students[m_studentNum].calculateTotal();
        m_students[m_studentNum].determineFinalGrade();
    }
}

//*****************************************************************************
//Print the information of a selected student (selected in ola2.cpp).
void Roster::printStudentInformation(std::string c_number) const
{
    //Print and format student info.
    for(int i = 0; i < m_studentNum; i++)
        if(m_students[i].getID() == c_number)
        {
            std::cout << "Here is the information for student "
                      << m_students[i].getID() << ":" << std::endl << "ID"
                      << std::setw(10) << "CLA" << std::setw(5) << "OLA"
                      << std::setw(6) << "Quiz" << std::setw(10) << "Homework"
                      << std::setw(6) << "Exam" << std::setw(7) << "Bonus"
                      << std::setw(7) << "Total" << std::setw(12)
                      << "FinalGrade" << std::endl << "-----------------------"
                      << "------------------------------------------"
                      << std::endl << std::setw(9) << std::left
                      << m_students[i].getID() << std::right << std::setw(3)
                      << m_students[i].getScore(Student::CLA) << std::setw(5)
                      << m_students[i].getScore(Student::OLA) << std::setw(6)
                      << m_students[i].getScore(Student::QUIZ) << std::setw(10)
                      << m_students[i].getScore(Student::HOMEWORK)
                      << std::setw(6) << m_students[i].getScore(Student::EXAM)
                      << std::setw(7)
                      << m_students[i].getScore(Student::BONUS) << std::setw(7)
                      << m_students[i].getTotal() << std::setw(12)
                      << m_students[i].getLetter() << std::endl << std::endl;
            return;
        }
    return;
}

//*****************************************************************************
//Display information of all students in the roster.
void Roster::printRoster(void) const
{
    //Printing formatted information.
    std::cout << "Here is the entire class roster: " << std::endl << "ID"
              << std::setw(10) << "CLA" << std::setw(5) << "OLA"
              << std::setw(6) << "Quiz" << std::setw(10) << "Homework"
              << std::setw(6) << "Exam" << std::setw(7) << "Bonus"
              << std::setw(7) << "Total" << std::setw(12) << "FinalGrade"
              << std::endl << "-----------------------------------------------"
              << "------------------" << std::endl;
    for(int i = 0; i < m_studentNum; i++)
            std::cout << std::setw(9) << std::left
                      << m_students[i].getID() << std::right << std::setw(3)
                      << m_students[i].getScore(Student::CLA) << std::setw(5)
                      << m_students[i].getScore(Student::OLA) << std::setw(6)
                      << m_students[i].getScore(Student::QUIZ) << std::setw(10)
                      << m_students[i].getScore(Student::HOMEWORK)
                      << std::setw(6) << m_students[i].getScore(Student::EXAM)
                      << std::setw(7)
                      << m_students[i].getScore(Student::BONUS) << std::setw(7)
                      << m_students[i].getTotal() << std::setw(12)
                      << m_students[i].getLetter() << std::endl;
    return;
}

