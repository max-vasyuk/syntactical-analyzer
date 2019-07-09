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
		switch (buffer[i])
		{
			case ' ': checker.append("������ "); break;
			case ';': checker.append("������ "); break;
			case '=': checker.append("����� "); break;
			case '\n': checker.append("������ "); break;
			default:
				if (buffer[i] >= 'A' && buffer[i] <= 'Z' || buffer[i] >= 'a' && buffer[i] <= 'z')
					checker.append("����� ");
				else if (buffer[i] >= '0' && buffer[i] <= '9')
					checker.append("����� ");
				else 
					checker.append("������ ");
		}
	}
	return checker;	// ���������� ���������� �������� ����� � ������
}