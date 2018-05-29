/*
    Author:      Ryan Florida
    Description: Read in a binary relation of the form
    {(num1, num2), (num3, num4), ...} and provide the user with different
    options of what they can do with their input relation.
*/

#include <iostream>

using namespace std;

//Declare global constants for array sizes.
const int MAX  = 10;
const int MAXX = MAX*MAX;

//Function declarations.
void GenerateAdjacencyMatrix(int adjacencyMatrix[][MAX], int &);  	      //1
void DisplayMenu(int adjacencyMatrix[][MAX], int);					      //2
void GetBinaryRelation(int binaryRelation[MAXX], int&);  	 	    	  //1.1
void DisplayMatrix(int adjacencyMatrix[][MAX], int);             	      //2.1
void FindIsolatedNodes(int adjacencyMatrix[][MAX], int);           	      //2.2
void DetermineNodeDegree(int adjacencyMatrix[][MAX], int);                //2.3
void FindEulerPath(int adjacencyMatrix[][MAX], int);             	      //2.4
void AdjacentNodeCheck(int adjacencyMatrix[][MAX]);               	      //2.5


//*****************************************************************************
//0: Main
int main()
{
	//Declare variables.
	int	numberOfNodes;
	int adjacencyMatrix[MAX][MAX];

	//Function calls.
	GenerateAdjacencyMatrix(adjacencyMatrix, numberOfNodes);
	DisplayMenu(adjacencyMatrix, numberOfNodes);

  return 0;
}


//*****************************************************************************
//1: Generate adjacency matrix consistent with user input.
void GenerateAdjacencyMatrix(int adjacencyMatrix[][MAX], int &numberOfNodes)
{
	int binaryRelationLength;
	int binaryRelation[MAXX];

	cout << "Enter number of nodes: ";
	cin  >> numberOfNodes;

	for(int i = 0; i < numberOfNodes; i++)
		for(int j = 0; j < numberOfNodes; j++)
			adjacencyMatrix[i][j] = 0;

	GetBinaryRelation(binaryRelation, binaryRelationLength);

	//If parallel arcs or loops are permitted, change "= 1" to "+= 1" below.
	for(int i = 0; i < binaryRelationLength; i += 2)
	{
		adjacencyMatrix[binaryRelation[i]][binaryRelation[i + 1]] = 1;
		adjacencyMatrix[binaryRelation[i + 1]][binaryRelation[i]] = 1;
	}

    cout << '\n';

	return;
}


//*****************************************************************************
//2: Display interactive menu for user.
void DisplayMenu(int adjacencyMatrix[][MAX], int numberOfNodes)
{
	int menuChoice;

	do
	{
		cout << "//////////////////////////MENU//////////////////////////"
			   << endl
			   << "Please make a selection from the options below: " << endl
			   << "	1: Print the adjacency matrix" << endl
			   << "	2: Determine if there are any isolated nodes" << endl
			   << "	3: Determine the degree of a node" << endl
			   << "	4: Determine if an Euler path exists" << endl
			   << "	5: Determine if one node is adjacent to another" << endl
			   << "	6: Quit" << endl
			   << "////////////////////////////////////////////////////////"
			   << endl << "Choice: ";
		cin  >> menuChoice;

		switch(menuChoice)
		{
			case 1:
				DisplayMatrix(adjacencyMatrix, numberOfNodes);
				break;
			case 2:
				FindIsolatedNodes(adjacencyMatrix, numberOfNodes);
				break;
			case 3:
				DetermineNodeDegree(adjacencyMatrix, numberOfNodes);
				break;
			case 4:
				FindEulerPath(adjacencyMatrix, numberOfNodes);
				break;
			case 5:
				AdjacentNodeCheck(adjacencyMatrix);
				break;
		}

	}while(menuChoice < 6);

	cout << endl << "Goodbye" << endl;

	return;
}


//*****************************************************************************
//1.1: Places all numbers entered by user into an array for use in generating
//     the adjacency array.
void GetBinaryRelation(int binaryRelation[MAXX], int &binaryRelationLength)
{
	int  number1,
	     number2;
	char wasteCollect;

	binaryRelationLength = 0;

	cout << "Enter a binary relation:\n";

	cin  >> wasteCollect;                                 // {
	for(int i = 0; wasteCollect != '}'; i += 2, binaryRelationLength += 2)
	{
		cin >> wasteCollect;                                // (
		cin >> number1;                                     // Collect number1.
		binaryRelation[i]     = number1 - 1;
		cin >> wasteCollect;                                // ,
		cin >> number2;                                     // Collect number2.
		binaryRelation[i + 1] = number2 - 1;
		cin >> wasteCollect;                                // )
		cin >> wasteCollect;                                // , or } at the end.
	}
	cin.clear();                                          // Rid istream of any
                                                        // undesirable trash.

	return;
}


//*****************************************************************************
//2.1: Displays the adjacency matrix for the user.
void DisplayMatrix(int adjacencyMatrix[][MAX], int numberOfNodes)
{
	int newLineTracker = 0;

	cout << endl;
	for(int i = 0; i < numberOfNodes; i++)
	{
		for(int j = 0; j < numberOfNodes; j++)
		{
			newLineTracker++;
			cout << adjacencyMatrix[i][j] << " ";
			if(newLineTracker%numberOfNodes == 0)
				cout << endl;
		}
	}
	cout << endl;

	return;
}


//*****************************************************************************
//2.2: Searches the adjacency matrix for isolated nodes then displays them.
void FindIsolatedNodes(int adjacencyMatrix[][MAX],int numberOfNodes)
{
	int numberOfAdjacentNodes = 0;

	cout << endl;
	for(int i = 0; i < numberOfNodes; i++)
	{
		for(int j = 0; j < numberOfNodes; j++)
		{
			if(adjacencyMatrix[i][j] != 0 || adjacencyMatrix[j][i] != 0)
			{
				numberOfAdjacentNodes++;
				goto checkNext;
			}
		}

		cout << "Node " << i + 1 << " is an isolated node." << endl;
		checkNext: ;
	}

	if(numberOfAdjacentNodes == numberOfNodes)
		cout << "There are no isolated nodes in this graph." << endl;
	cout << endl;

	return;
}


//*****************************************************************************
//2.3: Asks user to input a node and displays the degree of said node.
void DetermineNodeDegree(int adjacencyMatrix[][MAX], int numberOfNodes)
{
	int node,
		  sum = 0;

	cout << endl << "Enter the node you would like to check: ";
	cin  >> node;

	cout << endl;
	for(int i = 0; i < numberOfNodes; i++)
	{
		sum += adjacencyMatrix[node - 1][i];
		if(adjacencyMatrix[node-1][i] == 0)
			sum += adjacencyMatrix[i][node - 1];
	}
  if(adjacencyMatrix[node-1][node-1] == 1)
    sum++;

	cout << "The degree of node " << node << " is " << sum << endl << endl;

	return;
}


//*****************************************************************************
//2.4: Determines if an Euler path exists in the graph corresponding to the
//     adjacency matrix.
void FindEulerPath(int adjacencyMatrix[][MAX], int numberOfNodes)
{
	int numberOfOddNodes = 0,
		  degree;

	for(int i = 0; numberOfOddNodes < 3 && i < numberOfNodes; i++)
	{
		degree = 0;
		for(int j = 0; j < numberOfNodes; j++)
		{
			degree += adjacencyMatrix[i][j];
			if(adjacencyMatrix[i][j] == 0)
				degree += adjacencyMatrix[j][i];
          if(i == j && adjacencyMatrix[i][j] == 1)
            degree++;
		}
		if(degree%2 != 0)
			numberOfOddNodes++;
	}

	if(numberOfOddNodes > 2)
		cout << endl << "An Euler Path does not exist in the graph." << endl
	       << endl;
	else
		cout << endl << "An Euler Path exists in the graph." << endl << endl;

	return;
}


//*****************************************************************************
//2.5: Asks user to input two nodes, then alerts the user as to whether the
//     nodes are adjacent or not.
void AdjacentNodeCheck(int adjacencyMatrix[][MAX])
{
	int node1,
  		node2;

	cout << "Input two nodes to check for adjacency: ";
	cin  >> node1 >> node2;

	cout << endl;
	if(adjacencyMatrix[node1 - 1][node2 - 1] > 0 ||
	  adjacencyMatrix[node2 - 1][node1 - 1] > 0)
 		cout << "Node " << node1 << " is adjacent to node " << node2 << endl
	       << endl;
	else
		cout << "Node " << node1 << " is NOT adjacent to node " << node2
		     << endl << endl;
	return;
}
