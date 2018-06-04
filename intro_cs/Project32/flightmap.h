#ifndef flightMap_H
#define flightMap_H

#include "slist.h"

//Define "FlightMap" class.
class FlightMap
{
  public:
  	//Default constructor.
  	FlightMap();

  	//Assign value to numOfCities variable (found in private data below).
  	void GetNumOfCities(std::string);

  	//Generate array of size numOfCities of City names.
  	void GenerateCityArray(std::string);

  	//Generate array of size numOfCities of flight lists.
  	void GenerateFlightList(std::string);

  	//Display each element of each list within flights array.
  	void Display();

	  //Marks city in cities array as visited (flips boolean value in visited
    //array to true).
	  void MarkVisited(std::string);

	  //Returns boolean value of array entry in visited array corresponding to
    //the city in cities array.
	  bool IsVisited(std::string);

	  //Flip all boolean values in visited array to false.
	  void UnvisitAll();

	  //Returns true if there is another city in the flightpath of current city.
    //Otherwise, return false.
	  bool GetNextCity(std::string, std::string&);

	  //Lets user know if there is a path between two cities, or not.
	  void isPath(std::string originCity, std::string destinationCity);

  	//Destructor.
  	~FlightMap();



  private:
  	int          numOfCities; //Stores number of cities from input file.
  	std::string* cities;      //Used to make array of string type.
  	SortedList*  flights;     //Used to make array of SortedList type.
	  bool*        visited;     //Used to make array of bool type.
};

#endif
