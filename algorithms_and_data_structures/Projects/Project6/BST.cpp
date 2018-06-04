////Author:      Ryan Florida
////Program:     OLA6
////Due Date:    April 12, 2017
////Description: This program file is to provide implementation for the BST
////             class.
#include "BST.h"
#include <cmath>

const string _null = "M00000000";
typedef std::unordered_map<string, TreeNode>::iterator iter;

//Constructor
BST::BST()
:root(_null)
{}

//*****************************************************************************
//In-order traversal of list.
void BST::in_order(void)
{
    //Check if tree is empty; if the tree is not empty, then carry out the
    //traversal.
    if(tree.empty())
        printf("Tree is empty.\n");
    else
        InOrderTraversal(root);
    return;
}

//*****************************************************************************
//Search by M# and print selected student info.
void BST::search(string m_num)
{
    //Display the desired student information.
    cout << "\nYour search for student " << m_num << " returned the following "
         << "result:\n" << tree.find(m_num)->second.item;

    return;
}

//*****************************************************************************
//Insert new Student object
void BST::bstInsert(string m_num)
{
    //Make new tree node for insertion.
    TreeNode newNode;
    string   phoneNum           = GeneratePhoneNumber(), //generate phone #
             newAddress         = GenerateAddress();     //generate address.

    //Initialize new object.
    newNode.item                = Student(m_num, phoneNum, newAddress);
    newNode.left_child_mNumber  = _null;
    newNode.right_child_mNumber = _null;

    //Make key-value pair and insert new node into hash map.
    tree.insert(std::make_pair(m_num, newNode));

    //Call to recursive insertion.
    insertNode(root, m_num);
    return;
}

//*****************************************************************************
//Delete Student object
void BST::deleteNode(string m_num)
{
    //If tree is empty, let the user know.
    if(!root.compare(_null))
    {
        cout << "The tree is empty, therefore there are no nodes to delete."
             << endl;
        return;
    }

    //If we are deleting the root.
    if(!root.compare(m_num))
    {
        //If root has 0 or 1 child(ren).
        if(!(tree[root].right_child_mNumber.compare(_null) &&
               tree[root].left_child_mNumber.compare(_null)))
        {
            string temp = root;
            if(!tree[root].right_child_mNumber.compare(_null))
                root = InOrderPredecessor(tree[root].left_child_mNumber);
            else if(!tree[root].left_child_mNumber.compare(_null))
                root = InOrderSuccessor(tree[root].right_child_mNumber);
            else
                root = _null;
            tree.erase(temp);
        }
        //If root has two children, replace with inorder successor.
        else
        {
            string inOrderSuccessor =
                InOrderSuccessor(tree[root].right_child_mNumber),
                parentOfSuccessor;
            for(iter it = tree.begin(); it != tree.end(); ++it)
                if(!tree[it->second.item.get_m_number()].left_child_mNumber.compare(inOrderSuccessor))
                {
                    parentOfSuccessor = it->second.item.get_phone_number();
                    if(tree[inOrderSuccessor].right_child_mNumber.compare(_null))
                        tree[parentOfSuccessor].left_child_mNumber =
                            tree[inOrderSuccessor].right_child_mNumber;
                    else
                        tree[parentOfSuccessor].left_child_mNumber = _null;
                    break;
                }
            tree[inOrderSuccessor].left_child_mNumber = tree[root].left_child_mNumber;
            tree.erase(root);
            root = inOrderSuccessor;
        }
    }

    else
    {
        string left = tree[m_num].left_child_mNumber,
               right = tree[m_num].left_child_mNumber,
               parent;
        bool   child;

        for(iter it = tree.begin(); it != tree.end(); ++it)
        {
            if(!it->second.left_child_mNumber.compare(m_num))
            {
                parent = it->second.item.get_m_number();
                child  = 0;
                break;
            }

            else if(!it->second.right_child_mNumber.compare(m_num))
            {
                parent = it->second.item.get_m_number();
                child  = 1;
                break;
            }
        }

        if(!(left.compare(_null) || right.compare(_null)))
        {
            if(child)
                tree[parent].right_child_mNumber = _null;
            else
                tree[parent].left_child_mNumber  = _null;
            tree.erase(m_num);
        }
    }

}

//*****************************************************************************
//This function generates a random phone number for the student.
string BST::GeneratePhoneNumber(void)
{
    //Store digits for ten-digit phone number.
    int areaCode = 0,
        first3   = 0,
        last4    = 0;

    //Get a reasonable phone number.
    while((areaCode < 100) || (first3 < 100) || (last4 < 1000))
    {
        areaCode = rand()%1000;
        first3   = rand()%1000;
        last4    = rand()%10000;

    }

    //Construct phone number.
    std::string phoneNumber = "(" + std::to_string(areaCode) + ")" + "-"
                              + std::to_string(first3) + "-" +
                              std::to_string(last4);

    return phoneNumber;
}

//*****************************************************************************
//This functions generates a random address for the student.
string BST::GenerateAddress(void)
{
    //Arrays to store names of random famous streets.
    std::string set1[10] = {"Mulholland ", "Broadway ", "Abbey ", "Bourbon ",
                            "Wall ", "Pacific Coast ", "5th ", "Orchard ",
                            "Carnaby ", "Royal "},
                set2[8]  = {"Street", "Road", "Avenue", "Highway", "Boulevard",
                            "Alley", "Way", "Drive"},
                //Select random entries from the above arrays to make somewhat
                //unique street names.
                addressNum = std::to_string(abs((17*rand() + 59))%1000) + " ",
                newAddress = addressNum + set1[rand()%10] + set2[rand()%8];

    return newAddress;
}

//*****************************************************************************
//This is the recursive traversal function.
void BST::InOrderTraversal(string m_number)
{
    //If the tree is empty, display nothing.
    if (m_number.compare(_null) == 0)
        return;

    //Recursive call on left subtree.
    InOrderTraversal(tree.find(m_number)->second.left_child_mNumber);
    //Check to see if node has been deleted.
    cout << tree.find(m_number)->second.item;
    //Recursive call on right subtree.
    InOrderTraversal(tree.find(m_number)->second.right_child_mNumber);
    return;
}

//*****************************************************************************
//This is the recursive insertion function.
void BST::insertNode(string &currentRoot, string m_number)
{
    //If tree is empty, new node becomes the current root.
    if(currentRoot.compare(_null) == 0)
    {
         currentRoot = m_number;
         return;
    }

    //If the M-numbers match, do nothing.
    if(currentRoot.compare(m_number) == 0)
        return;
    //Search left subtree recursively until finding appropriate spot for
    //insertion of new node.
    else if(currentRoot.compare(m_number) > 0)
        insertNode(tree.find(currentRoot)->second.left_child_mNumber, m_number);
    //Search right subtree recursively until finding appropriate spot for
    //insertion of new node.
    else
        insertNode(tree.find(currentRoot)->second.right_child_mNumber, m_number);
}

string BST::InOrderSuccessor(string m_number)
{

    if(!tree[m_number].left_child_mNumber.compare(_null))
        return m_number;

    InOrderSuccessor(tree[m_number].left_child_mNumber);
}

string BST::InOrderPredecessor(string m_number)
{
    if(!tree[m_number].right_child_mNumber.compare(_null))
        return m_number;

    InOrderPredecessor(tree[m_number].right_child_mNumber);
}
