#include "type.h"
#include <iomanip>

using namespace std;

bool FlightRec::operator ==(const FlightRec& rhs)
{
   	return (fromCity == rhs.fromCity);
}


//*****************************************************************************
bool FlightRec::operator >(const FlightRec& rhs)
{
	   return (toCity > rhs.toCity);
}


//*****************************************************************************
bool FlightRec::operator <(const FlightRec& rhs)
{
	   return (toCity < rhs.toCity);
}


//*****************************************************************************
bool FlightRec::operator <=(const FlightRec& rhs)
{
	   return ((toCity < rhs.toCity) || (toCity == rhs.toCity));
}


//*****************************************************************************
std::ostream& operator <<(std::ostream& os, const FlightRec& rec)
{
	   os << setw(20) << left << rec.toCity << setw(10) << rec.flightNum
	      << " $" << setw(3) << right << rec.flightCost << std::endl;

	  return (os);
}


//*****************************************************************************
bool FlightRec::operator !=(const FlightRec& rhs)
{
	  return ((fromCity == rhs.fromCity) && (toCity == rhs.toCity) &&
			      (flightCost == rhs.flightCost) && (flightNum == rhs.flightCost));
}
