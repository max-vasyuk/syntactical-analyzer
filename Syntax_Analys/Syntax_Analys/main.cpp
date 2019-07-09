#include "header.h"

int main()
{
	setlocale(LC_ALL, "russian");

	string input_text = "";			// ���� ��������� �� ����� �����
	char result[10] = "ACCEPT";		// ������ �������� ������ � ����� ���� �� �������� (ACCEPT ��� REJECT)
	unsigned int buf_length = 0;	// ����� ������

	// ��������� ������� ������ �� ����� "INPUT.txt"
	fstream file_input;
	file_input.open("INPUT.txt", ios::in);

	// ���� ���� �� ��� ������, ��������� ������ ��������� � �������
	if (!file_input.is_open()) {
		cout << "������. ���� \"INPUT.txt\" �� ������," << endl;
		return -1;
	}
	
	// ��������� �� ����� �������� ������
	getline(file_input, input_text);

	// ��������� ����
	file_input.close();

	// ���������� ����� ������
	buf_length = input_text.size();

	// ��������������� ����� ������ � �������
	cout << "C��������� �����:\n" << input_text << "\n\n";

	// ���� ��������������
	cout << "���� ��������������:\n" << func_Translit(input_text, buf_length) << "\n\n";

	// ����������� ����
	func_Leks();

	// ���� ������������� �������� ����
	func_KeyWordIdent();

	// �������������� ����
	func_Syntax();

	// ��������� ���� "OUTPUT.txt" ��� ������ ���������� ��������������� ������� ������ (ACCEPT ��� RELECT)
	file_input.open("OUTPUT.txt", ios::out);

	// ���� ���� �� ��� ������, ��������� ������ ��������� � �������
	if (!file_input.is_open()) {
		cout << "������. ���� \"OUTPUT.txt\" �� ������," << endl;
		return -1;
	}

	// �������� ��������� ������ � ���� "OUTPUT.txt" � ������� ���
	file_input.write(result, sizeof(result));
	file_input.close();
	return 0;
}