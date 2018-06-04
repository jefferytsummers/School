//Author:      Ryan Florida (rjf2u)
//Professor:   Dr. Phillips
//Program:     OLA1
//Description: This is an implementation of the A* search algorithm for the
//             8 puzzle prolem.

#include <iostream>
#include <vector>
#include <math.h>
#include <limits.h>
#include <cstdlib>
#define inf INT_MAX

using std::vector;
using std::cin;
using std::cout;
using ::pow;

using namespace std;

typedef unsigned int uint;

const uint moves[36]     = {		   //0			 //1             //2
							1, 3, inf, inf, 0, 2, 4, inf, 1, 5, inf, inf,
									   //3			 //4			 //5
							0, 4, 6, inf,     1, 3, 5, 7,   2, 4, 8, inf,
									   //6           //7             //8
							3, 7, inf, inf, 4, 6, 8, inf, 5, 7, inf, inf
						   };

const uint distances[81] = {0, 1, 2, 1, 2, 3, 2, 3, 4, 1, 0, 1, 2, 1, 2, 3, 2,
                            3, 2, 1, 0, 3, 2, 1, 4, 3, 2, 1, 2, 3, 0, 1, 2, 1,
                            2, 3, 2, 1, 2, 1, 0, 1, 2, 1, 2, 3, 2, 1, 2, 1, 0,
                            3, 2, 1, 2, 3, 4, 1, 2, 3, 0, 1, 2, 3, 2, 3, 2, 1,
                            2, 1, 0, 1, 4, 3, 2, 3, 2, 1, 2, 1, 0};

uint goal[9]             = {0, 1, 2, 3, 4, 5, 6, 7, 8};


//Forward declaration of Node struct.
struct Node;

//Aliases.
typedef vector<Node *>::iterator         iter;     //Vector iterator.
typedef vector<Node *>::reverse_iterator r_iter;   //Vector reverse iterator.
typedef uint                             Board[9]; //Alias for board.


//#############################################################################
//Node struct.
struct Node
{
	//public properties.
	uint  pathcost,       // pathcost from root
	      heuristicCost,  // heuristic
	      totalCost,      // totalCost
	      move,           // where piece moved
	      numchildren,    // number of node children
	      depth;          // depth of node
	Board currentState;   // state
	Node  *children[4],   // children pointer
	      *parent;        // parent pointer

	//Node constructor.
	Node(uint moves)
	:parent(NULL), move(-inf), numchildren(0), heuristicCost(0), pathcost(0),
	 totalCost(0), depth(0)
	{
		for(uint i = 0; i < 9; ++i)
			currentState[i] = i;

		for(uint i = 0; i < moves; ++i)
			children[i] = NULL;
	}

};

//#############################################################################
//StateSpace class.
class StateSpace {

	public:
		//StateSpace user-defined constructor.
		StateSpace(uint);

		//StateSpace methods
		void  Solve();
		Node* Create(Node *, uint&);
		uint  DuplicateCheck(Node *);
		void  Initialize(Board&);
		void  Expand(Node *);
		void  PrintSolution(vector<Node *>);
		void  MakeChildren(Node *);
		void  PrintBoard(Board&);
		bool  IsGoal(Node *);
		uint  Heuristic(uint&, Node *);
		void  AddToFrontier(Node *);
		void  SetAttributes(Node *);
		uint  SetDepth(Node *, uint);
		void  Finished(Node *);
		void  Swap(Board&, uint, uint);
		void  GenerateSolution(vector<Node *> &, Node *);

	private:
		uint           startstate[9],     //Starting state.
		               numOfMoves,		  //depth of soltuion.
		               choiceOfHeuristic, //Store heuristic choice.
		               visited;			  //Store number of visited/expanded.
		vector<Node*>  frontier,		  //Frontier.
		               solutionToPrint;   //Solution vector.
		bool           goalIsReached;	  //True if goal is reached.
};


//*****************************************************************************
//Constructor.
StateSpace::StateSpace(uint h)
:numOfMoves(4), choiceOfHeuristic(h), visited(0), goalIsReached(false)
{
	//Read in initial state from standard input.
	for(uint i = 0; i < 9; ++i)
		cin >> startstate[i];
}


//*****************************************************************************
//Swap values.
void StateSpace::Swap(Board& board, uint index1, uint index2)
{
	uint temp     = board[index1];
	board[index1] = board[index2];
	board[index2] = temp;
}


//*****************************************************************************
//Returns selected heuristic.
uint StateSpace::Heuristic(uint& chosenHeuristic, Node *node)
{
	uint heuristic = 0;
	switch(chosenHeuristic)
	{

		case 0: //Uniform Cost Search
			return 0;
			break;

		case 1: //Displaced Tiles
			for(uint i = 0; i < 9; ++i)
				if(node->currentState[i] != goal[i])
					++heuristic;

			return heuristic;
			break;

		case 2: //Manhattan Distance
			for(uint i = 0; i < 9; ++i)
				heuristic += distances[i*9 + node->currentState[i]];

			return heuristic;
			break;

		case 3: //Tweaked Manhattan Distance.
		{
			uint additionalError = 0;

			for(uint i = 0; i < 9; ++i)
				heuristic += distances[i*9 + node->currentState[i]];

			for(uint i = 0; i < 8; ++i)
				if((node->currentState[i] + 1) != node->currentState[i + 1])
					++additionalError;

			if(node->currentState[8] != goal[8])
				++additionalError;

			heuristic += additionalError;

			return heuristic;
			break;
		}
	}
	return 0;
}


//*****************************************************************************
//Solve the puzzle.
void StateSpace::Solve()
{
	//Create root.
	Node* root = new Node(numOfMoves);

	//Initialize the root.
	Initialize(root->currentState);
	//Goal-check root node.
	if(IsGoal(root))
		Finished(root);
	//Make roots cost infinite to prevent back-tracking.
	root->totalCost = inf;
	//Add root to Frontier.


	AddToFrontier(root);

	while(!goalIsReached)
		Expand(root);

}


//*****************************************************************************
//Set input node to starting state.
void StateSpace::Initialize(Board& state)
{
	for(uint i = 0; i < 9; ++i)
		state[i] = startstate[i];
}


//*****************************************************************************
//When goal is reached, display states and generate the optimal path.
void StateSpace::Finished(Node *node)
{
	cout << "V=" << visited << "\nN=" << frontier.size() << "\nd="
       << node->depth << "\nb=" << pow(frontier.size(), 1.0/node->depth)
		   << "\n\n";

	goalIsReached = true;
	GenerateSolution(solutionToPrint, node);
}


//*****************************************************************************
//Add to frontier in appropriate manner.
void StateSpace::AddToFrontier(Node *node)
{
	iter itr;
	uint size = frontier.size();
	size /= 2;
	cout << size << "\n";

	for(itr = frontier.begin();itr!=frontier.end();itr++)
		if(node->totalCost <= (*itr)->totalCost)
			break;


	frontier.insert(itr,node);
}


//*****************************************************************************
//Expand selected node on frontier.
void StateSpace::Expand(Node *node)
{
	Node* temp;

	//If node is NULL, then frontier is empty and there is no solution.
	if(!node)
	{
		cout << "No solution.\n";
		exit(1);
	}

	//If the current node has any NULL children, then spawn children.
	if(!(node->children[0] || node->children[1] || node->children[2]
		 || node->children[3]))
		MakeChildren(node);
	//If the current node is not NULL, close it.
	else if(node)
		{
			temp = frontier.front();
			frontier.erase(frontier.begin());
			//Goal-check the next node on the frontier.
			if(IsGoal(temp))
			{
				Finished(frontier.front());
				if(goalIsReached)
					return;
			}
			//Expand the next-in-line on the frontier if it is not the goal.
			Expand(temp);
		}
}


//*****************************************************************************
//Spawn children.
void StateSpace::MakeChildren(Node *node)
{
	Node* child;

	for(uint i = 0; i < numOfMoves; ++i)
	{
		//Create i'th child.
		child = Create(node, i);

		//If i'th child is invalid, then set the i'th child pointer of the
		//current node to NULL and go on to next iteration.
		if(!child)
		{
			node->children[i] = NULL;
			continue;
		}

		//Check if child is the goal.
		if(IsGoal(child))
		{
			Finished(child);
			if(goalIsReached)
				return;
		}

		//Assuming the child exists, set the current node's i'th child pointer
		//to the new child object and increment the node's child count.
		node->children[i] = child;
		node->numchildren++;

		// add to frontier if not repeated
		if(DuplicateCheck(child) != inf)
			AddToFrontier(child);
	}
}


//*****************************************************************************
//Check for duplicate nodes.
uint StateSpace::DuplicateCheck(Node *node)
{
	Node* ancestor = node->parent->parent;

	//If node's ancestor is NULL, then return 0.
	if(!ancestor)
		return 0;
	//If returning 1, then we have a sibling of an existing node.
	else
		for(uint i = 0; i < 9; ++i)
			if(ancestor->currentState[i] != node->currentState[i])
				return 1;

	//Node is a duplicate.
	return inf;
}


//*****************************************************************************
//Recursively find depth of node.
uint StateSpace::SetDepth(Node *node, uint depth)
{
	//Base case: current node's parent is NULL.
	if(!node->parent)
		return ++depth;

	//Alternative case: current node's parent is not NULL.
	return SetDepth(node->parent, ++depth);
}


//*****************************************************************************
//Make the tree of possiblilites.
Node* StateSpace::Create(Node *node, uint& index)
{
	uint  i,
	      blank,
	      nextMove;
	Node* child;

	//Search board for blank.
	for(i = 0; i < 9; ++i)
		if(!node->currentState[i])
			break;

	//Identify valid moves.
	blank    = i;
	nextMove = moves[blank*4 + index];

	//If move is invalid, return NULL.
	if(nextMove == inf)
		return NULL;

	//If move is valid, then create a child indicative of that move.
	child         = new Node(numOfMoves);
	child->parent = node;

	//Set depth of child.
	child->depth  = SetDepth(node, 0);

	//Copy parent's board configuration to child.
	for(i = 0; i < 9; ++i)
		child->currentState[i] = node->currentState[i];

	//Make valid move found above.
	child->currentState[blank]     = node->currentState[nextMove];
	child->currentState[nextMove]  = node->currentState[blank];
	child->move                    = node->currentState[nextMove];

	//Set child attributes.
	SetAttributes(child);

	return child;
}


//*****************************************************************************
//Goal-check the input node.
bool StateSpace::IsGoal(Node *node)
{
	for(uint i = 0; i < 9; ++i)
		if(node->currentState[i] != goal[i])
			return false;

	return true;
}


//*****************************************************************************
//Use chosen heuristic to set node attributes.
void StateSpace::SetAttributes(Node *node)
{
	//Set path cost.
	node->pathcost      = node->depth;
	//Set heuristic cost.
	node->heuristicCost = Heuristic(choiceOfHeuristic, node);
	//Set total cost.
	node->totalCost     = node->pathcost + node->heuristicCost;

	//Increment number of visited/expanded nodes.
	++visited;
}


//*****************************************************************************
//This method recursively generates the solution to the puzzle.
void StateSpace::GenerateSolution(vector<Node *> &vec, Node* node)
{
	//Base case: node == NULL.
	if(!node)
	{
		PrintSolution(vec);
		return;
	}

	//Alternative cases: node != NULL
	//If move is valid, add the node to the print list.
	if(node->move != -inf)
		vec.push_back(node);

	//Recursively call on parent pointer.
	GenerateSolution(vec, node->parent);
}


//*****************************************************************************
//Print the solution path.
void StateSpace::PrintSolution(vector<Node *> vector)
{
	//Print the starting configuration.
	PrintBoard(startstate);
	//Print optimal path.
	for(r_iter it = vector.rbegin(); it != vector.rend(); ++it)
		PrintBoard((*it)->currentState);
}


//*****************************************************************************
//Print board in solution path.
void StateSpace::PrintBoard(Board& state)
{
	cout << '\n';
	for(uint i = 0; i < 9; ++i)
	{
		cout << state[i] << " ";
		if(i%3 == 2)
			cout << '\n';
	}
	cout << '\n';
}


//*****************************************************************************
//0: Main
int main(int argc, char* argv[])
{
	StateSpace _8slide(atoi(argv[1]));

	_8slide.Solve();

	return 0;
}
