////Author:      Ryan Florida
////Program:     OLA6
////Due Date:    April 12, 2017
////Description: This program file is to provide implementation for the Student
////             class.

#include "Student.h"

//Default Constructor
Student::Student()
{
}

//Constructor
Student::Student(std::string m_num, std::string phone, std::string new_address)
    :m_number(m_num), phone_number(phone), address(new_address)
{
}

//Accessors*******************************************************************
//Returns student M-number to caller.
std::string Student::get_m_number(void) const
{
    return m_number;
}

//Returns student phone number to caller.
std::string Student::get_phone_number(void) const
{
    return phone_number;
}

//Returns student address to caller.
std::string Student::get_address(void) const
{
    return address;
}

//Mutators*********************************************************************
//Change student M-number.
void Student::set_m_number(std::string m_num)
{
    m_number = m_num;
}

//Change student phone number.
void Student::set_phone_number(std::string phone_num)
{
    phone_number = phone_num;
}

//Change student address.
void Student::set_address(std::string new_address)
{
    address = new_address;
}

//Operator overloading*********************************************************
//Overload < operator by comparison of M-numbers.
bool Student::operator <(Student rhs)
{
    return(m_number.compare(rhs.m_number) < 0);
}

//Overload << operator to display student information
std::ostream& operator <<(std::ostream& os, const Student rhs)
{
    os << "M-number:     " << rhs.m_number << "\nPhone number: "
       << rhs.phone_number << "\nAddress:      " << rhs.address << "\n\n";
    return os;
}