////Author:      Ryan Florida
////Project:     OLA4
////Due Date:    March 20, 2017
////Description: This is the implementation file for the derived class Book.

#include "Book.h"
#include <sstream>

//Constructor.
Book::Book(std::string title, std::string author, std::string barcode,
        std::string publicationDate, double price, int copy, int demand)
:StoreItem(barcode, price, copy, demand), b_title(title), b_author(author),
    b_publicationDate(publicationDate)
{
}

//*****************************************************************************
//Return book title.
std::string Book::getTitle() const
{
    return b_title;
}

//*****************************************************************************
//Return book author.
std::string Book::getAuthor() const
{
    return b_author;
}

//*****************************************************************************
//Return pointer of Book type that stores the address of a Book type object
//that is created based on the string type parameter "info".
Book* Book::createFromString(const std::string info)
{
    //Local variable declaration.
    char              trashChar;
    std::stringstream ss(info);
    std::string       trashString,
                      barcode,
                      title,
                      author,
                      publicationDate;
    double            price;
    int               copy,
                      demand;

    //Stores value taken from info string in appropriate locations.
    ss >> trashChar;
    std::getline(ss, trashString, DELIMITER);
    std::getline(ss, barcode, DELIMITER);
    std::getline(ss, title, DELIMITER);
    std::getline(ss, author, DELIMITER);
    std::getline(ss, publicationDate, DELIMITER);
    ss >> price;
    ss >> trashChar;
    ss >> copy;
    ss >> trashChar;
    ss >> demand;

    //Create customized Book type object and assign to a pointer of Book type.
    Book* bookPtr = new Book(title, author, barcode, publicationDate, price,
                             copy, demand);

    return bookPtr;
}

//*****************************************************************************
void Book::printItem()
{
    std::cout << "\n******************************* Book with barcode " 
              << m_barcode << " ***********************************\n" 
              << "Title:            " << b_title << '\n' << "Author:     "
              << "      " << b_author << '\n' << "Publication Date: " 
              << b_publicationDate << '\n' << "Price:            " << m_price
              << '\n' 
              << "Number of copies: " << m_copy << '\n' << "Number in demand: "
              << m_demand << '\n' << '\n';

    return;
}
