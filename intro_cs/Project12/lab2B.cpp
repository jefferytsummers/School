#include <iostream>
#include <iomanip>

using namespace std;

const float CONVERSION_RATE = 0.87;

int main()
{
	cout << "Enter amount of US Dollar you want to conver : $ ";
	
	float usd;
	
	cin >> usd;
	
	cout << fixed << setprecision(2);
	
	cout << "You entered $" << usd << endl << endl << "1 dollar = 0.87 EUR"
	<< endl << usd << " US Dollar is equivalent to " << CONVERSION_RATE*usd
	<< " EUR" << endl;
	
	return 0;
}
