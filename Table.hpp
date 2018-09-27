#ifndef TBL_HPP
#define TBL_HPP

#include <stdio.h>
#include <ctype.h>
#include <map>

using namespace std;

// SYMBOLS,ALPHA - {c},ALPHA,DIGIT,_,"ALPHA - {a,d}",c,a,d,r,?,"ALPHA - {d,r}",.,+,-,"""",>,<,=,/,*,(,),'




enum symbols {
    ALPHA_NOT_C, // 
    ALPHA, //
    DIGIT, //
    UNDERSCORE, //
    ALPHA_NOT_A_D, // 
    CHAR_C,
    CHAR_A,
    CHAR_D,
    CHAR_R,
    QUESTION_MARK, //
    ALPHA_NOT_D_R, // "ALPHA - {d,r}" // 
    DOT, //
    PLUS, //
    MINUS, //
    DOUBLE_QUOTE, //
    GREATER_THAN,//
    LESS_THAN, //
    EQUAL, //
    DIVISION, //
    MULTIPLY, //
    OPEN_PAREN, //
    CLOSE_PAREN, //
    SINGLE_QUOTE, //

    ERR = -1
};

int getCol(char c, int state) {

    // Attempting to handle special cases for state 0
    if(state == 0) {
        if (isalpha(c) && c != 'c') {
            return ALPHA_NOT_C;
        }
        else if (c == 'c') {
            return CHAR_C;
        }
    }

    if (state == 1) {
        if (isalpha(c) && c != 'a' && c != 'd') {
                return ALPHA_NOT_A_D;
        }
        else if (c == 'a') {
            return CHAR_A;
        }
        else if (c == 'd') {
            return CHAR_D;
        }
    }

    if (state == 2) {
        if (isalpha(c) && c != 'd' && c != 'r') {
            return ALPHA_NOT_D_R;
        }
        else if (c == 'd') {
            return CHAR_D;
        }
        else if (c == 'r'){
            return CHAR_R;
        }
    }


    
    switch(c) {
        case '_':
            return UNDERSCORE; 
            
        case '?':
            return QUESTION_MARK;

        case '.':
            return DOT;

        case '+':
            return PLUS;
        
        case '-':
            return MINUS;

        case '"':
            return DOUBLE_QUOTE;

        case '>':
            return GREATER_THAN;
        
        case '<':
            return LESS_THAN;

        case '=':
            return EQUAL;

        case '/':
            return DIVISION;

        case '*':
            return MULTIPLY;

        case '(':
            return OPEN_PAREN;
        
        case ')':
            return CLOSE_PAREN;
        
        case '\'':
            return SINGLE_QUOTE;

        default:
           if (isalpha(c)) {
               return ALPHA;
           }
            else if (isdigit(c)) {
                return DIGIT;
            }
    }

    return -1; // ERR
}


static int tableDriver[][24] = {
// states 
// 0-3
{6,ERR,4,ERR,ERR,1,ERR,ERR,ERR,ERR,ERR,10,9,8,11,14,16,20,18,19,21,22,23},
{ERR,ERR,6,6,6,ERR,2,2,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR},
{ERR,ERR,6,6,ERR,ERR,ERR,2,3,ERR,6,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR},
{ERR,6,6,6,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR},
// 4-8
{ERR,ERR,4,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,5,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR},
{ERR,ERR,5,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR},
{ERR,6,6,6,ERR,ERR,ERR,ERR,ERR,7,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR},
{ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR},
{ERR,ERR,4,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,5,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR},
// 9 - 14
{ERR,ERR,4,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,5,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR},
{ERR,ERR,5,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR},
{ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,12,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR},
{ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR},
{ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR},
{ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,15,ERR,ERR,ERR,ERR,ERR},
// 15 - 19
{ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR},
{ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,17,ERR,ERR,ERR,ERR,ERR},
{ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR},
{ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR},
{ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR},
// 20-23
{ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR},
{ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR},
{ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR},
{ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR}
};







#endif