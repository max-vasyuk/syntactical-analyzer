#include "header.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "russian");

	char bufer[255] = "";			// буфер для хранения считанной из файла строки
	char result[10] = "ACCEPT";		// массив символов примет в итоге одно из значений (ACCEPT или RELECT)
	unsigned int buf_length = 0;	// длина строки

	// считываем входные данные из файла "INPUT.txt"
	fstream FileInput;
	FileInput.open("INPUT.txt", std::ios::in);

	// если файл не был открыт, завершаем работу программы с ошибкой
	if (!FileInput.is_open()){
		FileInput.close();
		cout << "Ошибка. Файл \"INPUT.txt\" не найден," << endl;
		return -1;
	}
		// считываем из файла исходные данные
		FileInput.read(bufer, 255);

		// закрываем файл
		FileInput.close();

		// определяем длину строки
		buf_length = strlen(bufer);

		// предварительный вывод строки в консоль
		cout << "содержимое файла:" << endl << bufer << endl << endl;

		// блок транслитерации
		cout << "блок транслитерации:" << endl << func_Translit(bufer, buf_length) << endl << endl;

		// лексический блок
		func_Leks();

		// блок идентификации ключевых слов
		func_KeyWordIdent();

		// синтаксический блок
		func_Syntax();

		// открываем файл "OUTPUT.txt" для записи результата синтаксического анализа строки (ACCEPT или RELECT)
		FileInput.open("OUTPUT.txt", std::ios::out);

		// если файл не был открыт, завершаем работу программы с ошибкой
		if (!FileInput.is_open()){
			FileInput.close();
			cout << "Ошибка. Файл \"OUTPUT.txt\" не найден," << endl;
			return -1;
		}
		// записали результат работы в файл "OUTPUT.txt"
		FileInput.write(result, 10);
		FileInput.close();
	return 0;
}