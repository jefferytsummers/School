////Author:      Ryan Florida
////Program:     OLA6
////Due Date:    April 12, 2017
////Description: This program file is provided as an interface to a binary
////             search tree composed of student nodes. The user may add and
////             delete nodes, search for particular nodes, and view an inorder
////             traversal of the BST with the methods provided in the BST class.
#include "BST.h"
#include <iostream>

int main()
{
    //Plant seed for random number generation.
    std::srand(time(NULL));

    //Make new binary search tree object.
    BST binarySearchTree;

    //Insert multiple nodes into the binary search tree.
    binarySearchTree.bstInsert("M00000005");
    binarySearchTree.bstInsert("M00000003");
    binarySearchTree.bstInsert("M00000002");
    binarySearchTree.bstInsert("M00000001");
    binarySearchTree.bstInsert("M00000004");
    binarySearchTree.bstInsert("M00000006");
    binarySearchTree.bstInsert("M00000009");
    binarySearchTree.bstInsert("M00000008");
    binarySearchTree.bstInsert("M00000007");
    binarySearchTree.bstInsert("M00000010");

    //Perform first inorder traversal of the binary search tree.
    printf("First inorder traversal of the binary search tree yields:\n");
    binarySearchTree.in_order();

    //Search BST for student with m-number "M00000007".
    binarySearchTree.search("M00000007");

    //Delete student with m-number "M00000002" from the BST.
    binarySearchTree.deleteNode("M00000002");
    //binarySearchTree.deleteNode("M00000001");

    //Second inorder traversal of the BST.
    printf("\nSecond inorder traversal of the binary search tree yields:\n");
    binarySearchTree.in_order();

    //Delete student with m-number "M00000005" from the BST.
    binarySearchTree.deleteNode("M00000005");

    //Second inorder traversal of the BST.
    printf("\nThird inorder traversal of the binary search tree yields:\n");
    binarySearchTree.in_order();

    return 0;
}
