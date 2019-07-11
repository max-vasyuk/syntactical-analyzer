#include "header.h"
#include "leks.h"

// func_Leks - ����������� ����
//________________________________________________________________________________________________________
// ����:  string translit_result - ������ ����� ��������������
//________________________________________________________________________________________________________
// �����: string - ��������� ������������ �������
//________________________________________________________________________________________________________
string func_Leks(string translit_result) {
	// ���������� ��� ������� ����������� ��������������
	char text[80];
	string leks[80];
	// ��������� ��������������
	int length = parse_translit_result(translit_result, text, leks);
	// ����� ������� �����������
	return func_analyze(text, leks, length);
}

// parse_translit_result - ������� ��� ������������� ����������� ��������������
//________________________________________________________________________________________________________
// ����: string translit_result - ������ ����� ��������������
//		 char text[] - �������������� ������ (���������� ��� ������)
//       string tr_keys[] - ������� �������������� (���������� ��� ������)
//________________________________________________________________________________________________________
// �����: int - ����� �������������� ������
//________________________________________________________________________________________________________
int parse_translit_result(string translit_result, char text[], string tr_keys[]) {
	// ������ ���������������� �������, ������ �������� ������� � ������ ���������� ��������������
	int ind = 0, cur = 1;

	// ���� �� ������ � ����������� �������������� ��� ���������� ������
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
	// ������ ��������� ���������� ������� (���������� - �����)
	return ind;
}

// func_analyze - ������� ��� ������������� ����������� ��������������
//________________________________________________________________________________________________________
// ����: char text[] - �������������� ������
//       string tr_keys[] - ������� ��������������
//       int length - ����� �������������� ������
//________________________________________________________________________________________________________
// �����: string - ������ � ����������� ������������ �������
//________________________________________________________________________________________________________
string func_analyze(char text[], string tr_keys[], int length) {
	// ������� ��������� - ������; ������ �������� ������� - 0
	int curState = BEGIN, ind = 0;
	// ������, � ������� ����� ������������ ���������
	string result_string = "";
	// ������ (������) � ������������ ������������� (��������)
	std::vector<Token> tokens;
	// ����� ������� ��� ��������� ��������� ��������
	tokens.push_back(state_begin(text, tr_keys, &curState, &ind));
	tokens.push_back(state_space1(text, tr_keys, &curState, &ind));
	tokens.push_back(state_space2(text, tr_keys, &curState, &ind));
	tokens.push_back(state_space3(text, tr_keys, &curState, &ind));
	tokens.push_back(state_space4(text, tr_keys, &curState, &ind));
	tokens.push_back(state_name1(text, tr_keys, &curState, &ind));
	Token obracket1{ "(", "�������" };
	tokens.push_back(obracket1);
	tokens.push_back(state_id3(text, tr_keys, &curState, &ind));
	Token �bracket1{ ")", "�������" };
	tokens.push_back(�bracket1);
	tokens.push_back(state_cbracket1(text, tr_keys, &curState, &ind));
	// ���� ��������� ; � ����������� �������������, ���� ���������� else
	if (curState != SEMICOLON) {
		tokens.push_back(state_space6(text, tr_keys, &curState, &ind));
		Token obracket2{ "(", "�������" };
		tokens.push_back(obracket2);
		tokens.push_back(state_sign_and_int(text, tr_keys, &curState, &ind));
		Token �bracket2{ ")", "�������" };
		tokens.push_back(�bracket2);
		tokens.push_back(state_cbracket2(text, tr_keys, &curState, &ind));
	}
	// ���� �������� ������� ����� ;
	if (ind <= length - 1) {
		Token tkn = state_semicolon(text, tr_keys, &curState, &ind);
		if (tkn.input_string != "�����")
			tokens.push_back(tkn);
	}
	// ��������� ���������� � ������
	for (int i = 0; i < tokens.size(); i++) {
		result_string.append("(" + tokens[i].input_string + ", " + tokens[i].leks + ")");
		if (tokens[i].leks == "������") break;
		if (i != tokens.size() - 1) result_string.append(", ");
	}
	// ������� ���������� ������������ �������
	return result_string;
}

// create_token - ������� ��� �������� ������ �������������
//________________________________________________________________________________________________________
// ����: string str - ������
//       string value - ��������������� �� ��������
//________________________________________________________________________________________________________
// �����: Token - �����, ���������� str, value
//________________________________________________________________________________________________________
Token create_token(string str, string value) {
	Token tkn;
	tkn.input_string = str;
	tkn.leks = value;
	return tkn;
}

// state_begin - ������� ��� ��������� "������"
//________________________________________________________________________________________________________
// ����: char symb[] - �������������� ������
//		 string value[] - ���������� ��������������
//		 int* curState - ������� ���������
//		 int* ind - ������� ������ � ������
//________________________________________________________________________________________________________
// �����: Token - �����, ���������� str, value
//________________________________________________________________________________________________________
Token state_begin(char symb[], string value[], int* curState, int* ind) {
	// ���� ������ ���������
	if (*curState == BEGIN) {
		// ���� ������� ������
		if (value[*ind] == "������") {
			// ������ ������ � ���� �� ���������, ����� ���� �� �������
			(*ind)++;
			return state_begin(symb, value, curState, ind);
		}
		// ���� �������� �����
		if (value[*ind] == "�����") {
			// ����� ��������� � ����� ������� ��� ���������� if
			*curState = IF;
			return state_if(symb, value, curState, ind);
		}
	}
	// ����� ������
	return create_token(string(1, symb[*ind]), "������");
}

// state_if - ������� ��� ��������� "IF"
//________________________________________________________________________________________________________
// ����: char symb[] - �������������� ������
//		 string value[] - ���������� ��������������
//		 int* curState - ������� ���������
//		 int* ind - ������� ������ � ������
//       string curString - ������ ��� ���������� ���������� ����������
//________________________________________________________________________________________________________
// �����: Token - �����, ���������� str, value
//________________________________________________________________________________________________________
Token state_if(char symb[], string value[], int* curState, int* ind, string curString) {
	// ���� ������ ���������
	if (*curState == IF) {
		// �������� �����
		if (value[*ind] == "�����") {
			// ��������� i ��� I ��� ��������� f ��� F
			if (curString == "" && (char)tolower(symb[*ind]) == 'i' || 
				curString.size() == 1 && (char)tolower(symb[*ind]) == 'f') {
				curString.push_back(symb[*ind]);
				(*ind)++;
				// ������ ������, ������ ��� �� �������
				return state_if(symb, value, curState, ind, curString);
			}
			// ����� ������
			return create_token(string(1, symb[*ind]), "������");
		}
		// ������� ������ ��� ��������� if
		if (curString.size() == 2 && value[*ind] == "������") {
			// ����� ���������
			*curState = SPACE1;
			// ������� ����������
			return create_token(curString, "�������������");
		}
	}
	// ����� ������
	return create_token(string(1, symb[*ind]), "������");
}

// �������� ���������� state_begin
Token state_space1(char symb[], string value[], int* curState, int* ind) {
	// ���� ������ ���������
	if (*curState == SPACE1) {
		// ������� ������
		if (value[*ind] == "������") {
			// ������ ������, ������ ��� �� �������
			(*ind)++;
			return state_space1(symb, value, curState, ind);
		}
		// �������� �����
		if (value[*ind] == "�����") {
			// ����� ���������, ����� ������� ���������� ��������������
			*curState = ID1;
			return state_id1(symb, value, curState, ind);
		}
	}
	// ����� ������
	return create_token(string(1, symb[*ind]), "������");
}

// �������� ���������� state_if
Token state_id1(char symb[], string value[], int* curState, int* ind, string curString) {
	// ���� ������ ���������
	if (*curState == ID1) {
		// ������� ������ ����� ���������� ��������������
		if (curString != "" && value[*ind] == "������") {
			// ����� ���������, ������� ����������
			*curState = SPACE2;
			return create_token(curString, "�������������");
		}
		// �������� ������� ��� ��������������
		if (value[*ind] == "�����" || value[*ind] == "�������" || value[*ind] == "�����" && curString != "") {
			// ������ �����, �������� ������ � curString
			curString.push_back(symb[*ind]);
			(*ind)++;
			return state_id1(symb, value, curState, ind, curString);
		}
	}
	// ����� ������
	return create_token(string(1, symb[*ind]), "������");
}

// �������� ���������� state_begin
Token state_space2(char symb[], string value[], int* curState, int* ind) {
	// ���� ������ ���������
	if (*curState == SPACE2) {
		// ������� ������
		if (value[*ind] == "������") {
			// ������ ����� � ���� �� ������� � ���� �� ���������
			(*ind)++;
			return state_space2(symb, value, curState, ind);
		}
		// �������� �����
		if (value[*ind] == "�����") {
			// ����� ��������� � ����� ������� ��� ���������� then
			*curState = THEN;
			return state_then(symb, value, curState, ind);
		}
	}
	// ����� ������
	return create_token(string(1, symb[*ind]), "������");
}

// �������� ���������� state_if
Token state_then(char symb[], string value[], int* curState, int* ind, string curString) {
	// ���� ������ ���������
	if (*curState == THEN) {
		// �������� �����
		if (value[*ind] == "�����") {
			// ������ then, �� �������� �������
			switch ((char)tolower(symb[*ind])) {
				case 't': if (curString.size() != 0) return create_token(string(1, symb[*ind]), "������");
					break;
				case 'h': if (curString.size() != 1) return create_token(string(1, symb[*ind]), "������");
					break;
				case 'e': if (curString.size() != 2) return create_token(string(1, symb[*ind]), "������");
					break;
				case 'n': if (curString.size() != 3) return create_token(string(1, symb[*ind]), "������");
					break;
				// ����� ������
				default: return create_token(string(1, symb[*ind]), "������");
			}
			curString.push_back(symb[*ind]);
			*ind += 1;
			return state_then(symb, value, curState, ind, curString);
		}
		// ������� ������ ����� ���������� then
		if (curString.size() == 4 && value[*ind] == "������") {
			// ����� ���������, ������� ����������
			*curState = SPACE3;
			return create_token(curString, "�������������");
		}
	}
	// ����� ������
	return create_token(string(1, symb[*ind]), "������");
}

// �������� ���������� state_begin
Token state_space3(char symb[], string value[], int* curState, int* ind) {
	// ���� ������ ���������
	if (*curState == SPACE3) {
		// ������� ������
		if (value[*ind] == "������") {
			// ������ ����� � ���� �� ������� � ���������
			(*ind)++;
			return state_space3(symb, value, curState, ind);
		}
		// �������� �����
		if (value[*ind] == "�����") {
			// ����� ��������� � ����� ������� ���������� ��������������2
			*curState = ID2;
			return state_id2(symb, value, curState, ind);
		}
	}
	// ����� ������
	return create_token(string(1, symb[*ind]), "������");
}

// �������� ���������� state_if
Token state_id2(char symb[], string value[], int* curState, int* ind, string curString) {
	// ���� ������ ���������
	if (*curState == ID2) {
		// ������ ������ ��� ��������������
		if (value[*ind] == "�����" || value[*ind] == "�������" || value[*ind] == "�����" && curString != "") {
			// ������ �����, �������� ������
			curString.push_back(symb[*ind]);
			(*ind)++;
			return state_id2(symb, value, curState, ind, curString);
		}
		// ������ ������ ��� ���������
		if (curString != "" && value[*ind] == "������" || value[*ind] == "���������") {
			// ����� ��������� � ������� ����������
			if (value[*ind] == "������") *curState = SPACE4;
			else *curState = COLON_EQUAL;
			return create_token(curString, "�������������");
		}
	}
	// ����� ������
	return create_token(string(1, symb[*ind]), "������");
}

// �������� ���������� state_begin
Token state_space4(char symb[], string value[], int* curState, int* ind) {
	// ���� ������ ���������
	if (*curState == SPACE4 || *curState == COLON_EQUAL) {
		// ������� ������
		if (value[*ind] == "������") {
			// ������ �����, �������� ���������
			(*ind)++;
			return state_space4(symb, value, curState, ind);
		}
		// �������� ���������
		if (value[*ind] == "���������") {
			// ����� ��������� � ����� ������ ������� ��� ����������
			*curState = COLON_EQUAL;
			return state_colon_and_equal(symb, value, curState, ind);
		}
	}
	// ����� ������
	return create_token(string(1, symb[*ind]), "������");
}

// �������� ���������� state_if
Token state_colon_and_equal(char symb[], string value[], int* curState, int* ind, string curString) {
	// ���� ������ ���������
	if (*curState == COLON_EQUAL) {
		// �������� ��������� ��� ����� ����� ���������
		if (curString == "" && value[*ind] == "���������" || 
			curString.size() == 1 && value[*ind] == "�����") {
			// �������� ��� � ������ �����
			curString.push_back(symb[*ind]);
			(*ind)++;
			return state_colon_and_equal(symb, value, curState, ind, curString);
		}
		// ���� ��������� � ����� �������
		if (curString.size() == 2){
			// ������� ������
			if (value[*ind] == "������") {
				// ������ �����
				(*ind)++;
				return state_colon_and_equal(symb, value, curState, ind, curString);
			}
			// �������� �����
			if (value[*ind] == "�����") {
				// ����� ��������� � ������� ����������
				*curState = NAME1;
				return create_token(curString, "����������");
			}
		}
	}
	// ����� ������
	return create_token(string(1, symb[*ind]), "������");
}

// �������� ���������� state_if
Token state_name1(char symb[], string value[], int* curState, int* ind, string curString) {
	// ���� ������ ���������
	if (*curState == NAME1) {
		// ������� ������ �������� ������������
		if (value[*ind] == "�����" || value[*ind] == "�������" || value[*ind] == "�����" && curString != "") {
			// ������ �����, �������� ���� ������
			curString.push_back(symb[*ind]);
			(*ind)++;
			return state_name1(symb, value, curState, ind, curString);
		}
		// �������� �������
		if (curString != "" && value[*ind] == "�������") {
			// ����� ��������� � ������� ����������
			*curState = ID3;
			(*ind)++;
			return create_token(curString, "������������");
		}
	}
	// ����� ������
	return create_token(string(1, symb[*ind]), "������");
}

// �������� ���������� state_if
Token state_id3(char symb[], string value[], int* curState, int* ind, string curString) {
	// ���� ������ ���������
	if (*curState == ID3) {
		// ������� ������ ��������������
		if (value[*ind] == "�����" || value[*ind] == "�������" || value[*ind] == "�����" && curString != "") {
			// �������� ������ � ����� ������ �����
			curString.push_back(symb[*ind]);
			(*ind)++;
			return state_id3(symb, value, curState, ind, curString);
		}
		// �������� ����������� ������ ����� ���������� ��������������
		if (curString != "" && value[*ind] == "�������") {
			// ����� ���������, ������� ����������
			*curState = CBRACKET1;
			(*ind)++;
			return create_token(curString, "�������������");
		}
	}
	// ����� ������
	return create_token(string(1, symb[*ind]), "������");
}

// �������� ���������� state_begin
Token state_cbracket1(char symb[], string value[], int* curState, int* ind) {
	// ���� ������ ���������
	if (*curState == CBRACKET1) {
		// ������� ������
		if (value[*ind] == "������") {
			// ����� ��������� � ����� ������� ������ ��������
			*curState = SPACE5;
			return state_space5(symb, value, curState, ind);
		}
		// �������� ������
		if (value[*ind] == "������") {
			// ����� ���������, ������� ����������
			*curState = SEMICOLON;
			(*ind)++;
			return create_token(";", "������");
		}
	}
	// ����� ������
	return create_token(string(1, symb[*ind]), "������");
}

// �������� ���������� state_begin
Token state_space5(char symb[], string value[], int* curState, int* ind) {
	// ���� ������ ���������
	if (*curState == SPACE5) {
		// ������� ������
		if (value[*ind] == "������") {
			// ������ �����
			(*ind)++;
			return state_space5(symb, value, curState, ind);
		}
		// �������� ������
		if (value[*ind] == "������") {
			// ����� ��������� � ����� ������� ��� ������
			*curState = SEMICOLON;
			return state_semicolon(symb, value, curState, ind);
		}
		// �������� �����
		if (value[*ind] == "�����") {
			// ����� ��������� � ����� ������� ��� ELSE
			*curState = ELSE;
			return state_else(symb, value, curState, ind);
		}
	}
	// ����� ������
	return create_token(string(1, symb[*ind]), "������");
}

// �������� ���������� state_if
Token state_else(char symb[], string value[], int* curState, int* ind, string curString) {
	// ���� ������ ���������
	if (*curState == ELSE) {
		// ������� ������ ����� else
		if (curString.size() == 4 && value[*ind] == "������") {
			// ����� ��������� � ������� ����������
			*curState = SPACE6;
			return create_token(curString, "�������������");
		}
		// �������� �����
		if (value[*ind] == "�����") {
			// ������ else ��� ����� ��������
			switch ((char)tolower(symb[*ind])) {
				case 'l': if (curString.size() != 1) return create_token(string(1, symb[*ind]), "������");
					break;
				case 's': if (curString.size() != 2) return create_token(string(1, symb[*ind]), "������");
					break;
				default:
				// ������ � � ����� ��� ���� (s ��� ������)
					if ((char)tolower(symb[*ind]) == 'e' && (curString.size() != 0 && 
						(char)tolower(symb[(*ind)-1]) == 's' || curString.size() == 0))
						break;
				// ����� ������
					return create_token(string(1, symb[*ind]), "������");
			}
			// ������ �����, �������� ������
			curString.push_back(symb[*ind]);
			*ind += 1;
			return state_else(symb, value, curState, ind, curString);
		}
	}
	// ����� ������
	return create_token(string(1, symb[*ind]), "������");
}

// �������� ���������� state_begin
Token state_space6(char symb[], string value[], int* curState, int* ind) {
	// ���� ������ ���������
	if (*curState == SPACE6) {
		// ������� ������
		if (value[*ind] == "������") {
			// ������ �� �����
			(*ind)++;
			return state_space6(symb, value, curState, ind);
		}
		// �������� �����
		if (value[*ind] == "�����") {
			// ����� ��������� � ����� ������� ������ ����� ������������
			*curState = NAME2;
			return state_name2(symb, value, curState, ind);
		}
	}
	// ����� ������
	return create_token(string(1, symb[*ind]), "������");
}

// �������� ���������� state_if
Token state_name2(char symb[], string value[], int* curState, int* ind, string curString) {
	// ���� ������ ���������
	if (*curState == NAME2) {
		// ������ ������ �� ����� ������������
		if (value[*ind] == "�����" || value[*ind] == "�������" || value[*ind] == "�����" && curString != "") {
			// ��������� ��� � ������ ������
			curString.push_back(symb[*ind]);
			(*ind)++;
			return state_name2(symb, value, curState, ind, curString);
		}
		// ������ ����������� ������ ����� ����� ������������
		if (curString != "" && value[*ind] == "�������") {
			// ����� ��������� � ������� ����������
			*curState = SIGN_INT;
			(*ind)++;
			return create_token(curString, "������������");
		}
	}
	// ����� ������
	return create_token(string(1, symb[*ind]), "������");
}

// �������� ���������� state_if
Token state_sign_and_int(char symb[], string value[], int* curState, int* ind, string curString) {
	// ���� ������ ���������
	if (*curState == SIGN_INT) {
		// ������� ���� ��� �����
		if (curString == "" && value[*ind] == "����" || value[*ind] == "�����") {
			// ���������, ������ �����
			curString.push_back(symb[*ind]);
			(*ind)++;
			return state_sign_and_int(symb, value, curState, ind, curString);
		}
		// �������� �������
		if (value[*ind] == "�������") {
			// ����� ��������� � ������� ����������
			*curState = CBRACKET2;
			(*ind)++;
			return create_token(curString, "�����");
		}
	}
	// ����� ������
	return create_token(string(1, symb[*ind]), "������");
}

// �������� ���������� state_begin
Token state_cbracket2(char symb[], string value[], int* curState, int* ind) {
	// ���� ������ ���������
	if (*curState == CBRACKET2) {
		// ������� ������
		if (value[*ind] == "������") {
			// ������ ������
			(*ind)++;
			return state_cbracket2(symb, value, curState, ind);
		}
		// �������� ������
		if (value[*ind] == "������") {
			// ����� ��������� � ������� ����������
			*curState = SEMICOLON;
			(*ind)++;
			return create_token(";", "������");
		}
	}
	// ����� ������
	return create_token(string(1, symb[*ind]), "������");
}

// �������� ���������� state_begin
Token state_semicolon(char symb[], string value[], int* curState, int* ind) {
	// ���� ������ ��������� � ������� ������
	if (*curState == SEMICOLON && value[*ind] == "������") {
		// ������ �� ������
		(*ind)++;
		return state_semicolon(symb, value, curState, ind);
	}
	// �������� ����� ����� - ������, ��� �� ��
	if (value[*ind] == "") return create_token("�����", "�����");
	// ����� ������
	return create_token(string(1, symb[*ind]), "������");
}