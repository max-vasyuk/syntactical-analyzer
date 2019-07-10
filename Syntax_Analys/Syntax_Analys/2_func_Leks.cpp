#include "header.h"
#include "leks.h"

// func_Leks - ����������� ����
//__________________________________________________________________
// ����:  string translit_result - ������ ����� ��������������
//__________________________________________________________________
// �����: string result - ��������� ������������ �������
//__________________________________________________________________
string func_Leks(string translit_result) {
	// ���������� ��� ������� ����������� ��������������
	char text[80];
	string leks[80];

	// ��������� ��������������
	int length = parse_translit_result(translit_result, text, leks);

	// ����� ������� �����������
	return func_analyze(text, leks, length);
}

string func_analyze(char text[], string tr_keys[], int length) {
	int curState = BEGIN, ind = 0;
	string result_string = "";
	Token tkn;

	if (state_begin(text, tr_keys, &curState, &ind, &tkn) == 0)
		token_to_string(&result_string, &tkn);
	else cout << "������";

	if (state_space1(text, tr_keys, &curState, &ind, &tkn) == 0)
		token_to_string(&result_string, &tkn);
	else cout << "������";

	if (state_space2(text, tr_keys, &curState, &ind, &tkn) == 0)
		token_to_string(&result_string, &tkn);
	else cout << "������";

	if (state_space3(text, tr_keys, &curState, &ind, &tkn) == 0)
		token_to_string(&result_string, &tkn);
	else cout << "������";

	if (state_space4(text, tr_keys, &curState, &ind, &tkn) == 0)
		token_to_string(&result_string, &tkn);
	else cout << "������";

	if (state_name1(text, tr_keys, &curState, &ind, &tkn) == 0) {
		token_to_string(&result_string, &tkn);
		tkn.input_string = "(";
		tkn.leks = "�������";
		token_to_string(&result_string, &tkn);
	}
	else cout << "������";

	if (state_id3(text, tr_keys, &curState, &ind, &tkn) == 0) {
		token_to_string(&result_string, &tkn);
		tkn.input_string = ")";
		tkn.leks = "�������";
		token_to_string(&result_string, &tkn);
	}
	else cout << "������";

	if (state_cbracket1(text, tr_keys, &curState, &ind, &tkn) == 0)
		token_to_string(&result_string, &tkn);
	else cout << "������";

	if (curState != SEMICOLON)
	{
		if (state_space6(text, tr_keys, &curState, &ind, &tkn) == 0) {
			token_to_string(&result_string, &tkn);
			tkn.input_string = "(";
			tkn.leks = "�������";
			token_to_string(&result_string, &tkn);
		}
		else cout << "������";

		if (state_sign_and_int(text, tr_keys, &curState, &ind, &tkn) == 0) {
			token_to_string(&result_string, &tkn);
			tkn.input_string = ")";
			tkn.leks = "�������";
			token_to_string(&result_string, &tkn);
		}
		else cout << "������";

		if (state_cbracket2(text, tr_keys, &curState, &ind, &tkn) == 0)
			result_string.append("(" + tkn.input_string + ", " + tkn.leks + ")");
		else cout << "������";
	}

	if (ind <= length - 1 && state_semicolon(text, tr_keys, &curState, &ind, &tkn) != 0)
		cout << "������";

	return result_string;
}

void token_to_string(string *str, Token *tkn)
{
	(*str).append("(" + tkn->input_string + ", " + tkn->leks + "), ");
	tkn->input_string = "";
	tkn->leks = "";
}

int parse_translit_result(string translit_result, char text[], string tr_keys[]) {
	// ������ ���������������� �������, ������ �������� ������� �
	// ������ ���������� ��������������
	int ind = 0, cur = 1;

	// ���� �� ������ � ����������� �������������� ��� ���������� 
	// ������
	while (cur < translit_result.size()) {
		// ���������� ��������������� ������
		text[ind] = translit_result[cur];

		// ������ ��������� ������� (�� ������� �� ������)
		int i = cur + 2;
		for (; translit_result[i] != ')'; i++)
			tr_keys[ind].push_back(translit_result[i]);

		// ������� � ���������� �������
		cur = i + 4;
		ind++;
	}
	return ind;
}

int state_begin(char symb[], string value[], int* curState, int* ind, Token* tkn) {
	if (*curState == BEGIN) {
		if (value[*ind] == "������") {
			*ind++;
			return state_begin(symb, value, curState, ind, tkn);
		}
		if (value[*ind] == "�����"){
			*curState = IF;
			return state_if(symb, value, curState, ind, tkn);
		}
		return -1;
	}
	return -1;
}

int state_if(char symb[], string value[], int* curState, int* ind, Token* tkn, string curString) {
	if (*curState == IF) {
		if (value[*ind] == "�����") {
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
		if (curString.size() == 2 && value[*ind] == "������") {
			*curState = SPACE1;
			tkn->input_string = curString;
			tkn->leks = "�������������";
			return 0;
		}
		return -1;
	}
	return -1;
}

int state_space1(char symb[], string value[], int* curState, int* ind, Token* tkn) {
	if (*curState == SPACE1) {
		if (value[*ind] == "������") {
			(*ind)++;
			return state_space1(symb, value, curState, ind, tkn);
		}
		if (value[*ind] == "�����") {
			*curState = ID1;
			return state_id1(symb, value, curState, ind, tkn);
		}
		return -1;
	}
	return -1;
}

int state_id1(char symb[], string value[], int* curState, int* ind, Token* tkn, string curString) {
	if (*curState == ID1) {
		if (curString != "" && value[*ind] == "������")
		{
			*curState = SPACE2;
			tkn->input_string = curString;
			tkn->leks = "�������������";
			return 0;
		}
		if (value[*ind] == "�����" || value[*ind] == "�������" || value[*ind] == "�����" && curString != "")
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
		if (value[*ind] == "������") {
			(*ind)++;
			return state_space2(symb, value, curState, ind, tkn);
		}
		if (value[*ind] == "�����") {
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
		if (value[*ind] == "�����") {
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
		if (curString.size() == 4 && value[*ind] == "������") {
			*curState = SPACE3;
			tkn->input_string = curString;
			tkn->leks = "�������������";
			return 0;
		}
		return -1;
	}
	return -1;
}

int state_space3(char symb[], string value[], int* curState, int* ind, Token* tkn) {
	if (*curState == SPACE3) {
		if (value[*ind] == "������") {
			(*ind)++;
			return state_space3(symb, value, curState, ind, tkn);
		}
		if (value[*ind] == "�����") {
			*curState = ID2;
			return state_id2(symb, value, curState, ind, tkn);
		}
		return -1;
	}
	return -1;
}

int state_id2(char symb[], string value[], int* curState, int* ind, Token* tkn, string curString) {
	if (*curState == ID2) {
		if (value[*ind] == "�����" || value[*ind] == "�������" || value[*ind] == "�����" && curString != "") {
			curString.push_back(symb[*ind]);
			(*ind)++;
			return state_id2(symb, value, curState, ind, tkn, curString);
		}
		if (curString != "" && value[*ind] == "������" || value[*ind] == "���������") {
			if (value[*ind] == "������") *curState = SPACE4;
			else *curState = COLON_EQUAL;
			tkn->input_string = curString;
			tkn->leks = "�������������";
			return 0;
		}
		return -1;
	}
	return -1;
}

int state_space4(char symb[], string value[], int* curState, int* ind, Token* tkn)
{
	if (*curState == SPACE4 || *curState == COLON_EQUAL) {
		if (value[*ind] == "������") {
			(*ind)++;
			return state_space4(symb, value, curState, ind, tkn);
		}
		if (value[*ind] == "���������") {
			*curState = COLON_EQUAL;
			return state_colon_and_equal(symb, value, curState, ind, tkn);
		}
		return -1;
	}
	return -1;
}

int state_colon_and_equal(char symb[], string value[], int* curState, int* ind, Token* tkn, string curString) {
	if (*curState == COLON_EQUAL) {
		if (curString == "" && value[*ind] == "���������") {
			curString.push_back(symb[*ind]);
			(*ind)++;
			return state_colon_and_equal(symb, value, curState, ind, tkn, curString);
		}
		if (curString.size() == 1 && value[*ind] == "�����") {
			curString.push_back(symb[*ind]);
			(*ind)++;
			return state_colon_and_equal(symb, value, curState, ind, tkn, curString);
		}
		if (curString.size() == 2){
			if (value[*ind] == "������") {
				(*ind)++;
				return state_colon_and_equal(symb, value, curState, ind, tkn, curString);
			}
			if (value[*ind] == "�����") {
				*curState = NAME1;
				tkn->input_string = curString;
				tkn->leks = "����������";
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
		if (value[*ind] == "�����" || value[*ind] == "�������" || value[*ind] == "�����" && curString != "") {
			curString.push_back(symb[*ind]);
			(*ind)++;
			return state_name1(symb, value, curState, ind, tkn, curString);
		}
		if (curString != "" && value[*ind] == "�������") {
			*curState = ID3;
			(*ind)++;
			tkn->input_string = curString;
			tkn->leks = "������������";
			return 0;
		}
		return -1;
	}
	return -1;
}

int state_id3(char symb[], string value[], int* curState, int* ind, Token* tkn, string curString)
{
	if (*curState == ID3) {
		if (value[*ind] == "�����" || value[*ind] == "�������" || value[*ind] == "�����" && curString != "") {
			curString.push_back(symb[*ind]);
			(*ind)++;
			return state_id3(symb, value, curState, ind, tkn, curString);
		}
		if (curString != "" && value[*ind] == "�������") {
			*curState = CBRACKET1;
			(*ind)++;
			tkn->input_string = curString;
			tkn->leks = "�������������";
			return 0;
		}
		return -1;
	}
	return -1;
}

int state_cbracket1(char symb[], string value[], int* curState, int* ind, Token* tkn)
{
	if (*curState == CBRACKET1) {
		if (value[*ind] == "������")
		{
			*curState = SPACE5;
			return state_space5(symb, value, curState, ind, tkn);
		}
		if (value[*ind] == "������")
		{
			*curState = SEMICOLON;
			(*ind)++;
			tkn->input_string = ";";
			tkn->leks = "������";
			return 0;
		}
		return -1;
	}
	return -1;
}


int state_space5(char symb[], string value[], int* curState, int* ind, Token* tkn)
{
	if (*curState == SPACE5) {
		if (value[*ind] == "������")
		{
			(*ind)++;
			return state_space5(symb, value, curState, ind, tkn);
		}
		if (value[*ind] == "������")
		{
			*curState = SEMICOLON;
			return state_semicolon(symb, value, curState, ind, tkn);
		}
		if (value[*ind] == "�����")
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
		if (curString.size() == 4 && value[*ind] == "������")
		{
			*curState = SPACE6;
			tkn->input_string = curString;
			tkn->leks = "�������������";
			return 0;
		}
		if (value[*ind] == "�����")
		{
			switch ((char)tolower(symb[*ind])) {
				case 'l': if (curString.size() != 1) return -1;
					break;
				case 's': if (curString.size() != 2) return -1;
					break;
				default:
				// ������ � � ����� ��� ���� s ��� ������
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
		if (value[*ind] == "������")
		{
			(*ind)++;
			return state_space6(symb, value, curState, ind, tkn);
		}
		if (value[*ind] == "�����")
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
		if (value[*ind] == "�����" || value[*ind] == "�������" || value[*ind] == "�����" && curString != "") {
			curString.push_back(symb[*ind]);
			(*ind)++;
			return state_name2(symb, value, curState, ind, tkn, curString);
		}
		if (curString != "" && value[*ind] == "�������") {
			*curState = SIGN_INT;
			(*ind)++;
			tkn->input_string = curString;
			tkn->leks = "������������";
			return 0;
		}
		return -1;
	}
	return -1;
}

int state_sign_and_int(char symb[], string value[], int* curState, int* ind, Token* tkn, string curString)
{
	if (*curState == SIGN_INT) {
		if (curString == "" && value[*ind] == "����") {
			curString.push_back(symb[*ind]);
			(*ind)++;
			return state_sign_and_int(symb, value, curState, ind, tkn, curString);
		}
		if (value[*ind] == "�����") {
			curString.push_back(symb[*ind]);
			(*ind)++;
			return state_sign_and_int(symb, value, curState, ind, tkn, curString);
		}
		if (value[*ind] == "�������")
		{
			*curState = CBRACKET2;
			(*ind)++;
			tkn->input_string = curString;
			tkn->leks = "�����";
			return 0;
		}
		return -1;
	}
	return -1;
}

int state_cbracket2(char symb[], string value[], int* curState, int* ind, Token* tkn)
{
	if (*curState == CBRACKET2) {
		if (value[*ind] == "������")
		{
			(*ind)++;
			return state_cbracket2(symb, value, curState, ind, tkn);
		}
		if (value[*ind] == "������")
		{
			*curState = SEMICOLON;
			(*ind)++;
			tkn->input_string = ";";
			tkn->leks = "������";
			return 0;
		}
		return -1;
	}
	return -1;
}

int state_semicolon(char symb[], string value[], int* curState, int* ind, Token* tkn)
{
	if (*curState == SEMICOLON && value[*ind] == "������") {
		(*ind)++;
		return state_semicolon(symb, value, curState, ind, tkn);
	}
	if (value[*ind] == "") return 0;
	return -1;
}