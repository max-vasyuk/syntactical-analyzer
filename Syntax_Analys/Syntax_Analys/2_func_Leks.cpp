#include "header.h"
#include "leks.h"

// func_Leks - Ëåêñè÷åñêèé áëîê
//__________________________________________________________________
// ÂÕÎÄ:  string translit_result - ñòğîêà ïîñëå òğàíñëèòåğàöèè
//__________________________________________________________________
// ÂÛÕÎÄ: string result - ğåçóëüòàò ëåêñè÷åñêîãî àíàëèçà
//__________________________________________________________________
string func_Leks(string translit_result) {
	// ïåğåìåííûå äëÿ ğàçáîğà ğåçóëüòàòîâ òğàíñëèòåğàöèè
	char text[80];
	string leks[80];

	// ğåçóëüòàò òğàíñëèòåğàöèè
	int length = parse_translit_result(translit_result, text, leks);

	// âûçîâ ôóíêöèè àíàëèçàòîğà
	return func_analyze(text, leks, length);
}

string func_analyze(char text[], string tr_keys[], int length) {
	int curState = BEGIN, ind = 0;
	string result_string = "";
	Token tkn;

	if (state_begin(text, tr_keys, &curState, &ind, &tkn) == 0)
		token_to_string(&result_string, &tkn);
	else cout << "ÎØÈÁÊÀ";

	if (state_space1(text, tr_keys, &curState, &ind, &tkn) == 0)
		token_to_string(&result_string, &tkn);
	else cout << "ÎØÈÁÊÀ";

	if (state_space2(text, tr_keys, &curState, &ind, &tkn) == 0)
		token_to_string(&result_string, &tkn);
	else cout << "ÎØÈÁÊÀ";

	if (state_space3(text, tr_keys, &curState, &ind, &tkn) == 0)
		token_to_string(&result_string, &tkn);
	else cout << "ÎØÈÁÊÀ";

	if (state_space4(text, tr_keys, &curState, &ind, &tkn) == 0)
		token_to_string(&result_string, &tkn);
	else cout << "ÎØÈÁÊÀ";

	if (state_name1(text, tr_keys, &curState, &ind, &tkn) == 0) {
		token_to_string(&result_string, &tkn);
		tkn.input_string = "(";
		tkn.leks = "ÎÑÊÎÁÊÀ";
		token_to_string(&result_string, &tkn);
	}
	else cout << "ÎØÈÁÊÀ";

	if (state_id3(text, tr_keys, &curState, &ind, &tkn) == 0) {
		token_to_string(&result_string, &tkn);
		tkn.input_string = ")";
		tkn.leks = "ÇÑÊÎÁÊÀ";
		token_to_string(&result_string, &tkn);
	}
	else cout << "ÎØÈÁÊÀ";

	if (state_cbracket1(text, tr_keys, &curState, &ind, &tkn) == 0)
		token_to_string(&result_string, &tkn);
	else cout << "ÎØÈÁÊÀ";

	if (curState != SEMICOLON)
	{
		if (state_space6(text, tr_keys, &curState, &ind, &tkn) == 0) {
			token_to_string(&result_string, &tkn);
			tkn.input_string = "(";
			tkn.leks = "ÎÑÊÎÁÊÀ";
			token_to_string(&result_string, &tkn);
		}
		else cout << "ÎØÈÁÊÀ";

		if (state_sign_and_int(text, tr_keys, &curState, &ind, &tkn) == 0) {
			token_to_string(&result_string, &tkn);
			tkn.input_string = ")";
			tkn.leks = "ÇÑÊÎÁÊÀ";
			token_to_string(&result_string, &tkn);
		}
		else cout << "ÎØÈÁÊÀ";

		if (state_cbracket2(text, tr_keys, &curState, &ind, &tkn) == 0)
			result_string.append("(" + tkn.input_string + ", " + tkn.leks + ")");
		else cout << "ÎØÈÁÊÀ";
	}

	if (ind <= length - 1 && state_semicolon(text, tr_keys, &curState, &ind, &tkn) != 0)
		cout << "ÎØÈÁÊÀ";

	return result_string;
}

void token_to_string(string *str, Token *tkn)
{
	(*str).append("(" + tkn->input_string + ", " + tkn->leks + "), ");
	tkn->input_string = "";
	tkn->leks = "";
}

int parse_translit_result(string translit_result, char text[], string tr_keys[]) {
	// èíäåêñ ğàññìàòğèâàåìîãî ñèìâîëà, èíäåêñ òåêóùåãî ñèìâîëà â
	// ñòğîêå ğåçóëüòàòà òğàíñëèòåğàöèè
	int ind = 0, cur = 1;

	// öèêë ïî ñòğîêå ñ ğåçóëüòàòîì òğàíñëèòåğàöèè äëÿ ñîõğàíåíèÿ 
	// ëåêñåì
	while (cur < translit_result.size()) {
		// çàïîìèíàåì ğàññìàòğèâàåìûé ñèìâîë
		text[ind] = translit_result[cur];

		// öèêëîì ñ÷èòûâàåì ëåêñåìó (îò çàïÿòîé äî ñêîáêè)
		int i = cur + 2;
		for (; translit_result[i] != ')'; i++)
			tr_keys[ind].push_back(translit_result[i]);

		// ïåğåõîä ê ñëåäóşùåìó ñèìâîëó
		cur = i + 4;
		ind++;
	}
	return ind;
}

int state_begin(char symb[], string value[], int* curState, int* ind, Token* tkn) {
	if (*curState == BEGIN) {
		if (value[*ind] == "ÏĞÎÁÅË") {
			*ind++;
			return state_begin(symb, value, curState, ind, tkn);
		}
		if (value[*ind] == "ÁÓÊÂÀ"){
			*curState = IF;
			return state_if(symb, value, curState, ind, tkn);
		}
		return -1;
	}
	return -1;
}

int state_if(char symb[], string value[], int* curState, int* ind, Token* tkn, string curString) {
	if (*curState == IF) {
		if (value[*ind] == "ÁÓÊÂÀ") {
			if (curString == "" && (char)tolower(symb[*ind]) == 'i') {
				curString.push_back(symb[*ind]);
				*ind += 1;
				return state_if(symb, value, curState, ind, tkn, curString);
			}
			if (curString.size() == 1 && (char)tolower(symb[*ind]) == 'f') {
				curString.push_back(symb[*ind]);
				*ind += 1;
				return state_if(symb, value, curState, ind, tkn, curString);
			}
			return -1;
		}
		if (curString.size() == 2 && value[*ind] == "ÏĞÎÁÅË") {
			*curState = SPACE1;
			tkn->input_string = curString;
			tkn->leks = "ÈÄÅÍÒÈÔÈÊÀÒÎĞ";
			return 0;
		}
		return -1;
	}
	return -1;
}

int state_space1(char symb[], string value[], int* curState, int* ind, Token* tkn) {
	if (*curState == SPACE1) {
		if (value[*ind] == "ÏĞÎÁÅË") {
			(*ind)++;
			return state_space1(symb, value, curState, ind, tkn);
		}
		if (value[*ind] == "ÁÓÊÂÀ") {
			*curState = ID1;
			return state_id1(symb, value, curState, ind, tkn);
		}
		return -1;
	}
	return -1;
}

int state_id1(char symb[], string value[], int* curState, int* ind, Token* tkn, string curString) {
	if (*curState == ID1) {
		if (curString != "" && value[*ind] == "ÏĞÎÁÅË")
		{
			*curState = SPACE2;
			tkn->input_string = curString;
			tkn->leks = "ÈÄÅÍÒÈÔÈÊÀÒÎĞ";
			return 0;
		}
		if (value[*ind] == "ÁÓÊÂÀ" || value[*ind] == "ÏÎÄ×ÅĞÊ" || value[*ind] == "ÖÈÔĞÀ" && curString != "")
		{
			curString.push_back(symb[*ind]);
			(*ind)++;
			return state_id1(symb, value, curState, ind, tkn, curString);
		}
		return -1;
	}
	return -1;
}

int state_space2(char symb[], string value[], int* curState, int* ind, Token* tkn)
{
	if (*curState == SPACE2) {
		if (value[*ind] == "ÏĞÎÁÅË") {
			(*ind)++;
			return state_space2(symb, value, curState, ind, tkn);
		}
		if (value[*ind] == "ÁÓÊÂÀ") {
			*curState = THEN;
			return state_then(symb, value, curState, ind, tkn);
		}
		return -1;
	}
	return -1;
}

int state_then(char symb[], string value[], int* curState, int* ind, Token* tkn, string curString)
{
	if (*curState == THEN) {
		if (value[*ind] == "ÁÓÊÂÀ") {
			switch ((char)tolower(symb[*ind])) {
				case 't': if (curString.size() != 0) return -1;
					break;
				case 'h': if (curString.size() != 1) return -1;
					break;
				case 'e': if (curString.size() != 2) return -1;
					break;
				case 'n': if (curString.size() != 3) return -1;
					break;
				default: return -1;
			}
			curString.push_back(symb[*ind]);
			*ind += 1;
			return state_then(symb, value, curState, ind, tkn, curString);
		}
		if (curString.size() == 4 && value[*ind] == "ÏĞÎÁÅË") {
			*curState = SPACE3;
			tkn->input_string = curString;
			tkn->leks = "ÈÄÅÍÒÈÔÈÊÀÒÎĞ";
			return 0;
		}
		return -1;
	}
	return -1;
}

int state_space3(char symb[], string value[], int* curState, int* ind, Token* tkn) {
	if (*curState == SPACE3) {
		if (value[*ind] == "ÏĞÎÁÅË") {
			(*ind)++;
			return state_space3(symb, value, curState, ind, tkn);
		}
		if (value[*ind] == "ÁÓÊÂÀ") {
			*curState = ID2;
			return state_id2(symb, value, curState, ind, tkn);
		}
		return -1;
	}
	return -1;
}

int state_id2(char symb[], string value[], int* curState, int* ind, Token* tkn, string curString) {
	if (*curState == ID2) {
		if (value[*ind] == "ÁÓÊÂÀ" || value[*ind] == "ÏÎÄ×ÅĞÊ" || value[*ind] == "ÖÈÔĞÀ" && curString != "") {
			curString.push_back(symb[*ind]);
			(*ind)++;
			return state_id2(symb, value, curState, ind, tkn, curString);
		}
		if (curString != "" && value[*ind] == "ÏĞÎÁÅË" || value[*ind] == "ÄÂÎÅÒÎ×ÈÅ") {
			if (value[*ind] == "ÏĞÎÁÅË") *curState = SPACE4;
			else *curState = COLON_EQUAL;
			tkn->input_string = curString;
			tkn->leks = "ÈÄÅÍÒÈÔÈÊÀÒÎĞ";
			return 0;
		}
		return -1;
	}
	return -1;
}

int state_space4(char symb[], string value[], int* curState, int* ind, Token* tkn)
{
	if (*curState == SPACE4 || *curState == COLON_EQUAL) {
		if (value[*ind] == "ÏĞÎÁÅË") {
			(*ind)++;
			return state_space4(symb, value, curState, ind, tkn);
		}
		if (value[*ind] == "ÄÂÎÅÒÎ×ÈÅ") {
			*curState = COLON_EQUAL;
			return state_colon_and_equal(symb, value, curState, ind, tkn);
		}
		return -1;
	}
	return -1;
}

int state_colon_and_equal(char symb[], string value[], int* curState, int* ind, Token* tkn, string curString) {
	if (*curState == COLON_EQUAL) {
		if (curString == "" && value[*ind] == "ÄÂÎÅÒÎ×ÈÅ") {
			curString.push_back(symb[*ind]);
			(*ind)++;
			return state_colon_and_equal(symb, value, curState, ind, tkn, curString);
		}
		if (curString.size() == 1 && value[*ind] == "ĞÀÂÍÎ") {
			curString.push_back(symb[*ind]);
			(*ind)++;
			return state_colon_and_equal(symb, value, curState, ind, tkn, curString);
		}
		if (curString.size() == 2){
			if (value[*ind] == "ÏĞÎÁÅË") {
				(*ind)++;
				return state_colon_and_equal(symb, value, curState, ind, tkn, curString);
			}
			if (value[*ind] == "ÁÓÊÂÀ") {
				*curState = NAME1;
				tkn->input_string = curString;
				tkn->leks = "ÏĞÈÑÂÎÅÍÈÅ";
				return 0; 
			}
			return -1;
		}
		return -1;
	}
	return -1;
}

int state_name1(char symb[], string value[], int* curState, int* ind, Token* tkn, string curString) {
	if (*curState == NAME1) {
		if (value[*ind] == "ÁÓÊÂÀ" || value[*ind] == "ÏÎÄ×ÅĞÊ" || value[*ind] == "ÖÈÔĞÀ" && curString != "") {
			curString.push_back(symb[*ind]);
			(*ind)++;
			return state_name1(symb, value, curState, ind, tkn, curString);
		}
		if (curString != "" && value[*ind] == "ÎÑÊÎÁÊÀ") {
			*curState = ID3;
			(*ind)++;
			tkn->input_string = curString;
			tkn->leks = "ÏÎÄÏĞÎÃĞÀÌÌÀ";
			return 0;
		}
		return -1;
	}
	return -1;
}

int state_id3(char symb[], string value[], int* curState, int* ind, Token* tkn, string curString)
{
	if (*curState == ID3) {
		if (value[*ind] == "ÁÓÊÂÀ" || value[*ind] == "ÏÎÄ×ÅĞÊ" || value[*ind] == "ÖÈÔĞÀ" && curString != "") {
			curString.push_back(symb[*ind]);
			(*ind)++;
			return state_id3(symb, value, curState, ind, tkn, curString);
		}
		if (curString != "" && value[*ind] == "ÇÑÊÎÁÊÀ") {
			*curState = CBRACKET1;
			(*ind)++;
			tkn->input_string = curString;
			tkn->leks = "ÈÄÅÍÒÈÔÈÊÀÒÎĞ";
			return 0;
		}
		return -1;
	}
	return -1;
}

int state_cbracket1(char symb[], string value[], int* curState, int* ind, Token* tkn)
{
	if (*curState == CBRACKET1) {
		if (value[*ind] == "ÏĞÎÁÅË")
		{
			*curState = SPACE5;
			return state_space5(symb, value, curState, ind, tkn);
		}
		if (value[*ind] == "Ò×ÊÇÏÒ")
		{
			*curState = SEMICOLON;
			(*ind)++;
			tkn->input_string = ";";
			tkn->leks = "Ò×ÊÇÏÒ";
			return 0;
		}
		return -1;
	}
	return -1;
}


int state_space5(char symb[], string value[], int* curState, int* ind, Token* tkn)
{
	if (*curState == SPACE5) {
		if (value[*ind] == "ÏĞÎÁÅË")
		{
			(*ind)++;
			return state_space5(symb, value, curState, ind, tkn);
		}
		if (value[*ind] == "Ò×ÊÇÏÒ")
		{
			*curState = SEMICOLON;
			return state_semicolon(symb, value, curState, ind, tkn);
		}
		if (value[*ind] == "ÁÓÊÂÀ")
		{
			*curState = ELSE;
			return state_else(symb, value, curState, ind, tkn);
		}
		return -1;
	}
	return -1;
}

int state_else(char symb[], string value[], int* curState, int* ind, Token* tkn, string curString)
{
	if (*curState == ELSE) {
		if (curString.size() == 4 && value[*ind] == "ÏĞÎÁÅË")
		{
			*curState = SPACE6;
			tkn->input_string = curString;
			tkn->leks = "ÈÄÅÍÒÈÔÈÊÀÒÎĞ";
			return 0;
		}
		if (value[*ind] == "ÁÓÊÂÀ")
		{
			switch ((char)tolower(symb[*ind])) {
				case 'l': if (curString.size() != 1) return -1;
					break;
				case 's': if (curString.size() != 2) return -1;
					break;
				default:
				// ïğèøëî å è ïåğåä íèì åñòü s èëè ïğîáåë
					if ((char)tolower(symb[*ind]) == 'e' && (curString.size() != 0 && 
						(char)tolower(symb[(*ind)-1]) == 's' || curString.size() == 0))
						break;
					return -1;
			}
			curString.push_back(symb[*ind]);
			*ind += 1;
			return state_else(symb, value, curState, ind, tkn, curString);
		}
		return -1;
	}
	return -1;
}

int state_space6(char symb[], string value[], int* curState, int* ind, Token* tkn)
{
	if (*curState == SPACE6) {
		if (value[*ind] == "ÏĞÎÁÅË")
		{
			(*ind)++;
			return state_space6(symb, value, curState, ind, tkn);
		}
		if (value[*ind] == "ÁÓÊÂÀ")
		{
			*curState = NAME2;
			return state_name2(symb, value, curState, ind, tkn);
		}
		return -1;
	}
	return -1;
}

int state_name2(char symb[], string value[], int* curState, int* ind, Token* tkn, string curString)
{
	if (*curState == NAME2) {
		if (value[*ind] == "ÁÓÊÂÀ" || value[*ind] == "ÏÎÄ×ÅĞÊ" || value[*ind] == "ÖÈÔĞÀ" && curString != "") {
			curString.push_back(symb[*ind]);
			(*ind)++;
			return state_name2(symb, value, curState, ind, tkn, curString);
		}
		if (curString != "" && value[*ind] == "ÎÑÊÎÁÊÀ") {
			*curState = SIGN_INT;
			(*ind)++;
			tkn->input_string = curString;
			tkn->leks = "ÏÎÄÏĞÎÃĞÀÌÌÀ";
			return 0;
		}
		return -1;
	}
	return -1;
}

int state_sign_and_int(char symb[], string value[], int* curState, int* ind, Token* tkn, string curString)
{
	if (*curState == SIGN_INT) {
		if (curString == "" && value[*ind] == "ÇÍÀÊ") {
			curString.push_back(symb[*ind]);
			(*ind)++;
			return state_sign_and_int(symb, value, curState, ind, tkn, curString);
		}
		if (value[*ind] == "ÖÈÔĞÀ") {
			curString.push_back(symb[*ind]);
			(*ind)++;
			return state_sign_and_int(symb, value, curState, ind, tkn, curString);
		}
		if (value[*ind] == "ÇÑÊÎÁÊÀ")
		{
			*curState = CBRACKET2;
			(*ind)++;
			tkn->input_string = curString;
			tkn->leks = "ÖÅËÎÅ";
			return 0;
		}
		return -1;
	}
	return -1;
}

int state_cbracket2(char symb[], string value[], int* curState, int* ind, Token* tkn)
{
	if (*curState == CBRACKET2) {
		if (value[*ind] == "ÏĞÎÁÅË")
		{
			(*ind)++;
			return state_cbracket2(symb, value, curState, ind, tkn);
		}
		if (value[*ind] == "Ò×ÊÇÏÒ")
		{
			*curState = SEMICOLON;
			(*ind)++;
			tkn->input_string = ";";
			tkn->leks = "Ò×ÊÇÏÒ";
			return 0;
		}
		return -1;
	}
	return -1;
}

int state_semicolon(char symb[], string value[], int* curState, int* ind, Token* tkn)
{
	if (*curState == SEMICOLON && value[*ind] == "ÏĞÎÁÅË") {
		(*ind)++;
		return state_semicolon(symb, value, curState, ind, tkn);
	}
	if (value[*ind] == "") return 0;
	return -1;
}