//// Author:      Ryan Florida
//// Project:     OLA2
//// Due Date:    February 15, 2017
//// Description: **See ola2.cpp for most of the description.** In this file,
////              the methods of the student class are implemented.
#include "Student.h"
#include <iostream>

//*****************************************************************************
//Default constructor with initialization list.
Student::Student()
    :m_id(" "), m_total(0), m_letterGrade(' '), m_score()
{
}

//*****************************************************************************
//Accessor
//Returns student id to caller.
std::string Student::getID(void) const
{
    return m_id;
}

//*****************************************************************************
//Mutator
//Sets student id to an input id.
void Student::setID(std::string inputID)
{
    m_id = inputID;
    return;
}

//*****************************************************************************
//Mutator
//Changes score member data to new input value.
void Student::changeScore(const ScoreType score, const int newScore)
{
    m_score[score] = newScore;
    return;
}

//*****************************************************************************
//Accessor
//Returns selected score to caller.
int Student::getScore(const ScoreType score) const
{
    return m_score[score];
}

//*****************************************************************************
//Accessor
//Returns total to caller.
int Student::getTotal() const
{
    return m_total;
}

//*****************************************************************************
//Accessor
//Returns final letter grade to caller.
char Student::getLetter() const
{
    return m_letterGrade;
}

//*****************************************************************************
//Mutator
//Calculates the total score (sum of all other scores).
void Student::calculateTotal()
{
    m_total = 0;
    for(int i = 0; i < CATEGORY_NUM; i++)
        m_total += m_score[i];

    return;
}

//*****************************************************************************
//Mutator
//Determines final grade based on the value of the total score.
void Student::determineFinalGrade()
{
    if(m_total >= 90)
        m_letterGrade = 'A';
    else if(m_total >= 80)
        m_letterGrade = 'B';
    else if(m_total >= 70)
        m_letterGrade = 'C';
    else if(m_total >= 60)
        m_letterGrade = 'D';
    else
        m_letterGrade = 'F';

    return;
}

