#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include "SyntacticalAnalyzer.h"

using namespace std;

SyntacticalAnalyzer::SyntacticalAnalyzer (char * filename)
{
	lex = new LexicalAnalyzer (filename);
	token_type t;
	while ((t = lex->GetToken()) != EOF_T)
	{
		//TODO:
		// Should be able to write to a file?
		//
		// cout << "t: " << t << endl << endl;
		// get a token
		
		// write its name to the .p1 file
		// write the corresponding lexeme to the .p1 file
	}
}

SyntacticalAnalyzer::~SyntacticalAnalyzer ()
{
	delete lex;
}
