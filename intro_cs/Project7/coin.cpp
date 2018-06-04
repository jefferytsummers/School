#include <iostream> 
#include <stdlib.h>
#include <ctime>

using namespace std;

int main()
{
	//Declaring variables.
	int coin,
	    count,
	    node;
	
	//Seeding srand()
	srand(time(0));
	
	//Initializing variables.
	coin  = rand() % 2;
	count = 0;
	node  = 0;
	
	/*
	  Coin flipping simulation, using node == 3 as a sentinel value. Heads and 
	  tails based on parity of randomly generated number, where even corresponds
	  to heads and odd corresponds to tails.
	*/
	while (node != 3)
	{
		count++;
		if (coin == 0)
			{
				cout << "Head" << endl;
				node++;
			}
		else
			{
				cout << "Tail" << endl;
				node = 0;
			}
		coin = rand() % 2;
	}
	
	//Displays how many coin flips it took to obtain 3 consecutive heads.
	cout << "It took " << count << " flips to get 3 consecutive heads."
		 << endl;
	return 0;
}
