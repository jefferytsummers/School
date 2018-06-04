////Author:      Ryan Florida
////Program:     OLA6
////Due Date:    April 12, 2017
////Description: This program file is the header file for the BST class.

#pragma once
#include <iostream>
#include <unordered_map>
#include <string>
#include "Student.h"
#include <stdlib.h>
#include <time.h>
#include <vector>

using std::vector;
using std::string;
using std::rand;
using std::srand;

//Make struct for tree nodes.
struct TreeNode
{
    Student item;
    string  left_child_mNumber;
    string  right_child_mNumber;
};

//Aliases.
typedef TreeNode* treePtr;
typedef vector<std::string>::iterator strIter;
typedef vector<bool>::iterator boolIter;

//Make Class.
class BST
{
  public:
      //Constructor
      BST();

      //In-order traversal of list.
      void in_order(void);

      //Search by M#
      void search(string m_num);

      //Insert new Student object
      void bstInsert(string m_num);

      //Delete Student object
      void deleteNode(string m_num);


  private:
      //Member data
      std::unordered_map<std::string, TreeNode> tree;          //Hash table to represent BST.
      string                                    root;          //Represents root node of tree.


      //Functions that do not benefit the user.********************************
      //This function generates a random phone number for the student.
      string GeneratePhoneNumber(void);
      //This functions generates a random address for the student.
      string GenerateAddress(void);
      //This is the recursive traversal function.
      void   InOrderTraversal(string m_number);
      //This is the recursive insertion function.
      void   insertNode(string &currentRoot, string m_number);
      string InOrderSuccessor(string m_number);
      string InOrderPredecessor(string m_number);
};
