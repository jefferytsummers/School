#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

using namespace std;

//Forward declaration.
struct Node;

//Create alias.
typedef string ListItemType;

//Declare struct.
struct Node
{
    Node*        precede;
    ListItemType data;
    Node*        next;
};

//Create alias.
typedef Node* NodePtr;

//Declare functions.
void BuildSortedList(ListItemType, NodePtr&);
void InitializeDummyHead(NodePtr&);
void BuildList(ifstream&, NodePtr&);
void PrintForward(NodePtr);
void PrintBackward(NodePtr);
void DestroyList(NodePtr&);

//Main
int main()
{
    //Declare variables.
    ifstream myIn;
    NodePtr  head = NULL;

    //Open and assert data file.
    myIn.open("produce.dat");
    assert(myIn);

    //Call functions.
    InitializeDummyHead(head);
    BuildList(myIn, head);
    PrintForward(head);
    PrintBackward(head);
    DestroyList(head);

    //Close file.
    myIn.close();

    return 0;
}


//Initialize head to a dummy node.
void InitializeDummyHead(NodePtr& ptr)
{
    ptr          = new Node;
    ptr->precede = ptr;
    ptr->next    = ptr;

    return;
}


//Create a sorted circular doubly linked list.
void BuildList(ifstream& file, NodePtr& ptr)
{
    //Declare local variable.
    ListItemType item;

    //Read data from the input file.
    while (file >> item)
    {
        BuildSortedList(item, ptr);
    }

    return;
}


//Insert items into list in a sorted manner.
void BuildSortedList(ListItemType item, NodePtr& ptr)
{
    //Declare local variable.
    NodePtr curr       = ptr->next,
            newNodePtr = new Node;

    newNodePtr->data   = item;

    //Iterate through list.
    while (curr != ptr && curr->data < item)
        curr = curr->next;

    //Insert new node into list.
    curr->precede->next = newNodePtr;
    newNodePtr->precede = curr->precede;
    curr->precede       = newNodePtr;
    newNodePtr->next    = curr;

    return;
}


//Print list in forward direction.
void PrintForward(NodePtr ptr)
{
    //Declare local variable.
    NodePtr curr = ptr->next;

    cout << "Printing forward:" << endl << endl;

    //Display each element in the list.
    while (curr != ptr)
    {
        cout << curr->data << endl;
        curr = curr->next;
    }

    cout << endl;

    return;
}


//Print list in backward direction.
void PrintBackward(NodePtr ptr)
{
    //Declare local variable.
    NodePtr curr = ptr->precede;

    cout << "Printing backward:" << endl << endl;

    //Display each element in the list.
    while (curr != ptr)
    {
        cout << curr->data << endl;
        curr = curr->precede;
    }

    cout << endl;

    return;
}


//Destroy the list.
void DestroyList(NodePtr& headPtr)
{
    //Local variables.
    NodePtr temp,
            curr = headPtr->next;

    //Iterate through list.
    while (curr != headPtr)
    {
        temp          = curr;
        curr          = curr->next;
        temp->next    = NULL;
        temp->precede = NULL;
        delete temp;
    }

    //Delete the dummy head.
    headPtr->next    = NULL;
    headPtr->precede = NULL;
    delete headPtr;
    headPtr          = NULL;

    return;
}
