#include <iomanip>
#include <cstdlib>
#include "LexicalAnalyzer.h"

#include "Table.hpp"

using namespace std;

/*
	GetToken: to return one token 
		synchronization err
	
	spaces
		Feed in char at a time? 
		
		capture everything up to a space
		try to identify it
		if fails {
			pass each individual char
		}

		ERR - just lexical ERR
		EOF




	id?

*/

static string token_names[] = {	
					"EOF_T",
								

					"LISTOP_T",
					"NUMLIT_T",
					"IDENT_T",
					"STRLIT_T",
					
					// Arithmetic
					"PLUS_T",
					"MINUS_T",
					"DIV_T",
					"MULT_T",
					"MODULO_T",
					"ROUND_T",

					// Logical/Relational
					"EQUALTO_T",
					"GT_T",
					"LT_T",
					"GTE_T",
					"LTE_T",

					// Other
					"LPAREN_T",
					"RPAREN_T",
					"SQUOTE_T",
					"ERROR_T",

					// Key words
					"IF_T",
					"CONS_T",
					"COND_T",
					"ELSE_T",
					"DISPLAY_T",
					"NEWLINE_T",
					"AND_T",
					"OR_T",
					"NOT_T",
					"DEFINE_T",

					// Predicates
					"NUMBERP_T",
					"LISTP_T",
					"ZEROP_T",
					"NULLP_T",
					"STRINGP_T",

					"NUM_TOKENS"



 }; 

LexicalAnalyzer::LexicalAnalyzer (char * filename)
{
	input.open(filename);
	listingFile.open("P1-0.lst");
	tokenFile.open("P1-0.p1");

	linenum = 1;

	while (getline(input, line))
	{
		pos = 0;
		int col = 0;
		int state = 0;
		// 
		while (pos < line.length()) {
			
			// skip over all white spaces
			for(; pos < line.length() && (line[pos] == ' '); pos++);
			if (line[pos] != '"') {
				for (; pos < line.length() && line[pos] != ' '; pos++) {
					col = getCol(line[pos], state);
					state = tableDriver[state][col];
					if (state == 7) { // need to check if its a predicate
						token_type ttype = PredicateProcessor(lexeme + line[pos]);
						if (ttype == ERROR_T) {
							pos--; // need to back up
							break;
						}
					}
					if (state != ERR) {
						lexeme += line[pos];
					}
					else { // its an err
						lexeme += line[pos];
					}

				}
			}
			else if (line[pos] == '"') {
				lexeme = line[pos];
				pos++; // need to increment past the double quote or
						// the coming for loop wont exec.
				for( ; pos < line.length() && line[pos] != '"'; pos++ ) {
					lexeme += line[pos];
				}
				lexeme += '"';
			}

			token = GetToken();
			// This line was printing unexpected tabsG
			cout << setw(20) << left << GetTokenName(token) << lexeme << endl;
			tokenFile << setw(20) << left << GetTokenName(token) << lexeme << endl;
			// printf("%s\t\t%s\n", GetTokenName(token).c_str(), lexeme.c_str());
			
			lexeme = "";
			pos++; // increment past the position of where the for loop left off.
		}

		listingFile << "\t" << linenum++ << ": " << line << endl;
		
		
	}


}

LexicalAnalyzer::~LexicalAnalyzer ()
{
	// This function will complete the execution of the lexical analyzer class
	input.close();
	listingFile.close();
	tokenFile.close();
}

token_type LexicalAnalyzer::GetToken ()
{
	int state = 0;
	int col = 0;
	int tempState;
	int tempCol;
	string tempLex = "";
	// Do don not execute for loop if state is 11
	// State 11 == STRLIT_T
	for (int i=0; i < lexeme.size() && state != ERR && state != 11; i++) {
		col = getCol(lexeme[i], state);
		state = tableDriver[state][col];
		tempLex += lexeme[i];
		// PEEK
		// Peek at the next char and see if it throws an err.
		//TODO: Check to make sure not EOL
		// The only state that needs validation is 
		// 		predicate
		//TODO: If peek reveals a question mark,
		// test to see if it its a predicate
		if (lexeme[i + 1] == '?') {
			token_type ttype = PredicateProcessor(lexeme + lexeme[i + 1]);
			if (ttype == ERROR_T) {
				pos = pos - (pos - i);
				break;
			}

		}


		// Checking for ERR
		// tempCol = getCol(lexeme[i+1], state);
		// tempState = tableDriver[state][tempCol];
		
		// if (tempState == ERR){
		// 	// synchronize pos with i...
		// 	pos = pos - (pos - i);
		// 	lexeme = tempLex;
		// 	cout << "YO, TEMP STATE HAS AN ERR" << endl; 
		// }
	}
	// cout << "state: " << state << endl;
	if (state != ERR) {
		switch (state){
			case 3:
				return LISTOP_T;
			case 6:
				return KeywordProcessor(lexeme);
			case 7:
				return PredicateProcessor(lexeme);
			case 4: 
				return NUMLIT_T;
			case 5: 
				return NUMLIT_T;
			case 9: 
				return PLUS_T;
			case 8:
				return MINUS_T;
			case 18:
				return DIV_T;
			case 19:
				return MULT_T;
			case 20:
				return EQUALTO_T;
			case 21:
				return LPAREN_T;
			case 22:
				return RPAREN_T;
			case 23:
				return SQUOTE_T;
			case 12:
				return STRLIT_T;
			case 14:
				return GT_T;
			case 15:
				return GTE_T;
			case 16:
				return LT_T;
			case 17:
				return LTE_T;
			case 11:
				return STRLIT_T;
		}
	}
	return ERROR_T;
}

string LexicalAnalyzer::GetTokenName (token_type t) const
{
	// The GetTokenName function returns a string containing the name of the
	// token passed to it. 
	return token_names[t];
}

string LexicalAnalyzer::GetLexeme () const
{
	// This function will return the lexeme found by the most recent call to 
	// the get_token function
	return lexeme;
}

void LexicalAnalyzer::ReportError (const string & msg)
{
	// This function will be called to write an error message to a file
}


// Function implementation added after framework
// Logic had to be split up because was returning a predicate as a possible 
// identifier
token_type LexicalAnalyzer::KeywordProcessor(string lex) {
	map<string, token_type> PKW;
	// Keywords
	PKW["if"] = IF_T;
	PKW["cons"] = CONS_T;
	PKW["cond"] = COND_T;
	PKW["else"] = ELSE_T;
	PKW["display"] = DISPLAY_T;
	PKW["newline"] = NEWLINE_T;
	PKW["and"] = AND_T;
	PKW["or"] = OR_T;
	PKW["not"] = NOT_T;
	PKW["define"] = DEFINE_T;

	if (PKW[lex] != 0) {
		return PKW[lex];
	}
	// If its not a keyword then 
	// it must be an IDENT_T
	return IDENT_T;
}

token_type LexicalAnalyzer::PredicateProcessor(string lex) {
	// Predicate
	map<string, token_type> PKW;
	PKW["number?"] = NUMBERP_T;
	PKW["list?"] = LISTP_T;
	PKW["zero?"] = ZEROP_T;
	PKW["null?"] = NULLP_T;
	PKW["string?"] = STRINGP_T;

	// Arithmetic
	PKW["modulo"] = MODULO_T;
	PKW["round"] = ROUND_T;

	if (PKW[lex] != 0) {
		return PKW[lex];
	}

	
	return ERROR_T; 
}