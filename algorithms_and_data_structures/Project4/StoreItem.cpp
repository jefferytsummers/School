////Author:      Ryan Florida
////Project:     OLA4
////Due Date:    March 20, 2017
////Description: This is the implementation file for the base class StoreItem.
#include "StoreItem.h"

//Constructor.
StoreItem::StoreItem(std::string barcode, double price, int copy, int demand)
:m_barcode(barcode), m_price(price), m_copy(copy), m_demand(demand)
{
}

//*****************************************************************************
//Return item barcode.
std::string StoreItem::getBarcode(void) const
{
    return m_barcode;
}

//*****************************************************************************
//Return item price.
double StoreItem::getPrice(void) const
{
    return m_price;
}

//*****************************************************************************
//Return number of copies of item.
int StoreItem::getCopy(void) const
{
    return m_copy;
}

//*****************************************************************************
//Return number representing the demand for the item.
int StoreItem::getDemand(void) const
{
    return m_demand;
}

//*****************************************************************************
//Increment the number of copies of the item.
void StoreItem::increaseCopy(void)
{
    m_copy++;
    return;
}

//*****************************************************************************
//Decrement the number of copies of the item.
void StoreItem::decreaseCopy(void)
{
    m_copy--;
    return;
}

//*****************************************************************************
//Increment the demand for the item.
void StoreItem::increaseDemand(void)
{
    m_demand++;
    return;
}

//*****************************************************************************
//Decrement the demand for the item.
void StoreItem::decreaseDemand(void)
{
    if(m_demand > 0)
        m_demand--;
    return;
}

//*****************************************************************************
//Overload == operator.
bool StoreItem::operator == (const StoreItem& rhs) const
{
    return m_barcode == rhs.m_barcode;
}

//*****************************************************************************
//Overload < operator.
bool StoreItem::operator < (const StoreItem& rhs) const
{
    return m_barcode < rhs.m_barcode;
}

//*****************************************************************************
//Destructor.
StoreItem::~StoreItem()
{
}