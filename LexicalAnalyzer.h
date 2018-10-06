#ifndef LEX_H
#define LEX_H

#include <iostream>
#include <fstream>

using namespace std;


enum token_type { NONE = -1, 
                    EOF_T, 

					LISTOP_T,
					NUMLIT_T,
					IDENT_T,
					STRLIT_T,

					// Arithmetic
					PLUS_T,
					MINUS_T,
					DIV_T,
					MULT_T,
					MODULO_T,
					ROUND_T,

					// Logical/Relational
					EQUALTO_T,
					GT_T,
					LT_T,
					GTE_T,
					LTE_T,

					// Other
					LPAREN_T,
					RPAREN_T,
					SQUOTE_T,
					ERROR_T,

					// Key words
					IF_T,
					CONS_T,
					COND_T,
					ELSE_T,
					DISPLAY_T,
					NEWLINE_T,
					AND_T,
					OR_T,
					NOT_T,
					DEFINE_T,

					// Predicates
					NUMBERP_T,
					LISTP_T,
					ZEROP_T,
					NULLP_T,
					STRINGP_T,


					
					NUM_TOKENS
};


class LexicalAnalyzer 
{
    public:
	LexicalAnalyzer (char * filename);
	~LexicalAnalyzer ();
	token_type GetToken (); // return a single line
	string GetTokenName (token_type t) const;
	string GetLexeme () const;
	void ReportError (const string & msg);

	
    private:
	ifstream input;
	ofstream listingFile; // .lst file
	ofstream tokenFile;
	ofstream debugFile;
	token_type token;
	string line;
	int linenum;
	int pos;
	string lexeme;
	int errors;

	// Function added after framework
	token_type KeywordProcessor(string lex);
	token_type PredicateProcessor(string lex);
	token_type ProcessSTRLIT_T();
	token_type GetTokenType(int);
};
	
#endif
