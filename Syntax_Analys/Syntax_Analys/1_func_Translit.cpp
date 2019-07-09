#include "header.h"
using namespace std;

// func_Translit - блок транслитерации
//__________________________________________________________________
// ВХОД:  char *bufer - символьная строка из файла
//		  buf_length  - длина строки из файла (кол-во символов в ней)
//__________________________________________________________________
// ВЫХОД: string checker - итоговый набор лексемм
//__________________________________________________________________
string func_Translit(char *bufer, unsigned int buf_length)
{
	string checker = "";	// строка для хранения результатов работы функции
	// массив цифр
	char numbers[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	// массив латинских букв
	char letters[52] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
						 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
	bool flag;	// проверочный флаг для принятия решений

	// основной цикл по кол-ву символов в строке bufer
	// последовательно сверяем его с необходимыми символами
	// и присваиваем соответствующую лексемму
	// если совпадений не было, присваиваем символу
	// статус "ОШИБКА"
	for (int i = 0; i < buf_length; i++){
		flag = false;
		if (bufer[i] == ' '){
			checker.append("ПРОБЕЛ ");
			continue;
		}
		if (bufer[i] == ';'){
			checker.append("ТЧКЗПТ ");
			continue;
		}
		if (bufer[i] == '='){
			checker.append("РАВНО ");
			continue;
		}
		for (unsigned int num_index = 0; num_index < 10; num_index++){
			if (bufer[i] == numbers[num_index]){
				checker.append("ЦИФРА ");
				flag = true;
				break;
			}
		}
		if (flag) continue;
		for (unsigned int let_index = 0; let_index < 52; let_index++){
			if (bufer[i] == letters[let_index]){
				checker.append("БУКВА ");
				flag = true;
				break;
			}
		}
		if (!flag) checker.append("ОШИБКА ");
	}
	return checker;	// возвращаем полученные лексеммы далее в работу
}