#include "header.h"

// func_Translit - блок транслитерации
//__________________________________________________________________
// ВХОД:  string buffer - символьная строка из файла
//		  int buf_length  - длина строки из файла (кол-во символов в ней)
//__________________________________________________________________
// ВЫХОД: string checker - итоговый набор лексем
//__________________________________________________________________
string func_Translit(string buffer, int buf_length)
{
	string checker = "";	// строка для хранения результатов работы функции
	// цикл по кол-ву символов в строке buffer
	// последовательно сверяем его с символами
	// и присваиваем соответствующую лексему
	// если совпадений не было, присваиваем символу
	// статус "ОШИБКА"
	for (int i = 0; i < buf_length; i++){
		switch (buffer[i])
		{
			case ' ': checker.append("ПРОБЕЛ "); break;
			case ';': checker.append("ТЧКЗПТ "); break;
			case '=': checker.append("РАВНО "); break;
			case '\n': checker.append("НВСТРК "); break;
			default:
				if (buffer[i] >= 'A' && buffer[i] <= 'Z' || buffer[i] >= 'a' && buffer[i] <= 'z')
					checker.append("БУКВА ");
				else if (buffer[i] >= '0' && buffer[i] <= '9')
					checker.append("ЦИФРА ");
				else 
					checker.append("ОШИБКА ");
		}
	}
	return checker;	// возвращаем полученные лексеммы далее в работу
}