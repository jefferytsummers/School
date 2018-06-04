/*
  Simple integer arithmetic calculator according to the following BNF
  exps		--> exp | exp NEWLINE exps
  exp		--> term {addop term}
  addop		--> + | -
  term		--> factor {mulop factor}
  mulop		--> * | /
  factor	--> ( exp ) | INT
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include "tokens.h"
#include "FlexLexer.h"

using namespace std;

string toknames[] = {
"INT", "LPAREN", "RPAREN", "PLUS", "MINUS", "TIMES", "DIVIDE", "NEWLINE"
};

string tokname(int tok) {
  return tok<257 || tok>264 ? "BAD_TOKEN" : toknames[tok-257];
}

yyFlexLexer			lexer;
YYSTYPE				yylval;

int		nextToken;	//global variable stores the token to be processed

void readNextToken( void ); //read the next token into the variable nextToken

void exps( void );	//process all expressions in the input
int  exp( void );	//returns the integer value of an expression
int term ( void );	//returns the integer value of an term
int factor( void );	//returns the integer value of an factor

//If the next token matches expectedToken, read the next token and return true
//otherwise, print an error message and return false
bool match( int expectedToken );

//print the error message
void error( string errorMsg );

//skip the rest of the line
void skipline( void );

int main(int argc, char **argv) {
	ifstream	ifs; 
	
	if (argc!=2) 
	{
		cerr << "usage: " << argv[0] << " filename" << endl;
		return 1;	
	}
	ifs.open( argv[1] );
	if( !ifs ) 
	{
		cerr << "Input file cannot be opened.\n";
        return 0;
	}
	cout << "Lexcial Analysis of the file " << argv[1] << endl;
	
	lexer.switch_streams(&ifs, NULL);

	readNextToken();

	exps();

	system("pause");

	return 0;
}

//print the error message, and
//terminate the program
void error( string errorMsg )
{
	cout << errorMsg << endl;
	exit(1);
}

//skip the rest of the line
void skipline( void )
{
	while( nextToken != NEWLINE && nextToken != 0 )
		readNextToken();
}


//read the next token into the variable nextToken
void readNextToken( void )
{
	nextToken = lexer.yylex();
}

//If the next token is expectedToken, call readNextToken and return true,
//otherwise, print an error message and return false
bool match( int expectedToken )
{
	if ( expectedToken == nextToken )
	{
		readNextToken();
		return true;
	}
	else
		return false;
}

void exps( void )
{
	int		count = 1;
	int		value;

	do 
	{
		try {
			value = exp();
			cout << "expression " << count << " : " << value << endl;
		} catch(runtime_error e) {
			skipline();
			cout << "expression " << count << " :    wrong syntax -- " << e.what() << endl;
		}
		count ++;
	} while ( match(NEWLINE) );
}

//returns the integer value of an expression
int exp( void )
{
	//Call to term function.
	int value = term();

	//Helps program decide which operation, between addition and subtraction, to
	//perform. If neither operation symbol is identified, then an error will be
	//thrown.
	while (nextToken == PLUS || nextToken == MINUS)
	{
		switch (nextToken)
		{
			case PLUS: 
				readNextToken();
				value += term();
				break;
			case MINUS: 
				readNextToken();
				value -= term();
				break;
			default:
				throw runtime_error("Token PLUS or MINUS expected.");
		}
	}
	
	return value;


}

int term ( void )
{
	//Call to factor function.
	int value = factor();

	//Helps program decide which operation, between multiplication and division,
	//to perform. If neither operation symbol is identified, then an error will
	//be thrown.
	while (nextToken == TIMES || nextToken == DIVIDE)
	{
		switch (nextToken)
		{
			case TIMES: 
				readNextToken();
				value *= factor();
				break;
			case DIVIDE: 
				readNextToken();
				value /= factor();
				break;
			default:
				throw runtime_error("Token TIMES or DIVIDE expected.");
		}
	}

	return value;
}

int factor( void )
{
	//Local variable declaration.
	int value;

	//We expect the first value to be read in to either be "(" or an integer.
	//If it so happens that neither of the aforementioned are read in first,
	//then an error will be thrown.
	switch (nextToken)
	{
		case LPAREN:
			readNextToken();
			value = exp();
			//If a ")" is not read in to match the "(", then an error will
			//be thrown.
			if (!match(RPAREN))
				throw runtime_error("Token RPAREN expected.");
			break;
		case INT:
			value = yylval.ival;
			readNextToken();
			break;
		default:
			throw runtime_error("Token LPAREN or INT expected.");
	}

	return value;
}
