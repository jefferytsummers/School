//*******************************************************

// Implementation file fraction.cpp implements the member
// functions of class Fraction.

#include <iostream>
#include "fraction.h"

Fraction::Fraction()
{
    numerator   = 0;
	  denominator = 1;
}

// mutators
void Fraction::SetNumerator(int num)
{
	  numerator = num;
}

void Fraction::SetDenominator(int denom)
{
	  denominator = denom;
}

Fraction::Fraction(const Fraction& rhs)
{
    std::cout << "(Copy constructor was called.)" << std::endl;
    numerator   = rhs.numerator;
    denominator = rhs.denominator;
}

Fraction Fraction::Add(const Fraction& rhs)
{
    Fraction temp;

    temp.numerator   = numerator*rhs.denominator + rhs.numerator*denominator;
    temp.denominator = denominator*rhs.denominator;

    return temp;
}

bool Fraction::LessThan(const Fraction& rhs) const
{
    return !((*this > rhs) || !(*this != rhs));
}

// define the overloaded < operator
bool operator>(const Fraction& frac1, const Fraction& frac2)
{
    int x = frac1.numerator,
        y = frac1.denominator,
        r = frac2.numerator,
        s = frac2.denominator;

    return ((float(x)/y) > (float(r)/s));
}

// define the overloaded != operator
bool operator!=(const Fraction& frac1, const Fraction& frac2)
{
    int x = frac1.numerator,
        y = frac1.denominator,
        r = frac2.numerator,
        s = frac2.denominator;

 //   if (((x > r && x%r == 0) && ((y > s && y%s == 0) || (s > y && s%y == 0)))
  //      || ((r > x && r%x == 0) && ((y > s && y%s == 0) || (s > y && s%y == 0)))
   //     || ((x == r && y == s)))
    //    return false;
   // else
    //    return true;
    return !(((x > r && x%r == 0) && ((y > s && y%s == 0) ||
            (s > y && s%y ==0))) || ((r > x && r%x == 0) && ((y > s && y%s == 0)
            || (s > y && s%y == 0))) || ((x == r && y == s)));
}

// define the overloaded << operator
std::ostream& operator<<(std::ostream& output, const Fraction& frac)
{
    output << frac.numerator << "/" << frac.denominator;

    return output;
}

// define the overloaded >> operator
std::istream& operator>>(std::istream& input, Fraction& frac)
{
    input >> frac.numerator >> frac.denominator;

    return input;
}

// Destructor
Fraction::~Fraction()
{
}
