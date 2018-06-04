#ifndef FRACTION_H
#define FRACTION_H
#include <iostream>

// Header file fraction.h declares class Fraction.
class Fraction
// Class Fraction represents the numerator and
// denominator of a fraction.
{
  public:

    // Constructors

    // default constructor
    // Post: Numerator and denominator have been set to zero
    Fraction();

    // copy constructor
    // Post: Numerator has been set to the Numerator of the right-hand-side object
    //       denominator has been set to the Denominator of the right-hand-side object
    Fraction(const Fraction& rhs);

    // mutators
    void SetNumerator(int num);

    void SetDenominator(int denom);

    // Post: self + rhs fraction is returned.
    Fraction Add(const Fraction & rhs);

    // Post: whether the self fraction is less than the rhs fraction is returned
    bool LessThan(const Fraction & rhs) const;

    void Display(const Fraction &rhs) const;

    // overloaded operators
    // define overloaded > operator
    friend bool operator>(const Fraction&, const Fraction&);

    // define overloaded != operator
    friend bool operator!=(const Fraction&, const Fraction&);

    // define overloaded << operator, display the fraction in the format :  numerator/denominator
    friend std::ostream& operator<<(std::ostream&, const Fraction&);

    // define overloaded >> operator
    friend std::istream& operator>>(std::istream&, Fraction&);

    // Destructor

    ~Fraction();

  private:
    int numerator;
    int denominator;
};

#endif
