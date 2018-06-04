#pragma once
////Author:      Ryan Florida
////Project:     OLA4
////Due Date:    March 20, 2017
////Description: This is the header file for the derived class Book.
#include <string>
#include "StoreItem.h"

class Book : public StoreItem
{
    public:
        //Default constructor, sets everything to empty or zero.
        Book(std::string title = "", std::string author = "", std::string
                barcode = "", std::string publicationDate = "0", double price
                = 0, int copy = 0, int demand = 0);

//*****************************************************************************
//Return book title.
        std::string getTitle() const;

//*****************************************************************************
//Return book author.
        std::string getAuthor() const;

//*****************************************************************************
//This function returns a dynamically created StoreItem object which is created
//from a string. The string info must be of the line format specificed in
//inventory.txt
        Book* createFromString(const std::string info) override;

//*****************************************************************************
//Prints current item to the screen.
        void printItem() override;

//Private data.
    private:
        std::string b_title;
        std::string b_author;
        std::string b_publicationDate;
};
