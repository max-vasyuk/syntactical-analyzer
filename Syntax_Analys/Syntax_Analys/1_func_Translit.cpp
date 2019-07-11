#include "header.h"

// func_Translit - блок транслитерации
//__________________________________________________________________
// ВХОД:  string buffer - символьная строка из файла
//__________________________________________________________________
// ВЫХОД: vector<Token> - массив кортежей вида (символ, класс символа)
//__________________________________________________________________
std::vector<Token> func_Translit(string buffer) {
	// длина строки
	int length = buffer.size();
	// массив для сохранения результатов работы
	std::vector<Token> tokens;

	// цикл по строке buffer, присваиваем каждому символу лексему
	// если совпадений не было - присваиваем статус "ОШИБКА"
	for (int i = 0; i < length; i++) {
		Token tmp;
		tmp.input_string = buffer[i];
		switch (buffer[i]) {
			case ' ': tmp.leks = "ПРОБЕЛ"; break;
			case ';': tmp.leks = "ТЧКЗПТ"; break;
			case ':': tmp.leks = "ДВОЕТОЧИЕ"; break;
			case '=': tmp.leks = "РАВНО"; break;
			case '(': tmp.leks = "ОСКОБКА"; break;
			case ')': tmp.leks = "ЗСКОБКА"; break;
			case '_': tmp.leks = "ПОДЧЕРК"; break;
			case '-': case '+': tmp.leks = "ЗНАК"; break;
			default:
				if (buffer[i] >= 'A' && buffer[i] <= 'Z' || buffer[i] >= 'a' && buffer[i] <= 'z')
					tmp.leks = "БУКВА";
				else if (buffer[i] >= '0' && buffer[i] <= '9') tmp.leks = "ЦИФРА";
				else tmp.leks = "ОШИБКА";
		}
		tokens.push_back(tmp);
	}
	// возвращаем полученные лексемы далее в работу
	return tokens;
}