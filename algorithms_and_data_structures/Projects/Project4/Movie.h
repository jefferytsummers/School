#pragma once
////Author:      Ryan Florida
////Project:     OLA4
////Due Date:    March 20, 2017
////Description: This is the header file for the derived class Movie.
#include <string>
#include "StoreItem.h"

class Movie : public StoreItem
{
  public:
      //default constructor setting every thing to empty or 0
      Movie( std::string title="", std::string director="",
          std::string barcode="", double price=0, int copy=0, int demand=0);

//*****************************************************************************
      std::string getTitle() const;

//*****************************************************************************
      std::string getDirector() const;

//*****************************************************************************
      //This function returns a dynamically created StoreItem object
      //which is created from a string.
      //The string info must be of the line format specificed in
      //inventory.txt
      Movie* createFromString( const std::string info) override;

//*****************************************************************************
      //Print current item to the screen
      void printItem() override;

//  private:
      std::string m_title;        // movie title
      std::string m_director;     // movie directors
};
