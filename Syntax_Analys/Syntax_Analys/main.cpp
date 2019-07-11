#include "header.h"

int main() {
	setlocale(LC_ALL, "russian");
	// ���� ��������� �� ����� �����
	string input_text = "";
	// ������ �������� ������ � ����� ���� �� �������� (ACCEPT ��� REJECT)
	string result = "ACCEPT";
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

	// ��������������� ����� ������ � �������
	cout << "C��������� �����:\n" << input_text << "\n\n";
	// ����� ������
	int length = input_text.size();

	// ���� ��������������: ����� � ����� ���������� �� �����

	cout << "���� ��������������:\n";
	std::vector<Token> translit_result = func_Translit(input_text);
	for (int i = 0; i < length; i++) {
		cout << "(" << translit_result[i].input_string << ", " << translit_result[i].leks << ")";
		if (i != length - 1) cout << ", ";
		if (translit_result[i].leks == "������") result = "REJECT";
	}
	
	// ����������� ����
	cout << "\n\n����������� ����:\n";
	if (result != "REJECT") {
		std::vector<Token> leks_result = func_Leks(translit_result);
		length = leks_result.size();
		for (int i = 0; i < leks_result.size(); i++) {
			cout << "(" << leks_result[i].input_string << ", " << leks_result[i].leks << ")";
			if (i != length - 1) cout << ", ";
			if (leks_result[i].leks == "������") {
				result = "REJECT";
				break;
			}
		}
	}
	
	// ���� ������������� �������� ����
	cout << "\n\n���� ������������� �������� ����:\n";
	if (result != "REJECT") {
		func_KeyWordIdent();
	}

	// �������������� ����
	cout << "\n\n�������������� ����:\n";
	func_Syntax();
	
	// ��������� ���� "OUTPUT.txt" ��� ������ ���������� ��������������� ������� ������ (ACCEPT ��� RELECT)
	file_input.open("OUTPUT.txt", ios::out);

	// ���� ���� �� ��� ������, ��������� ������ ��������� � �������
	if (!file_input.is_open()) {
		cout << "������. ���� \"OUTPUT.txt\" �� ������," << endl;
		return -1;
	}

	// �������� ��������� ������ � ���� "OUTPUT.txt" � ������� ���
	file_input.write(result.c_str(), sizeof(result));
	file_input.close();
	return 0;
}