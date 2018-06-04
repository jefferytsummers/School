#include <fstream>
#include <cassert>
#include "flightmap.h"
#include <iomanip>
#include <stack>

using namespace std;

FlightMap::FlightMap()
{
	  GetNumOfCities("../cities.dat");
	  flights = new SortedList[numOfCities];
	  cities  = new std::string[numOfCities];
	  visited = new bool[numOfCities];
}


//*****************************************************************************
void FlightMap::GetNumOfCities(std::string fileName)
{
	  ifstream myIn;

	  myIn.open(fileName);
	  assert(myIn);

	  myIn >> numOfCities;

	  myIn.close();

	  return;
}


//*****************************************************************************
void FlightMap::GenerateCityArray(std::string fileName)
{
	  ifstream myIn;
	  string   skipLine,
			       temp;
	  int      i,
	           j,
		         minIndex;

	  myIn.open(fileName);
  	assert(myIn);

  	myIn >> skipLine;

  	for (int r = 0; r < numOfCities; r++)
	  {
    		myIn >> cities[r];
			  visited[r] = false;
	  }

	  myIn.close();

	  for(i = 0; i < (numOfCities - 1); i++)
	  {
		    minIndex = i;
		    for (j = (i + 1); j < numOfCities; j++)
		    {
			      if (cities[j] < cities[minIndex])
				        minIndex = j;
		    }

		    if (minIndex != i)
		    {
			      temp             = cities[i];
			      cities[i]        = cities[minIndex];
			      cities[minIndex] = temp;
		    }
	  }

    myIn.close();

	  return;
}


//*****************************************************************************
void FlightMap::GenerateFlightList(string inputFileName)
{
	  ifstream inFile;
    NodePtr  newNodePtr;

	  inFile.open(inputFileName);
	  assert(inFile);

	  newNodePtr = new NodeType;

	  while (inFile >> newNodePtr->data.flightNum)
	  {
		    inFile >> newNodePtr->data.fromCity;
		    inFile >> newNodePtr->data.toCity;
		    inFile >> newNodePtr->data.flightCost;

			  for (int i = 0; i < numOfCities; i++)
		  	{
				   flights[i].Reset();
				   if (newNodePtr->data.fromCity == cities[i])
					 flights[i].Insert(newNodePtr->data);
			  }
	  }

    inFile.close();

  	return;
}


//*****************************************************************************
void FlightMap::Display()
{
	  cout << right << setw(9) << "Origin" << setw(27) << "Destination"
	       << setw(15) << "Flight" << setw(10) << "Price" << endl
		     << "==============================================================="
         << endl;

	  for (int i = 0; i < numOfCities; i++)
	  {
		    flights[i].Reset();
		    if (flights[i].HasNext())
			      cout << " From " << setw(13) << left << cities[i] << setw(6)
			           << " to: " << flights[i].GetNextItem();
		    while (flights[i].HasNext())
			      cout << setw(25) << "" << flights[i].GetNextItem();
	  }

    return;
}


//*****************************************************************************
void FlightMap::MarkVisited(std::string city)
{
    for (int i = 0; i < numOfCities; i++)
		{
        if (cities[i] == city)
				    visited[i] = true;
		}

		return;
}


//*****************************************************************************
bool FlightMap::IsVisited(std::string city)
{
		int i;

		for (i = 0; i < numOfCities; i++)
		{
			  if (cities[i] == city)
				    break;
		}

		return (visited[i]);
}


//*****************************************************************************
void FlightMap::UnvisitAll()
{
		for (int i = 0; i < numOfCities; i++)
			  visited[i] = false;

		return;
}


//*****************************************************************************
bool FlightMap::GetNextCity(std::string city, std::string& nextCity)
{
	  ItemType record;

	  for (int i = 0; i < numOfCities; i++)
	  {
		    flights[i].Reset();

		    if (cities[i] == city)
		    {
			      while (flights[i].HasNext())
			      {
				        record = flights[i].GetNextItem();
				        if (!IsVisited(record.toCity))
				        {
					          nextCity = record.toCity;
					          return true;
				        }
			      }
		    }
	  }

	  return false;
}


//*****************************************************************************
void FlightMap::isPath(std::string originCity, std::string destinationCity)
{
	  stack <string> aStack,
                   reverseStack;
	  string         topCity,
	                 nextCity,
		       		     temp;
	  bool           success,
	         				 originCheck = false,
					         destinationCheck = false;
	  int            size,
				           j,
					         sum = 0;
	  ItemType       record,
	                 recordClone;

	  for (int i = 0; i < numOfCities; i++)
	  {
		   if (cities[i] == originCity)
		     	 originCheck = true;
		   if (cities[i] == destinationCity)
			     destinationCheck = true;
	  }

	  if (!(originCheck && destinationCheck))
	  {
		   cout << "Sorry, EastWest Airline does not serve " << originCity
			      << endl;
		   return;
	  }

	  UnvisitAll();

	  aStack.push(originCity);
	  MarkVisited(originCity);
	  topCity = aStack.top();
	  while (!aStack.empty() && topCity != destinationCity)
	  {
		    success = GetNextCity(topCity, nextCity);
		    if (!(success || aStack.empty()))
		        aStack.pop();
		    else
		    {
			      aStack.push(nextCity);
			      MarkVisited(nextCity);
		    }

		   if (!aStack.empty())
			     topCity = aStack.top();
	     }

	     if (aStack.empty())
	     {
		        cout << "Request is to fly from " << originCity << " to " 
					  << destinationCity << "." << endl
					  << "There are no flights from " << originCity << " to "
                 << destinationCity << "." << endl;
		        return;
	     }

	     else
	     {
		       size = aStack.size();

		       for (int i = 0; i < size; i++)
		       {
		         	 temp = aStack.top();
		        	 aStack.pop();
		        	 reverseStack.push(temp);
		       }

		       cout << "Request is to fly from " << originCity << " to "
			          << destinationCity << "." << endl << "FlyWithUs airline serves "
			          << "between these two cities." << endl << "The flight itinerary"
			          << " is:" << endl << endl << left << setw(8) << "Flight #"
			          << setw(5) << " " << setw(13) << "From" << setw(5) << " "
			          << setw(13) << "To" << setw(5) << " " << setw(4) << "Cost"
                << endl << "==================================================="
                << "===" << endl;

		       for (int i = 0; i < (size - 1); i++)
		       {
			         temp = reverseStack.top();
			         reverseStack.pop();

			         for(j = 0; j < numOfCities; j++)
			         {
				           flights[j].Reset();
				           if (cities[j] == temp)
				           {
					             while (flights[j].HasNext())
					             {
						               record = flights[j].GetNextItem();
						               if (record.toCity == reverseStack.top())
						               {
						               	   recordClone = record;
							                 break;
						                }
					             }
				           }
		           }

			         cout << left << setw(8) << recordClone.flightNum << setw(5)
                    << " " << setw(13) << temp << setw(5) << " " << setw(13)
                    << reverseStack.top() << setw(6) << right << " $"
                    << setw(3) << recordClone.flightCost << endl;

			         sum += recordClone.flightCost;
		       }

		       cout << setw(47) << right << "Total:" << setw(3) << "$" << setw(3)
                << sum << endl;
	  }
}


//*****************************************************************************
FlightMap::~FlightMap()
{
	  delete [] visited;
	  delete [] cities;
	  delete [] flights;

	  cities  = NULL;
	  flights = NULL;
	  visited = NULL;
}
