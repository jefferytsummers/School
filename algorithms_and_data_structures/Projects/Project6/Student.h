////Author:      Ryan Florida
////Program:     OLA6
////Due Date:    April 12, 2017
////Description: This program file is the header file for the Student class.
#pragma once
#include <iostream>
#include <string>

using std::cout;
using std::endl;

//Make class.
class Student
{
  public:
      //Default constructor
      Student();
      //Constructor
      Student(std::string m_num, std::string phone, std::string new_address);

      //Accessors**************************************************************
      //Returns student M-number to caller.
      std::string get_m_number(void) const;
      //Returns student phone number to caller.
      std::string get_phone_number(void) const;
      //Returns student address to caller.
      std::string get_address(void) const;

      //Mutators***************************************************************
      //Change student M-number.
      void set_m_number(std::string m_num);
      //Change student phone number.
      void set_phone_number(std::string phone_num);
      //Change student address.
      void set_address(std::string new_address);

      //Operator overloading***************************************************
      //Overload < operator by comparison of M-numbers.
      bool operator <(Student rhs);
      //Overload << operator to display student information.
      friend std::ostream& operator <<(std::ostream& os, const Student rhs);

  private:
      //Member data.
      std::string m_number;     //Store student M-number.
      std::string phone_number; //Store student phone number.
      std::string address;      //Store student address.
};