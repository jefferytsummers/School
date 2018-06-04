#include <iostream>
#include <fstream>
#include <string>
#include <cassert>


using namespace std;

//Forward declaration.
struct Node;

//Create an alias.
typedef string ListItemType;

//Define struct.
struct Node
{
    ListItemType data;
    Node* next;
};

//Create an alias.
typedef Node* NodePtr;

//Declare functions.
void BuildSortedList(ifstream&, NodePtr&);
void SortedListInsert(ListItemType, NodePtr&);
void DisplayList(NodePtr);
void DestroyList(NodePtr&);

//Main
int main()
{
    //Declare variables.
    ifstream myIn;
    NodePtr  head = NULL;

    //Open and assert file.
    myIn.open("produce.dat");
    assert(myIn);

    //Call functions.
    BuildSortedList(myIn, head);
    DisplayList(head);
    DestroyList(head);

    return 0;
}


//Creates a sorted list.
void BuildSortedList(ifstream& file, NodePtr& ptr)
{
    //Declare local variables.
    ListItemType item;

    //Read in items from file.
    while (file >> item)
    {
        SortedListInsert(item, ptr);
    }

    return;
}


//Inserts items in the list in a sorted manner.
void SortedListInsert(ListItemType item, NodePtr& headPtr)
{
    //Declare local variables.
    NodePtr curr,
            prev,
            newNodePtr;

    newNodePtr       = new Node;
    newNodePtr->data = item;
    newNodePtr->next = NULL;

    if (headPtr == NULL)
    {
        headPtr = newNodePtr;
    }

    else
    {
        curr = headPtr;
        prev = NULL;
        while ((curr != NULL) && (curr->data < item))
        {
            prev = curr;
            curr = curr->next;
        }

        if (prev == NULL)
            headPtr = newNodePtr;
        else
            prev->next = newNodePtr;

        newNodePtr->next = curr;
    }

    return;
}


//Display list.
void DisplayList(NodePtr ptr)
{
    //Declare local variable.
    NodePtr curr = ptr;

    while (curr != NULL)
    {
        cout << curr->data << endl;
        curr = curr->next;
    }

    return;
}


//Destroy list.
void DestroyList(NodePtr& headPtr)
{
    //Declare local variables.
    NodePtr temp,
            curr = headPtr;

    while (curr != NULL)
    {
        temp = curr;
        curr = curr->next;
        temp->next = NULL;
        delete temp;
    }

    return;
}
