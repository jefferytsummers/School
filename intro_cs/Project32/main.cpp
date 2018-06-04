/*
PROGRAMMER:          Ryan Florida
Assignment:          OLA7 Part A
Class:               CSCI 2170 Section 001
Course Instructor:   Dr. Li
Due Data:            Midnight, Thursday August 4 2016

Description:         This program is used to generate and display a flight
                     itenerary for the user. The program will read in a file
                     of origin and destination cities, then it will display
                     the itenerary, if it exists. The total cost of the full
                     route will also be calculated and displayed for
                     convenience. If there is no flight, or set of flights, that
                     links the origin and destination cities an error message
                     will be displayed.
*/

#include "flightmap.h"
#include <fstream>
#include <cassert>

using namespace std;

int main()
{
	  //Declare variables.
	  string    originCity, //Store name of origin city.
	            nextCity;   //Store name of next city.
	  ifstream  inFile;     //Store input file.
	  FlightMap flights;    //FlightMap object.

    //Open and assert input file.
	  inFile.open("../requests.dat");
	  assert(inFile);

	  //Generate array of cities using data file: cities.dat.
	  flights.GenerateCityArray("../cities.dat");

	  //Generate flight list using data file: flights.dat.
	  flights.GenerateFlightList("../flights.dat");

    //Read in values from the input file to originCity and nextCity variables.
    //After this is complete, the flight path shall be displayed, granted it
    //exists. If no flight path exists, the user will be notified.
	  while (inFile >> originCity >> nextCity)
	  {
        flights.isPath(originCity, nextCity);
		    cout << endl << endl;
	  }

    inFile.close();

	  return 0;
}
