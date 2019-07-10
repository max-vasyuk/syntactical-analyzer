#ifndef LEKS_H
#define LEKS_H

enum leks_states {
	BEGIN, IF, SPACE1, ID1, SPACE2, THEN, SPACE3, ID2, SPACE4, COLON_EQUAL, NAME1,
	OBRACKET1, ID3, CBRACKET1, ELSE, SPACE5, NAME2, OBRACKET2, SIGN_INT, CBRACKET2, SPACE6, SEMICOLON
};

struct Token { string input_string, leks; };

string func_analyze(char[], string[], int);
void token_to_string(string*, Token*);
int parse_translit_result(string, char[], string[]);
int state_begin(char[], string[], int*, int*, Token*);
int state_if(char[], string[], int*, int*, Token*, string = "");
int state_space1(char[], string[], int*, int*, Token*);
int state_id1(char[], string[], int*, int*, Token*, string = "");
int state_space2(char[], string[], int*, int*, Token*);
int state_then(char[], string[], int*, int*, Token*, string = "");
int state_space3(char[], string[], int*, int*, Token*);
int state_id2(char[], string[], int*, int*, Token*, string = "");
int state_space4(char[], string[], int*, int*, Token*);
int state_colon_and_equal(char[], string[], int*, int*, Token*, string = "");
int state_name1(char[], string[], int*, int*, Token*, string = "");
int state_id3(char[], string[], int*, int*, Token*, string = "");
int state_cbracket1(char[], string[], int*, int*, Token*);
int state_space5(char[], string[], int*, int*, Token*);
int state_semicolon(char[], string[], int*, int*, Token*);
int state_else(char[], string[], int*, int*, Token*, string = "");
int state_space6(char[], string[], int*, int*, Token*);
int state_name2(char[], string[], int*, int*, Token*, string = "");
int state_sign_and_int(char[], string[], int*, int*, Token*, string = "");
int state_cbracket2(char[], string[], int*, int*, Token*);


#endif