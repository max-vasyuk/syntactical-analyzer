#include "header.h"
using namespace std;

// func_Translit - ���� ��������������
//__________________________________________________________________
// ����:  char *bufer - ���������� ������ �� �����
//		  buf_length  - ����� ������ �� ����� (���-�� �������� � ���)
//__________________________________________________________________
// �����: string checker - �������� ����� �������
//__________________________________________________________________
string func_Translit(char *bufer, unsigned int buf_length)
{
	string checker = "";	// ������ ��� �������� ����������� ������ �������
	// ������ ����
	char numbers[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	// ������ ��������� ����
	char letters[52] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
						 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
	bool flag;	// ����������� ���� ��� �������� �������

	// �������� ���� �� ���-�� �������� � ������ bufer
	// ��������������� ������� ��� � ������������ ���������
	// � ����������� ��������������� ��������
	// ���� ���������� �� ����, ����������� �������
	// ������ "������"
	for (int i = 0; i < buf_length; i++){
		flag = false;
		if (bufer[i] == ' '){
			checker.append("������ ");
			continue;
		}
		if (bufer[i] == ';'){
			checker.append("������ ");
			continue;
		}
		if (bufer[i] == '='){
			checker.append("����� ");
			continue;
		}
		for (unsigned int num_index = 0; num_index < 10; num_index++){
			if (bufer[i] == numbers[num_index]){
				checker.append("����� ");
				flag = true;
				break;
			}
		}
		if (flag) continue;
		for (unsigned int let_index = 0; let_index < 52; let_index++){
			if (bufer[i] == letters[let_index]){
				checker.append("����� ");
				flag = true;
				break;
			}
		}
		if (!flag) checker.append("������ ");
	}
	return checker;	// ���������� ���������� �������� ����� � ������
}