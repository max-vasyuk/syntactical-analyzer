#include "header.h"

// func_Translit - ���� ��������������
//__________________________________________________________________
// ����:  string buffer - ���������� ������ �� �����
//		  int buf_length  - ����� ������ �� ����� (���-�� �������� � ���)
//__________________________________________________________________
// �����: string checker - �������� ����� ������
//__________________________________________________________________
string func_Translit(string buffer, int buf_length)
{
	string checker = "";	// ������ ��� �������� ����������� ������ �������
	// ���� �� ���-�� �������� � ������ buffer
	// ��������������� ������� ��� � ���������
	// � ����������� ��������������� �������
	// ���� ���������� �� ����, ����������� �������
	// ������ "������"
	for (int i = 0; i < buf_length; i++){
		string cur_string = "(";
		cur_string.push_back(buffer[i]);
		switch (buffer[i])
		{
		case ' ': cur_string.append(",������)"); break;
			case ';': cur_string.append(",������)"); break;
			case '=': cur_string.append(",�����)"); break;
			default:
				if (buffer[i] >= 'A' && buffer[i] <= 'Z' || buffer[i] >= 'a' && buffer[i] <= 'z')
					cur_string.append(",�����)");
				else if (buffer[i] >= '0' && buffer[i] <= '9')
					cur_string.append(",�����)");
				else cur_string.append(",������)");
		}
		if (i != buf_length - 1)
			cur_string.append(", ");
		checker.append(cur_string);
	}
	return checker;	// ���������� ���������� �������� ����� � ������
}