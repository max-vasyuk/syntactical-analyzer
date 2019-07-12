#include "header.h"

// toLower - ����������� ������ ���� string � ������� ��������
//________________________________________________________________________________________________________
// ����:  string - ������, ������� ��������� �������� � ������� ��������
//________________________________________________________________________________________________________
// �����: string - ��������������� � ������� �������� ������
//________________________________________________________________________________________________________
string toLower(string s) {
	char* cstr = new char[s.length() + 1];
	strcpy(cstr, s.c_str());
	for (int i = 0; i < s.length(); i++)
		cstr[i] = tolower(cstr[i]);
	return string(cstr);
}

// func_KeyWordIdent- ���� ������������� �������� ����
//________________________________________________________________________________________________________
// ����:  vector<Token> leks_result - ������ �������� (������, �����)  - ��������� ������������ �����������
//________________________________________________________________________________________________________
// �����: vector<Token> - ��������� ������������� �������� ���� - ������� ���� (������, ����� �����)
//________________________________________________________________________________________________________
vector<Token> func_KeyWordIdent(vector<Token> leks_result) {
	//�������� ����� ����� �������
	vector<string> keywords{ "absolute", "and", "array", "asm", "begin", "case", "const", "constructor", "div", "goto", "do",
							 "downto", "destructor", "end", "exports", "external", "file", "for", "forward", "function", "in",
							 "implementation", "inline", "interrupt", "interface", "inherited", "label", "library", "mod", "nil",
							 "not", "of", "or", "object", "packed", "procedure", "program", "record", "repeat", "set", "shl",
							 "shr", "string", "to", "type", "unit", "until", "uses", "var", "while", "with", "xor" };
	//��������� �����
	vector<Token> result;
	//��������� �� ���� ������������ �������� � ����� ��������������� ���� �������� �����
	for (int i = 0; i < leks_result.size(); i++) {
		//������� � ��������� �������, ���� ������� �� �������� ���������������
		if (leks_result[i].leks != "�������������") {
			result.push_back(create_token(leks_result[i].input_string, leks_result[i].leks));
			continue;
		}
		//��������� if
		if (toLower(leks_result[i].input_string) == "if") {
			result.push_back(create_token(leks_result[i].input_string, "�������_IF"));
			continue;
		}
		//��������� then
		if (toLower(leks_result[i].input_string) == "then") {
			result.push_back(create_token(leks_result[i].input_string, "�������_THEN"));
			continue;
		}
		//��������� else
		if (toLower(leks_result[i].input_string) == "else") {
			result.push_back(create_token(leks_result[i].input_string, "�������_ELSE"));
			continue;
		}
		bool flag = 0; //false - ���� �� �������� ���������� �������������� � ��������� �������
		for (int j = 0; j < keywords.size(); j++) {
			//���� �������� �����
			if (toLower(leks_result[i].input_string) == keywords[j]) {
				result.push_back(create_token(leks_result[i].input_string, "������"));
				flag = 1;
				break;
			}
		}
		//���� �� �������� �����
		if (!flag)
			result.push_back(create_token(leks_result[i].input_string, "���������"));
	}
	//���������� ���������
	return result;
}