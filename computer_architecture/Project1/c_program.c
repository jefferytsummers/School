/*
 Author:     Ryan Florida
 Course:     CSCI 3130
 Assignment: OLA1
 Date:       1/20/2017
*/

//Declare Haiku function whose argument shall be a single string.
void DisplayHaiku(const char* haiku);

//Declare Main.
int main()
{
	//Create Haiku string to pass into the function DisplayHaiku function.
	const char* haiku = "Quaternionic Haiku, by Ryan Florida\nThe quaternion.\nImaginary vector,\nwith real part scalar.\n";
	
	DisplayHaiku(haiku);

	return 0;
}
