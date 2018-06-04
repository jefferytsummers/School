////Author:      Ryan Florida
////Project:     OLA4
////Due Date:    March 20, 2017
////Description: This is the implementation file for the derived class Movie.

#include "Movie.h"
#include <iostream>
#include <string>
#include <sstream>

//Constructor.
Movie::Movie(std::string title, std::string director, std::string barcode,
        double price, int copy, int demand)
:StoreItem(barcode, price, copy, demand), m_title(title), m_director(director)
{
}

//*****************************************************************************
//Return movie title.
std::string Movie::getTitle() const
{
    return m_title;
}

//*****************************************************************************
//Return director name.
std::string Movie::getDirector() const
{
    return m_director;
}

//*****************************************************************************
//Return pointer of Movie type that stores the address of a Movie type object
//that is created based on the string type parameter "info".
Movie* Movie::createFromString(const std::string info)
{
    //Local variable declaration.
    char              trashChar;
    std::stringstream ss(info);
    std::string       trashString,
                      barcode,
                      title,
                      director;
    double            price;
    int               copy,
                      demand;

    //Stores value taken from info string in appropriate locations.
    ss >> trashChar;
    std::getline(ss, trashString, DELIMITER);
    std::getline(ss, barcode, DELIMITER);
    std::getline(ss, title, DELIMITER);
    std::getline(ss, director, DELIMITER);
    ss >> price;
    ss >> trashChar;
    ss >> copy;
    ss >> trashChar;
    ss >> demand;

    //Create customized Movie type object and assign to a pointer of Movie type
    Movie* moviePtr = new Movie(title, director, barcode, price, copy, demand);

    return moviePtr;
}

//*****************************************************************************
//Print the object in a readable way.
void Movie::printItem()
{
    std::cout << "\n***************** Movie with barcode " << m_barcode 
              << " ****************\nTitle:            " << m_title << '\n' 
              << "Director:         " << m_director << '\n' << "Price:       "
              << "     " << m_price << "\nnumber of copies: " << m_copy << '\n'
              << "number in demand: " << m_demand << '\n' << '\n';
  
    return;
}



