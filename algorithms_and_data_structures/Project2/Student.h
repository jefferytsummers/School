/*
 * File:	Student.h
 * Author:	Zhijiang Dong
 * Course:	CSCI 3110
 * Instructor:	Zhijiang Dong
 * Date:	Oct. 06 2006
 *
 * Purpose: This file is a part of the 1st open lab assignment, which
 * includes Student.h, Student.cpp, Roster.h, Roster.cpp,
 * and main.cpp. This file gives the full definition
 * of the class Student.
 */

#ifndef __CSCI3110_STUDENT__
#define __CSCI3110_STUDENT__

#include <string>
#include <stdexcept>


class Student
{
	public:
		// The types of score. You can access the type or enumerators outside
		// of the Student class scope by the following expressions:
		//	Student::ScoreType              Student::CLA        Student::BONUS
		enum ScoreType {CLA, OLA, QUIZ, HOMEWORK, EXAM, BONUS};

		// To access the class constant outside of the Student class scope:
		//	Student::CATEGORY_NUM
		static const int CATEGORY_NUM = BONUS - CLA + 1;

		// default constructor. This is necessary since we define an array
		// of students in the class Roster
		Student( void );

		//Accessor & mutator of m_id
		std::string getID( void ) const;
		void setID( std::string ) ;


		//Accessor and mutator of m_score
		//ScoreType indicates which score you want to access
		void changeScore( const ScoreType, const int );
		int  getScore( const ScoreType ) const;

		//********************************************************************
		//Add your functions here if necessary
    //like getters and setters for m_total and m_letterGrade
    //
    //
    //// Author: Ryan Florida
    void calculateTotal();
    void determineFinalGrade();
    int  getTotal(void) const;
    char getLetter(void) const;
		//********************************************************************

	private:
		std::string		m_id;		// Student ID
		int				m_score[CATEGORY_NUM];
						// m_score[CLA] is CLA score
						// m_score[OLA] is OLA score
						// m_score[QUIZ] is QUIZ score
						// m_score[HOMEWORK] is HOMEWORK score
						// m_score[EXAM] is EXAM score
						// m_score[BONUS] is BONUS score
    int     m_total;  //total score, which is the sum of all scores
    char    m_letterGrade;
};
#endif
