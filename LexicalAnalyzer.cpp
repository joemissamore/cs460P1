#include <iomanip>
#include <cstdlib>
#include "LexicalAnalyzer.h"

#include "Table.hpp"

using namespace std;

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
	
	// token = GetToken();
	
			
}

LexicalAnalyzer::~LexicalAnalyzer ()
{
	// This function will complete the execution of the lexical analyzer class
	linenum = 0;
	input.close();
	listingFile.close();
	tokenFile.close();
}

token_type LexicalAnalyzer::GetToken ()
{	
	
	int col;
	int state;
	int prevState;
	//TODO: Implement with syntactical analyzer in control
	// while (getline(input, line))


	/* If the line is empty then its the first time
		the function has been called.
		If the pos >= line.length() then 
		we need to grab a newline*/
	if (line == "" || pos >= line.length()) {

		/* If its a new line we need to burn it */
		char c;
		while (input.get(c)) {
			if (c != '\n') {
				/* Put the char back */
				input.unget();
				break;
			}
		}

		/* EOF_T */
		if (input.eof()) {
			return EOF_T;
		}

		getline(input, line);
		pos = 0;
		linenum++;
		// cout << "line: " << line << endl;
	}
		col = 0;
		state = 0;
		prevState = 0;
		// 
		while (pos < line.length()) {

			/* Cause all these checks arent necessary for whitespace 
				we are going to burn it here */
			for(; pos < line.length() && (line[pos] == ' '); pos++);


			


			/* If not STRLIT_T we need to analyze it further */
			if (line[pos] != '"') {
				for (; pos < line.length() && line[pos] != ' '; pos++) {
					// cout << "pos (beginning of loop): " << pos << endl;
					
					col = getCol(line[pos], state);
					// cout << "col: " << col << endl;
					if (col == -1) { 
						state = ERR; 
					}
					else { 
						state = tableDriver[state][col]; 
					}
					// cout << "state: " << state << ", on: " << line[pos] << endl;
					/* state 7 is known as the predicate state and is one
						of the few states that needs additional attention */
					if (state == 7) { 
						/* Checks if the lexeme is a predicate */
						token_type ttype = PredicateProcessor(lexeme + line[pos]);
						if (ttype == ERROR_T) {
							state = prevState;
							pos--; // need to back up
						}
						else { // its a valid predicate
							/* So we will append the current char */
							lexeme += line[pos];
						}
						break;
					}
					/* If the current state is ERR and the 
						lexeme is empty then this is the 
						error causing char. */
					else if (state == ERR && lexeme == "") {
						lexeme += line[pos];
						break;
					}
					/* If the current state is ERR and the 
						lexeme currently has valid chars in
						in it. That lexeme needs to be acessed
						and the error causing char needs to be
						reevaluated */
					else if(state == ERR) { 
						state = prevState;
						pos--;
						break;
					}
					/* If all is good, well we are going to 
						continue on. */
					else {
						lexeme += line[pos];
					}
					prevState = state;

				} // end for

				// If a quote is encountered
			// then it must be a STRLIT_T
			
			} else if (line[pos] == '"') {
				// cout << "STRLIT" << endl;
				lexeme = line[pos];
				pos++; // need to increment past the double quote or
						// the coming for loop wont exec.
				for( ; pos < line.length() && line[pos] != '"'; pos++ ) {
					lexeme += line[pos];
				}
				lexeme += '"';
				/*STRLIT_T*/
				state = 12;
			}
			token = GetTokenType(state);


			cout << setw(20) << left << GetTokenName(token) << lexeme << endl;
			tokenFile << setw(20) << left << GetTokenName(token) << lexeme << endl;
			
			lexeme = ""; // reset lexeme
			pos++; // increment past the position of where the for loop left off.
			state = 0; // reset the state

			// cout << "line: " << line << endl;


			return GetTokenType(state);

		}		
	// }
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


	// Arithmetic
	/* If in state 6 also need to check if instead of 
		being a keyword it may be an arithmetic operator*/
	PKW["modulo"] = MODULO_T;
	PKW["round"] = ROUND_T;

	if (PKW[lex] != 0) {
		return PKW[lex];
	}
	// If its not a keyword or arithmetic
	// then it must be an IDENT_T
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

	if (PKW[lex] != 0) {
		return PKW[lex];
	}

	
	return ERROR_T; 
}

token_type LexicalAnalyzer::GetTokenType(int state) {


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