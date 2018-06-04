#include <iostream>
#include "mycomplexclass.h"

MyComplexClass::MyComplexClass()
{
    rePart = 0.0;
    imPart = 0.0;
}

MyComplexClass::MyComplexClass(float Re, float Im)
{
    rePart = Re;
    imPart = Im;
}

MyComplexClass::MyComplexClass(const MyComplexClass& otherCmplxNum)
{
    std::cout << "Copy constructor called." << std::endl;
    rePart = otherCmplxNum.rePart;
    imPart = otherCmplxNum.imPart;
}

void MyComplexClass::SetValues(float Re, float Im)
{
    rePart = Re;
    imPart = Im;
}

float MyComplexClass::GetReal() const
{
    return rePart;
}

float MyComplexClass::GetIm() const
{
    return imPart;
}


void MyComplexClass::Display() const
{
    std::cout << *this;
}

bool MyComplexClass::EqualTo(MyComplexClass rhs)
{
    return (rePart == rhs.rePart && imPart == rhs.imPart);
}

bool MyComplexClass::operator ==(MyComplexClass rhs)
{
    return (rePart == rhs.rePart && imPart == rhs.imPart);
}

std::ostream& operator <<(std::ostream& os, const MyComplexClass& cNum)
{
    if (cNum.imPart >= 0)
        os << cNum.rePart << " + " << cNum.imPart << "i" << std::endl;
    else
        os << cNum.rePart << " - " << -(cNum.imPart) << "i" << std::endl;
    return os;
}

std::istream& operator >>(std::istream& is, MyComplexClass& cNum)
{
    std::cout << "Please enter values for the real and imaginary parts: ";
    is >> cNum.rePart >> cNum.imPart;

    return is;
}
