#include "syntax.h"

// func_Leks - ����������� ����
//________________________________________________________________________________________________________
// ����:  vector<Token>keyident_result - ������ �������� (������, �����) ����� ������������� �������� ����
//________________________________________________________________________________________________________
// �����: ��������� ��������������� ������� - ������, ���������� ACCEPT ��� REJECT - ������� ��� ��� ������� ��������������
//________________________________________________________________________________________________________
string func_Syntax(vector<Token> keyident_result) {
	int curState = BEGIN, ind = 0;
	string text[80];
	string leks[80];

	for (int i = 0; i < keyident_result.size(); i++) {
		text[i] = keyident_result[i].input_string;
		leks[i] = keyident_result[i].leks;
	}

	Token result = state_begin(text, leks, &curState, &ind);
	if (result.leks == "������") return "REJECT";
	return "ACCEPT";
}

// state_begin - ������� ��� ��������� "������"
//________________________________________________________________________________________________________
// ����: string text[] - ������������ ������� ������
//		 string value[] - ���������� ������������ �����������
//		 int* curState - ������� ���������
//		 int* ind - ������� ������ � ������
//________________________________________________________________________________________________________
// �����: Token - �����, ���������� str, value
//________________________________________________________________________________________________________
Token state_begin(string text[], string value[], int* curState, int* ind) {
	// ���� ������ ���������
	if (*curState == BEGIN) {
		// ���� ������� IF
		if (value[*ind] == "�������_IF") {
			// ����� ��������� � ����� ������� ��� ���������� ��������� ����� if
			*curState = IF;
			(*ind)++;
			return state_if(text, value, curState, ind);
		}
	}
	// ����� ������
	return create_token(text[*ind], "������");
}

// �������� ���������� state_begin
Token state_if(string text[], string value[], int* curState, int* ind) {
	// ���� ������ ���������
	if (*curState == IF) {
		// ���� ������� �������������
		if (value[*ind] == "���������") {
			// ����� ��������� � ����� ������� ��� ���������� ��������� ����� ��������������
			*curState = ID1;
			(*ind)++;
			return state_id1(text, value, curState, ind);
		}
	}
	// ����� ������
	return create_token(text[*ind], "������");
}

// �������� ���������� state_begin
Token state_id1(string text[], string value[], int* curState, int* ind) {
	// ���� ������ ���������
	if (*curState == ID1) {
		// ���� ������� THEN
		if (value[*ind] == "�������_THEN") {
			// ����� ��������� � ����� ������� ��� ���������� ��������� ����� then
			*curState = THEN;
			(*ind)++;
			return state_then(text, value, curState, ind);
		}
	}
	// ����� ������
	return create_token(text[*ind], "������");
}

// �������� ���������� state_begin
Token state_then(string text[], string value[], int* curState, int* ind) {
	// ���� ������ ���������
	if (*curState == THEN) {
		// ���� ������� �������������
		if (value[*ind] == "���������") {
			// ����� ��������� � ����� ������� ��� ���������� ��������� ����� ��������������
			*curState = ID2;
			(*ind)++;
			return state_id2(text, value, curState, ind);
		}
	}
	// ����� ������
	return create_token(text[*ind], "������");
}

// �������� ���������� state_begin
Token state_id2(string text[], string value[], int* curState, int* ind) {
	// ���� ������ ���������
	if (*curState == ID2) {
		// ���� ������� ����������
		if (value[*ind] == "����������") {
			// ����� ��������� � ����� ������� ��� ���������� ��������� ����� ����������
			*curState = COLON_EQUAL;
			(*ind)++;
			return state_colon_and_equal(text, value, curState, ind);
		}
	}
	// ����� ������
	return create_token(text[*ind], "������");
}

// �������� ���������� state_begin
Token state_colon_and_equal(string text[], string value[], int* curState, int* ind) {
	// ���� ������ ���������
	if (*curState == COLON_EQUAL) {
		// ���� ������� �������������
		if (value[*ind] == "���������") {
			// ����� ��������� � ����� ������� ��� ���������� ��������� ����� ��������������
			*curState = NAME1;
			(*ind)++;
			return state_name1(text, value, curState, ind);
		}
	}
	// ����� ������
	return create_token(text[*ind], "������");
}

// �������� ���������� state_begin
Token state_name1(string text[], string value[], int* curState, int* ind) {
	// ���� ������ ���������
	if (*curState == NAME1) {
		// ���� ������� �������
		if (value[*ind] == "�������") {
			// ����� ��������� � ����� ������� ��� ���������� ��������� ����� �������
			*curState = OBRACKET1;
			(*ind)++;
			return state_obracket1(text, value, curState, ind);
		}
	}
	// ����� ������
	return create_token(text[*ind], "������");
}

// �������� ���������� state_begin
Token state_obracket1(string text[], string value[], int* curState, int* ind) {
	// ���� ������ ���������
	if (*curState == OBRACKET1) {
		// ���� ������� �������������
		if (value[*ind] == "���������") {
			// ����� ��������� � ����� ������� ��� ���������� ��������� ����� �������������� 
			*curState = ID3;
			(*ind)++;
			return state_id3(text, value, curState, ind);
		}
	}
	// ����� ������
	return create_token(text[*ind], "������");
}

// �������� ���������� state_begin
Token state_id3(string text[], string value[], int* curState, int* ind) {
	// ���� ������ ���������
	if (*curState == ID3) {
		// ���� ������� �������
		if (value[*ind] == "�������") {
			// ����� ��������� � ����� ������� ��� ���������� ��������� ����� �������
			*curState = CBRACKET1;
			(*ind)++;
			return state_cbracket1(text, value, curState, ind);
		}
	}
	// ����� ������
	return create_token(text[*ind], "������");
}

// �������� ���������� state_begin
Token state_cbracket1(string text[], string value[], int* curState, int* ind) {
	// ���� ������ ���������
	if (*curState == CBRACKET1) {
		// ���� ������� ELSE
		if (value[*ind] == "�������_ELSE") {
			// ����� ��������� � ����� ������� ��� ���������� ��������� ����� else
			*curState = ELSE;
			(*ind)++;
			return state_else(text, value, curState, ind);
		}
		// ���� ������� ������
		if (value[*ind] == "������") {
			// ����� ��������� � ����� ������� ��� ���������� ������ ��
			*curState = SEMICOLON;
			(*ind)++;
			return state_semicolon(text, value, curState, ind);
		}
	}
	// ����� ������
	return create_token(text[*ind], "������");
}

// �������� ���������� state_begin
Token state_else(string text[], string value[], int* curState, int* ind) {
	// ���� ������ ���������
	if (*curState == ELSE) {
		// ���� ������� �������������
		if (value[*ind] == "���������") {
			// ����� ��������� � ����� ������� ��� ���������� ��������� ����� ��������������
			*curState = NAME2;
			(*ind)++;
			return state_name2(text, value, curState, ind);
		}
	}
	// ����� ������
	return create_token(text[*ind], "������");
}

// �������� ���������� state_begin
Token state_name2(string text[], string value[], int* curState, int* ind) {
	// ���� ������ ���������
	if (*curState == NAME2) {
		// ���� ������� �������
		if (value[*ind] == "�������") {
			// ����� ��������� � ����� ������� ��� ���������� ��������� ����� �������
			*curState = OBRACKET2;
			(*ind)++;
			return state_obracket2(text, value, curState, ind);
		}
	}
	// ����� ������
	return create_token(text[*ind], "������");
}

// �������� ���������� state_begin
Token state_obracket2(string text[], string value[], int* curState, int* ind) {
	// ���� ������ ���������
	if (*curState == OBRACKET2) {
		// ���� ������� ���� � �����
		if (value[*ind] == "�����") {
			// ����� ��������� � ����� ������� ��� ���������� ��������� ����� ����� � ������
			*curState = SIGN_INT;
			(*ind)++;
			return state_sign_and_int(text, value, curState, ind);
		}
	}
	// ����� ������
	return create_token(text[*ind], "������");
}

// �������� ���������� state_begin
Token state_sign_and_int(string text[], string value[], int* curState, int* ind) {
	// ���� ������ ���������
	if (*curState == SIGN_INT) {
		// ���� ������� �������
		if (value[*ind] == "�������") {
			// ����� ��������� � ����� ������� ��� ���������� ��������� ����� �������
			*curState = CBRACKET2;
			(*ind)++;
			return state_cbracket2(text, value, curState, ind);
		}
	}
	// ����� ������
	return create_token(text[*ind], "������");
}

// �������� ���������� state_begin
Token state_cbracket2(string text[], string value[], int* curState, int* ind) {
	// ���� ������ ���������
	if (*curState == CBRACKET2) {
		// ���� ������� ������
		if (value[*ind] == "������") {
			// ����� ��������� � ����� ������� ��� ���������� ������ ��
			*curState = SEMICOLON;
			(*ind)++;
			return state_semicolon(text, value, curState, ind);
		}
	}
	// ����� ������
	return create_token(text[*ind], "������");
}

// �������� ���������� state_begin
Token state_semicolon(string text[], string value[], int* curState, int* ind) {
	//�������� ��������� ��������� - ������, ��� �� ��
	return create_token("�����", "�����");
}