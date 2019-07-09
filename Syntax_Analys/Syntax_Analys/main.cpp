#include "header.h"

int main()
{
	setlocale(LC_ALL, "russian");

	string input_text = "";			    // ���� ��������� �� ����� �����
	string line = "";					// ��� ���������� ����� ������
	char result[10] = "ACCEPT";		// ������ �������� ������ � ����� ���� �� �������� (ACCEPT ��� REJECT)
	unsigned int buf_length = 0;	// ����� ������

	// ��������� ������� ������ �� ����� "INPUT.txt"
	fstream file_input;
	file_input.open("INPUT.txt", std::ios::in);

	// ���� ���� �� ��� ������, ��������� ������ ��������� � �������
	if (!file_input.is_open()) {
		file_input.close();
		cout << "������. ���� \"INPUT.txt\" �� ������," << endl;
		return -1;
	}
	
	// ��������� �� ����� �������� ������
	while (getline(file_input, line)) {
		input_text = input_text + line + '\n';
	}

	// ��������� ����
	file_input.close();

	// ���������� ����� ������
	buf_length = input_text.size();

	// ��������������� ����� ������ � �������
	cout << "���������� �����:\n" << input_text << "\n";

	// ���� ��������������
	cout << "���� ��������������:\n" << func_Translit(input_text, buf_length) << "\n\n";

	// ����������� ����
	func_Leks();

	// ���� ������������� �������� ����
	func_KeyWordIdent();

	// �������������� ����
	func_Syntax();

	// ��������� ���� "OUTPUT.txt" ��� ������ ���������� ��������������� ������� ������ (ACCEPT ��� RELECT)
	file_input.open("OUTPUT.txt", std::ios::out);

	// ���� ���� �� ��� ������, ��������� ������ ��������� � �������
	if (!file_input.is_open()) {
		file_input.close();
		cout << "������. ���� \"OUTPUT.txt\" �� ������," << endl;
		return -1;
	}
	// �������� ��������� ������ � ���� "OUTPUT.txt"
	file_input.write(result, sizeof(result));
	file_input.close();
	return 0;
}