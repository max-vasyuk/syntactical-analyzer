#include "header.h"

int main() {
	setlocale(LC_ALL, "russian");
	// весь считанный из файла текст
	string input_text = "";
	// массив символов примет в итоге одно из значений (ACCEPT или REJECT)
	string result = "ACCEPT";
	// считываем входные данные из файла "INPUT.txt"
	fstream file_input;
	file_input.open("INPUT.txt", ios::in);

	// если файл не был открыт, завершаем работу программы с ошибкой
	if (!file_input.is_open()) {
		cout << "Ошибка. Файл \"INPUT.txt\" не найден," << endl;
		return -1;
	}
	// считываем из файла исходные данные
	getline(file_input, input_text);
	// закрываем файл
	file_input.close();

	// предварительный вывод строки в консоль
	cout << "Cодержимое файла:\n" << input_text << "\n\n";
	// длина строки
	int length = input_text.size();

	// блок транслитерации: вызов и вывод результата на экран

	cout << "Блок транслитерации:\n";
	vector<Token> translit_result = func_Translit(input_text);
	for (int i = 0; i < length; i++) {
		cout << "(" << translit_result[i].input_string << ", " << translit_result[i].leks << ")";
		if (i != length - 1) cout << ", ";
		if (translit_result[i].leks == "ОШИБКА") result = "REJECT";
	}
	
	// лексический блок
	cout << "\n\nЛексический блок:\n";
	vector<Token> leks_result;
	if (result != "REJECT") {
		leks_result = func_Leks(translit_result);
		length = leks_result.size();
		for (int i = 0; i < leks_result.size(); i++) {
			cout << "(" << leks_result[i].input_string << ", " << leks_result[i].leks << ")";
			if (i != length - 1) cout << ", ";
			if (leks_result[i].leks == "ОШИБКА") {
				result = "REJECT";
				break;
			}
		}
	}
	
	// блок идентификации ключевых слов
	cout << "\n\nБлок идентификации ключевых слов:\n";
	vector<Token> keyIdent_result;
	if (result != "REJECT") {
		keyIdent_result = func_KeyWordIdent(leks_result);
		for (int i = 0; i < keyIdent_result.size(); i++) {
			cout << "(" << keyIdent_result[i].input_string << ", " << keyIdent_result[i].leks << ")";
			if (i != length - 1) cout << ", ";
			if (keyIdent_result[i].leks == "ОШИБКА") {
				result = "REJECT";
				break;
			}
		}
	}

	// синтаксический блок
	cout << "\n\nСинтаксический блок:\n";
	if (result != "REJECT") {
		result = func_Syntax(keyIdent_result);
		cout << result << endl;
	}

	// открываем файл "OUTPUT.txt" для записи результата синтаксического анализа строки (ACCEPT или RELECT)
	file_input.open("OUTPUT.txt", ios::out);

	// если файл не был открыт, завершаем работу программы с ошибкой
	if (!file_input.is_open()) {
		cout << "Ошибка. Файл \"OUTPUT.txt\" не найден," << endl;
		return -1;
	}

	// записали результат работы в файл "OUTPUT.txt" и закрыли его
	file_input.write(result.c_str(), 7);
	file_input.close();
	return 0;
}