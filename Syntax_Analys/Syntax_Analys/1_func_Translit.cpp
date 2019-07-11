#include "header.h"

// func_Translit - блок транслитерации
//__________________________________________________________________
// ВХОД:  string buffer - символьная строка из файла
//__________________________________________________________________
// ВЫХОД: string checker - итоговый набор лексем
//__________________________________________________________________
string func_Translit(string buffer) {
	// строка для хранения результатов работы функции
	string checker = "";	
	// цикл по строке buffer, присваиваем каждому символу лексему
	// если совпадений не было - присваиваем статус "ОШИБКА"
	for (int i = 0; i < buffer.size(); i++) {
		string cur_string = "(";
		cur_string.push_back(buffer[i]);
		switch (buffer[i]) {
			case ' ': cur_string.append(",ПРОБЕЛ)"); break;
			case ';': cur_string.append(",ТЧКЗПТ)"); break;
			case ':': cur_string.append(",ДВОЕТОЧИЕ)"); break;
			case '=': cur_string.append(",РАВНО)"); break;
			case '(': cur_string.append(",ОСКОБКА)"); break;
			case ')': cur_string.append(",ЗСКОБКА)"); break;
			case '_': cur_string.append(",ПОДЧЕРК)"); break;
			case '-': case '+': cur_string.append(",ЗНАК)"); break;
			default:
				if (buffer[i] >= 'A' && buffer[i] <= 'Z' || buffer[i] >= 'a' && buffer[i] <= 'z')
					cur_string.append(",БУКВА)");
				else if (buffer[i] >= '0' && buffer[i] <= '9')
					cur_string.append(",ЦИФРА)");
				else cur_string.append(",ОШИБКА)");
		}
		if (i != buffer.size() - 1)
			cur_string.append(", ");
		checker.append(cur_string);
	}
	// возвращаем полученные лексемы далее в работу
	return checker;	
}