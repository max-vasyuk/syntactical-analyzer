#ifndef LEKS_H
#define LEKS_H

#include "header.h"

// перечисление состояний конечного автомата
enum leks_states {
	BEGIN, IF, SPACE1, ID1, SPACE2, THEN, SPACE3, ID2, SPACE4, COLON_EQUAL, NAME1,
	OBRACKET1, ID3, CBRACKET1, ELSE, SPACE5, NAME2, OBRACKET2, SIGN_INT, CBRACKET2, SPACE6, SEMICOLON
};

vector<Token> func_analyze(char[], string[], int);
Token state_begin(char[], string[], int*, int*);
Token state_if(char[], string[], int*, int*, string = "");
Token state_space1(char[], string[], int*, int*);
Token state_id1(char[], string[], int*, int*, string = "");
Token state_space2(char[], string[], int*, int*);
Token state_then(char[], string[], int*, int*, string = "");
Token state_space3(char[], string[], int*, int*);
Token state_id2(char[], string[], int*, int*, string = "");
Token state_space4(char[], string[], int*, int*);
Token state_colon_and_equal(char[], string[], int*, int*, string = "");
Token state_name1(char[], string[], int*, int*, string = "");
Token state_id3(char[], string[], int*, int*, string = "");
Token state_cbracket1(char[], string[], int*, int*);
Token state_space5(char[], string[], int*, int*);
Token state_semicolon(char[], string[], int*, int*);
Token state_else(char[], string[], int*, int*, string = "");
Token state_space6(char[], string[], int*, int*);
Token state_name2(char[], string[], int*, int*, string = "");
Token state_sign_and_int(char[], string[], int*, int*, string = "");
Token state_cbracket2(char[], string[], int*, int*);
#endif