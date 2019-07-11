#include "header.h"

// func_Translit - ���� ��������������
//__________________________________________________________________
// ����:  string buffer - ���������� ������ �� �����
//__________________________________________________________________
// �����: vector<Token> - ������ �������� ���� (������, ����� �������)
//__________________________________________________________________
std::vector<Token> func_Translit(string buffer) {
	// ����� ������
	int length = buffer.size();
	// ������ ��� ���������� ����������� ������
	std::vector<Token> tokens;

	// ���� �� ������ buffer, ����������� ������� ������� �������
	// ���� ���������� �� ���� - ����������� ������ "������"
	for (int i = 0; i < length; i++) {
		Token tmp;
		tmp.input_string = buffer[i];
		switch (buffer[i]) {
			case ' ': tmp.leks = "������"; break;
			case ';': tmp.leks = "������"; break;
			case ':': tmp.leks = "���������"; break;
			case '=': tmp.leks = "�����"; break;
			case '(': tmp.leks = "�������"; break;
			case ')': tmp.leks = "�������"; break;
			case '_': tmp.leks = "�������"; break;
			case '-': case '+': tmp.leks = "����"; break;
			default:
				if (buffer[i] >= 'A' && buffer[i] <= 'Z' || buffer[i] >= 'a' && buffer[i] <= 'z')
					tmp.leks = "�����";
				else if (buffer[i] >= '0' && buffer[i] <= '9') tmp.leks = "�����";
				else tmp.leks = "������";
		}
		tokens.push_back(tmp);
	}
	// ���������� ���������� ������� ����� � ������
	return tokens;
}