#include "header.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "russian");

	char bufer[255] = "";			// ����� ��� �������� ��������� �� ����� ������
	char result[10] = "ACCEPT";		// ������ �������� ������ � ����� ���� �� �������� (ACCEPT ��� RELECT)
	unsigned int buf_length = 0;	// ����� ������

	// ��������� ������� ������ �� ����� "INPUT.txt"
	fstream FileInput;
	FileInput.open("INPUT.txt", std::ios::in);

	// ���� ���� �� ��� ������, ��������� ������ ��������� � �������
	if (!FileInput.is_open()){
		FileInput.close();
		cout << "������. ���� \"INPUT.txt\" �� ������," << endl;
		return -1;
	}
		// ��������� �� ����� �������� ������
		FileInput.read(bufer, 255);

		// ��������� ����
		FileInput.close();

		// ���������� ����� ������
		buf_length = strlen(bufer);

		// ��������������� ����� ������ � �������
		cout << "���������� �����:" << endl << bufer << endl << endl;

		// ���� ��������������
		cout << "���� ��������������:" << endl << func_Translit(bufer, buf_length) << endl << endl;

		// ����������� ����
		func_Leks();

		// ���� ������������� �������� ����
		func_KeyWordIdent();

		// �������������� ����
		func_Syntax();

		// ��������� ���� "OUTPUT.txt" ��� ������ ���������� ��������������� ������� ������ (ACCEPT ��� RELECT)
		FileInput.open("OUTPUT.txt", std::ios::out);

		// ���� ���� �� ��� ������, ��������� ������ ��������� � �������
		if (!FileInput.is_open()){
			FileInput.close();
			cout << "������. ���� \"OUTPUT.txt\" �� ������," << endl;
			return -1;
		}
		// �������� ��������� ������ � ���� "OUTPUT.txt"
		FileInput.write(result, 10);
		FileInput.close();
	return 0;
}