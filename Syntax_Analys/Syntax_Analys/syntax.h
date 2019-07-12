#ifndef SYNTAX_H
#define SYNTAX_H

#include "header.h"

// перечисление состояний конечного автомата
enum syntax_states {
   BEGIN, IF, ID1, THEN, ID2, COLON_EQUAL, NAME1, OBRACKET1, ID3, CBRACKET1,
   ELSE, NAME2, OBRACKET2, SIGN_INT, CBRACKET2, SEMICOLON
};

Token state_begin(string text[], string value[], int *curState, int *ind);
Token state_if(string text[], string value[], int *curState, int *ind);
Token state_id1(string text[], string value[], int *curState, int *ind);
Token state_then(string text[], string value[], int *curState, int *ind);
Token state_id2(string text[], string value[], int *curState, int *ind);
Token state_colon_and_equal(string text[], string value[], int *curState, int *ind);
Token state_name1(string text[], string value[], int *curState, int *ind);
Token state_obracket1(string text[], string value[], int *curState, int *ind);
Token state_id3(string text[], string value[], int *curState, int *ind);
Token state_cbracket1(string text[], string value[], int *curState, int *ind);
Token state_else(string text[], string value[], int *curState, int *ind);
Token state_name2(string text[], string value[], int *curState, int *ind);
Token state_obracket2(string text[], string value[], int *curState, int *ind);
Token state_sign_and_int(string text[], string value[], int *curState, int *ind);
Token state_cbracket2(string text[], string value[], int *curState, int *ind);
Token state_semicolon(string text[], string value[], int *curState, int *ind);

#endif