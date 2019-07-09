#include "header.h"

int main()
{
	setlocale(LC_ALL, "russian");

	string input_text = "";			// весь считанный из файла текст
	char result[10] = "ACCEPT";		// массив символов примет в итоге одно из значений (ACCEPT или REJECT)

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

	// блок транслитерации
	string translit_result = func_Translit(input_text);
	cout << "Блок транслитерации:\n" << translit_result << "\n\n";

	// лексический блок
	string leks_result = func_Leks(translit_result);
	cout << "Лексический блок:\n" << leks_result << "\n\n";

	// блок идентификации ключевых слов
	func_KeyWordIdent();

	// синтаксический блок
	func_Syntax();

	// открываем файл "OUTPUT.txt" для записи результата синтаксического анализа строки (ACCEPT или RELECT)
	file_input.open("OUTPUT.txt", ios::out);

	// если файл не был открыт, завершаем работу программы с ошибкой
	if (!file_input.is_open()) {
		cout << "Ошибка. Файл \"OUTPUT.txt\" не найден," << endl;
		return -1;
	}

	// записали результат работы в файл "OUTPUT.txt" и закрыли его
	file_input.write(result, sizeof(result));
	file_input.close();
	return 0;
}