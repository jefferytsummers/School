#include "slist.h"

using namespace std;

SortedList::SortedList()
{
    head    = NULL;
    currPos = NULL;
    length  = 0;
    lastPtr = NULL;
}

//**************************************************************************
SortedList::SortedList(const SortedList& otherList)
{
    NodePtr fromPtr;
    NodePtr toPtr;

    if (otherList.head == NULL)
    {
   	    head = NULL;
	      return;
    }

    fromPtr    = otherList.head;
    head       = new NodeType;
    head->data = fromPtr -> data;

    toPtr   = head;
    fromPtr = fromPtr->next;
    while (fromPtr != NULL)
    {
	      toPtr->next = new NodeType;
	      toPtr       = toPtr->next;
	      toPtr->data = fromPtr->data;
	      fromPtr     = fromPtr->next;
    }

    toPtr->next = NULL;
    lastPtr     = toPtr;
}


//**************************************************************************
void SortedList::Insert(ItemType item)
{
    NodePtr currPtr;
    NodePtr prevPtr;
    NodePtr newNodePtr;

    newNodePtr       = new NodeType;
    newNodePtr->data = item;
    newNodePtr->next = NULL;

    if (head == NULL)
    {
	      head    = newNodePtr;
	      lastPtr = newNodePtr;
    }
    else
    {
	      currPtr = head;
	      prevPtr = NULL;
	      while (currPtr != NULL && currPtr->data < item)
	      {
	          prevPtr = currPtr;
	          currPtr = currPtr->next;
	      }

	      if (prevPtr == NULL)
	          head = newNodePtr;
	      else
	          prevPtr->next = newNodePtr;
	      newNodePtr->next = currPtr;

	      if (currPtr == NULL)
	          lastPtr = newNodePtr;
    }
    length++;
}

//**************************************************************************
void SortedList::Delete(ItemType item)
{
    NodePtr prevPtr = NULL;
    NodePtr currPtr = head;
    while (currPtr != NULL && currPtr->data != item)
    {
     	  prevPtr = currPtr;
	      currPtr = currPtr->next;
    }

    if (currPtr != NULL)
    {
  	    if (currPtr == head)
	 	        head = currPtr->next;
	      else
		        prevPtr->next = currPtr->next;

	      if (currPtr == lastPtr)
		        lastPtr = prevPtr;

	      delete currPtr;
	      length --;
    }
}

//**************************************************************************
void SortedList::Reset()
{
    currPos = head;
}

//**************************************************************************
ItemType SortedList::GetNextItem()
{
    ItemType item;
    item    = currPos->data;
    currPos = currPos->next;
    return item;
}


//**************************************************************************
int SortedList::GetLength() const
{
    return length;
}

//**************************************************************************
bool SortedList::IsEmpty() const
{
    return (head==NULL);
}

//**************************************************************************
bool SortedList::HasNext() const
{
    return (currPos != NULL);
}

//**************************************************************************
bool SortedList::IsFull() const
{
    return false;
}

//**************************************************************************
bool SortedList::IsThere(ItemType item) const
{
    NodePtr currPtr = head;

    while (currPtr != NULL && currPtr->data != item)
    {
	      currPtr = currPtr->next;
    }

    if (currPtr != NULL)
  	    return true;
    else
  	    return false;
}

//**************************************************************************
SortedList::~SortedList()
{
    NodePtr tempPtr;
    NodePtr currPtr = head;

    while (currPtr != NULL)
    {
	      tempPtr = currPtr;
	      currPtr = currPtr->next;
	      delete tempPtr;
    }
}
