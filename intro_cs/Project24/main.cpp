#include <iostream>
#include <fstream>
#include <string>
#include <cassert>


using namespace std;


//Make alias.
typedef string ItemType;

//Foraward declaration.
struct NodeType;

//Make alias.
typedef NodeType* NodePtr;

//Define struct.
struct NodeType
{
    ItemType data;
    NodePtr  next;
};

//Declare functions.
void BuildList(ifstream&, NodePtr&);
void DisplayList(NodePtr);
bool IsPresent(ItemType, NodePtr);
void Delete(ItemType, NodePtr&);


//Main
int main()
{
    //Declare variables.
    ifstream myIn;
    NodePtr  head;
    ItemType item;

    //Open and assert file.
    myIn.open("grocery.dat");
    assert(myIn);

    //Call BuildList function.
    BuildList(myIn, head);

    //Call DisplayList function.
    DisplayList(head);

    //Ask user for item they would like to delete.
    cout << "Enter an item to be deleted from the list: ";
    cin  >> item;

    //Delete item, if it is present, and display newly edited list.
    if (IsPresent(item, head))
    {
        Delete(item, head);
        DisplayList(head);
    }

    else
        cout << "The item was not found in the list." << endl;

    return 0;
}


//Form the linked list.
void BuildList(ifstream& file, NodePtr& ptr)
{
    //Declare local variables.
    ItemType item;
    NodePtr  curr;

    //Form list.
    ptr  = new NodeType;
    curr = ptr;

    while (file >> item)
    {
        curr->data = item;
        curr->next = new NodeType;
        curr       = curr->next;
        curr->next = NULL;
    }

    return;
}


//Display the list for the user.
void DisplayList(NodePtr ptr)
{
    //Declare local variable.
    NodePtr curr = ptr;

    //Display items in list.
    while (curr != NULL)
    {
        cout << curr->data << endl;
        curr = curr->next;
    }

    return;
}


//Searches for input item in the input list.
bool IsPresent(ItemType item, NodePtr ptr)
{
    //Declare local variable.
    NodePtr curr = ptr;

    //Search for item.
    while (curr != NULL)
    {
        if (curr->data == item)
            return true;

        curr = curr->next;
    }

    return false;
}


//Delete input item, if present, from input list.
void Delete(ItemType item, NodePtr& ptr)
{
    //Declare local variables.
    NodePtr curr  = ptr,
            temp  = curr;
    int     count = 0;

    //Delete item, if present.
    while (curr != NULL)
    {
        if ((curr->data == item) && (count == 0))
        {
            ptr = curr->next;
            return;
        }

        if (curr->data == item)
        {
            temp->next = curr->next;
            curr->next = NULL;
            delete curr;
            curr       = NULL;
            return;
        }

        temp = curr;
        curr = curr->next;
        count++;
    }
    return;
}
