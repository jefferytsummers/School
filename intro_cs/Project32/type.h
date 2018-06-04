#ifndef type_H
#define type_H

#include <iostream>
#include <string>

//Forward declaration.
struct FlightRec;

//Define "FlightRec" struct.
struct FlightRec
{
	  //Declare variables.
    std::string fromCity,    //Stores departure city.
                toCity;      //Stores destination city.
    int         flightNum,   //Stores flight numer.
                flightCost;  //Stores cost of flight.

	  //Overload == operator (compares fromCity fields).
    bool operator ==(const FlightRec&);

	  //Overload > operator (compares toCity fields).
    bool operator >(const FlightRec&);

	  //Overload < operator (compares toCity fields).
    bool operator <(const FlightRec&);

	  //Overload <= operator (compares toCity fields).
    bool operator <=(const FlightRec&);

	  //Overload << operator (displays all fields except fromCity).
    friend std::ostream& operator <<(std::ostream&, const FlightRec&);

	  //Overload != operator (compares each field within the record).
    bool operator !=(const FlightRec&);
};

#endif
