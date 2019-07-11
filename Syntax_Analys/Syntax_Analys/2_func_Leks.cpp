#include "header.h"
#include "leks.h"

// func_Leks - Лексический блок
//________________________________________________________________________________________________________
// ВХОД:  string translit_result - строка после транслитерации
//________________________________________________________________________________________________________
// ВЫХОД: string - результат лексического анализа
//________________________________________________________________________________________________________
string func_Leks(string translit_result) {
	// переменные для разбора результатов транслитерации
	char text[80];
	string leks[80];
	// результат транслитерации
	int length = parse_translit_result(translit_result, text, leks);
	// вызов функции анализатора
	return func_analyze(text, leks, length);
}

// parse_translit_result - функция для распознавания результатов транслитерации
//________________________________________________________________________________________________________
// ВХОД: string translit_result - строка после транслитерации
//		 char text[] - распознаваемая строка (переменная для записи)
//       string tr_keys[] - лексемы транслитерации (переменная для записи)
//________________________________________________________________________________________________________
// ВЫХОД: int - длина распознаваемой строки
//________________________________________________________________________________________________________
int parse_translit_result(string translit_result, char text[], string tr_keys[]) {
	// индекс рассматриваемого символа, индекс текущего символа в строке результата транслитерации
	int ind = 0, cur = 1;

	// цикл по строке с результатом транслитерации для сохранения лексем
	while (cur < translit_result.size()) {
		// запоминаем рассматриваемый символ
		text[ind] = translit_result[cur];
		// циклом считываем лексему (от запятой до скобки)
		int i = cur + 2;
		for (; translit_result[i] != ')'; i++)
			tr_keys[ind].push_back(translit_result[i]);
		// переход к следующему символу
		cur = i + 4;
		ind++;
	}
	// вернем положение последнего символа (фактически - длину)
	return ind;
}

// func_analyze - функция для распознавания результатов транслитерации
//________________________________________________________________________________________________________
// ВХОД: char text[] - распознаваемая строка
//       string tr_keys[] - лексемы транслитерации
//       int length - длина распознаваемой строки
//________________________________________________________________________________________________________
// ВЫХОД: string - строка с результатом лексического анализа
//________________________________________________________________________________________________________
string func_analyze(char text[], string tr_keys[], int length) {
	// текущее состояние - начало; индекс текущего символа - 0
	int curState = BEGIN, ind = 0;
	// строка, в которую будет записываться результат
	string result_string = "";
	// массив (вектор) с результатами распознавания (токенами)
	std::vector<Token> tokens;
	// вызов функций для состояний конечного автомата
	tokens.push_back(state_begin(text, tr_keys, &curState, &ind));
	tokens.push_back(state_space1(text, tr_keys, &curState, &ind));
	tokens.push_back(state_space2(text, tr_keys, &curState, &ind));
	tokens.push_back(state_space3(text, tr_keys, &curState, &ind));
	tokens.push_back(state_space4(text, tr_keys, &curState, &ind));
	tokens.push_back(state_name1(text, tr_keys, &curState, &ind));
	Token obracket1{ "(", "ОСКОБКА" };
	tokens.push_back(obracket1);
	tokens.push_back(state_id3(text, tr_keys, &curState, &ind));
	Token сbracket1{ ")", "ЗСКОБКА" };
	tokens.push_back(сbracket1);
	tokens.push_back(state_cbracket1(text, tr_keys, &curState, &ind));
	// либо встречаем ; и заканчиваем распознавание, либо распознаем else
	if (curState != SEMICOLON) {
		tokens.push_back(state_space6(text, tr_keys, &curState, &ind));
		Token obracket2{ "(", "ОСКОБКА" };
		tokens.push_back(obracket2);
		tokens.push_back(state_sign_and_int(text, tr_keys, &curState, &ind));
		Token сbracket2{ ")", "ЗСКОБКА" };
		tokens.push_back(сbracket2);
		tokens.push_back(state_cbracket2(text, tr_keys, &curState, &ind));
	}
	// если остались символы после ;
	if (ind <= length - 1) {
		Token tkn = state_semicolon(text, tr_keys, &curState, &ind);
		if (tkn.input_string != "КОНЕЦ")
			tokens.push_back(tkn);
	}
	// сохраняем результаты в строку
	for (int i = 0; i < tokens.size(); i++) {
		result_string.append("(" + tokens[i].input_string + ", " + tokens[i].leks + ")");
		if (tokens[i].leks == "ОШИБКА") break;
		if (i != tokens.size() - 1) result_string.append(", ");
	}
	// возврат результата лексического анализа
	return result_string;
}

// create_token - функция для создания токена распознавания
//________________________________________________________________________________________________________
// ВХОД: string str - строка
//       string value - соответствующее ей значение
//________________________________________________________________________________________________________
// ВЫХОД: Token - токен, содержащий str, value
//________________________________________________________________________________________________________
Token create_token(string str, string value) {
	Token tkn;
	tkn.input_string = str;
	tkn.leks = value;
	return tkn;
}

// state_begin - функция для состояния "Начало"
//________________________________________________________________________________________________________
// ВХОД: char symb[] - распознаваемая строка
//		 string value[] - результаты транслитерации
//		 int* curState - текущее состояние
//		 int* ind - текущий индекс в строке
//________________________________________________________________________________________________________
// ВЫХОД: Token - токен, содержащий str, value
//________________________________________________________________________________________________________
Token state_begin(char symb[], string value[], int* curState, int* ind) {
	// если верное состояние
	if (*curState == BEGIN) {
		// если получен ПРОБЕЛ
		if (value[*ind] == "ПРОБЕЛ") {
			// читаем дальше в этом же состоянии, вызов этой же фукнции
			(*ind)++;
			return state_begin(symb, value, curState, ind);
		}
		// если получена БУКВА
		if (value[*ind] == "БУКВА") {
			// смена состояния и вызов функции для считывания if
			*curState = IF;
			return state_if(symb, value, curState, ind);
		}
	}
	// иначе ОШИБКА
	return create_token(string(1, symb[*ind]), "ОШИБКА");
}

// state_if - функция для состояния "IF"
//________________________________________________________________________________________________________
// ВХОД: char symb[] - распознаваемая строка
//		 string value[] - результаты транслитерации
//		 int* curState - текущее состояние
//		 int* ind - текущий индекс в строке
//       string curString - строка для накопления результата считывания
//________________________________________________________________________________________________________
// ВЫХОД: Token - токен, содержащий str, value
//________________________________________________________________________________________________________
Token state_if(char symb[], string value[], int* curState, int* ind, string curString) {
	// если верное состояние
	if (*curState == IF) {
		// получена БУКВА
		if (value[*ind] == "БУКВА") {
			// считываем i или I или считываем f или F
			if (curString == "" && (char)tolower(symb[*ind]) == 'i' || 
				curString.size() == 1 && (char)tolower(symb[*ind]) == 'f') {
				curString.push_back(symb[*ind]);
				(*ind)++;
				// читаем дальше, вызвав эту же функцию
				return state_if(symb, value, curState, ind, curString);
			}
			// иначе ОШИБКА
			return create_token(string(1, symb[*ind]), "ОШИБКА");
		}
		// получен ПРОБЕЛ при считанном if
		if (curString.size() == 2 && value[*ind] == "ПРОБЕЛ") {
			// смена состояния
			*curState = SPACE1;
			// возврат результата
			return create_token(curString, "ИДЕНТИФИКАТОР");
		}
	}
	// иначе ОШИБКА
	return create_token(string(1, symb[*ind]), "ОШИБКА");
}

// описание аналогично state_begin
Token state_space1(char symb[], string value[], int* curState, int* ind) {
	// если верное состояние
	if (*curState == SPACE1) {
		// получен ПРОБЕЛ
		if (value[*ind] == "ПРОБЕЛ") {
			// читаем дальше, вызвав эту же функцию
			(*ind)++;
			return state_space1(symb, value, curState, ind);
		}
		// получена БУКВА
		if (value[*ind] == "БУКВА") {
			// смена состояния, вызов функции считывания идентификатора
			*curState = ID1;
			return state_id1(symb, value, curState, ind);
		}
	}
	// иначе ОШИБКА
	return create_token(string(1, symb[*ind]), "ОШИБКА");
}

// описание аналогично state_if
Token state_id1(char symb[], string value[], int* curState, int* ind, string curString) {
	// если верное состояние
	if (*curState == ID1) {
		// получен ПРОБЕЛ после считывания идентификатора
		if (curString != "" && value[*ind] == "ПРОБЕЛ") {
			// смена состояния, возврат результата
			*curState = SPACE2;
			return create_token(curString, "ИДЕНТИФИКАТОР");
		}
		// получены символы для идентификатора
		if (value[*ind] == "БУКВА" || value[*ind] == "ПОДЧЕРК" || value[*ind] == "ЦИФРА" && curString != "") {
			// читаем далее, сохранив символ в curString
			curString.push_back(symb[*ind]);
			(*ind)++;
			return state_id1(symb, value, curState, ind, curString);
		}
	}
	// иначе ОШИБКА
	return create_token(string(1, symb[*ind]), "ОШИБКА");
}

// описание аналогично state_begin
Token state_space2(char symb[], string value[], int* curState, int* ind) {
	// если верное состояние
	if (*curState == SPACE2) {
		// получен ПРОБЕЛ
		if (value[*ind] == "ПРОБЕЛ") {
			// читаем далее в этой же функции и этом же состоянии
			(*ind)++;
			return state_space2(symb, value, curState, ind);
		}
		// получена БУКВА
		if (value[*ind] == "БУКВА") {
			// смена состояния и вызов функции для считывания then
			*curState = THEN;
			return state_then(symb, value, curState, ind);
		}
	}
	// иначе ОШИБКА
	return create_token(string(1, symb[*ind]), "ОШИБКА");
}

// описание аналогично state_if
Token state_then(char symb[], string value[], int* curState, int* ind, string curString) {
	// если верное состояние
	if (*curState == THEN) {
		// получена БУКВА
		if (value[*ind] == "БУКВА") {
			// читаем then, не учитывая регистр
			switch ((char)tolower(symb[*ind])) {
				case 't': if (curString.size() != 0) return create_token(string(1, symb[*ind]), "ОШИБКА");
					break;
				case 'h': if (curString.size() != 1) return create_token(string(1, symb[*ind]), "ОШИБКА");
					break;
				case 'e': if (curString.size() != 2) return create_token(string(1, symb[*ind]), "ОШИБКА");
					break;
				case 'n': if (curString.size() != 3) return create_token(string(1, symb[*ind]), "ОШИБКА");
					break;
				// иначе ОШИБКА
				default: return create_token(string(1, symb[*ind]), "ОШИБКА");
			}
			curString.push_back(symb[*ind]);
			*ind += 1;
			return state_then(symb, value, curState, ind, curString);
		}
		// получен ПРОБЕЛ после считанного then
		if (curString.size() == 4 && value[*ind] == "ПРОБЕЛ") {
			// смена состояния, возврат результата
			*curState = SPACE3;
			return create_token(curString, "ИДЕНТИФИКАТОР");
		}
	}
	// иначе ОШИБКА
	return create_token(string(1, symb[*ind]), "ОШИБКА");
}

// описание аналогично state_begin
Token state_space3(char symb[], string value[], int* curState, int* ind) {
	// если верное состояние
	if (*curState == SPACE3) {
		// получен ПРОБЕЛ
		if (value[*ind] == "ПРОБЕЛ") {
			// читаем далее в этой же функции и состоянии
			(*ind)++;
			return state_space3(symb, value, curState, ind);
		}
		// получена БУКВА
		if (value[*ind] == "БУКВА") {
			// смена состояния и вызов функции считывания идентификатора2
			*curState = ID2;
			return state_id2(symb, value, curState, ind);
		}
	}
	// иначе ОШИБКА
	return create_token(string(1, symb[*ind]), "ОШИБКА");
}

// описание аналогично state_if
Token state_id2(char symb[], string value[], int* curState, int* ind, string curString) {
	// если верное состояние
	if (*curState == ID2) {
		// пришел символ для идентификатора
		if (value[*ind] == "БУКВА" || value[*ind] == "ПОДЧЕРК" || value[*ind] == "ЦИФРА" && curString != "") {
			// читаем далее, сохранив символ
			curString.push_back(symb[*ind]);
			(*ind)++;
			return state_id2(symb, value, curState, ind, curString);
		}
		// пришел пробел или двоеточие
		if (curString != "" && value[*ind] == "ПРОБЕЛ" || value[*ind] == "ДВОЕТОЧИЕ") {
			// смена состояния и возврат результата
			if (value[*ind] == "ПРОБЕЛ") *curState = SPACE4;
			else *curState = COLON_EQUAL;
			return create_token(curString, "ИДЕНТИФИКАТОР");
		}
	}
	// иначе ОШИБКА
	return create_token(string(1, symb[*ind]), "ОШИБКА");
}

// описание аналогично state_begin
Token state_space4(char symb[], string value[], int* curState, int* ind) {
	// если верное состояние
	if (*curState == SPACE4 || *curState == COLON_EQUAL) {
		// получен ПРОБЕЛ
		if (value[*ind] == "ПРОБЕЛ") {
			// читаем далее, сохранив состояние
			(*ind)++;
			return state_space4(symb, value, curState, ind);
		}
		// получено ДВОЕТОЧИЕ
		if (value[*ind] == "ДВОЕТОЧИЕ") {
			// смена состояния и вызов другой функции для считывания
			*curState = COLON_EQUAL;
			return state_colon_and_equal(symb, value, curState, ind);
		}
	}
	// иначе ОШИБКА
	return create_token(string(1, symb[*ind]), "ОШИБКА");
}

// описание аналогично state_if
Token state_colon_and_equal(char symb[], string value[], int* curState, int* ind, string curString) {
	// если верное состояние
	if (*curState == COLON_EQUAL) {
		// получено ДВОЕТОЧИЕ или РАВНО после ДВОЕТОЧИЕ
		if (curString == "" && value[*ind] == "ДВОЕТОЧИЕ" || 
			curString.size() == 1 && value[*ind] == "РАВНО") {
			// сохраним его и читаем далее
			curString.push_back(symb[*ind]);
			(*ind)++;
			return state_colon_and_equal(symb, value, curState, ind, curString);
		}
		// если ДВОЕТОЧИЕ и РАВНО считаны
		if (curString.size() == 2){
			// получен ПРОБЕЛ
			if (value[*ind] == "ПРОБЕЛ") {
				// читаем далее
				(*ind)++;
				return state_colon_and_equal(symb, value, curState, ind, curString);
			}
			// получена БУКВА
			if (value[*ind] == "БУКВА") {
				// смена состояния и возврат результата
				*curState = NAME1;
				return create_token(curString, "ПРИСВОЕНИЕ");
			}
		}
	}
	// иначе ОШИБКА
	return create_token(string(1, symb[*ind]), "ОШИБКА");
}

// описание аналогично state_if
Token state_name1(char symb[], string value[], int* curState, int* ind, string curString) {
	// если верное состояние
	if (*curState == NAME1) {
		// получен символ названия подпрограммы
		if (value[*ind] == "БУКВА" || value[*ind] == "ПОДЧЕРК" || value[*ind] == "ЦИФРА" && curString != "") {
			// читаем далее, сохранив этот символ
			curString.push_back(symb[*ind]);
			(*ind)++;
			return state_name1(symb, value, curState, ind, curString);
		}
		// получена ОСКОБКА
		if (curString != "" && value[*ind] == "ОСКОБКА") {
			// смена состояния и возврат результата
			*curState = ID3;
			(*ind)++;
			return create_token(curString, "ПОДПРОГРАММА");
		}
	}
	// иначе ОШИБКА
	return create_token(string(1, symb[*ind]), "ОШИБКА");
}

// описание аналогично state_if
Token state_id3(char symb[], string value[], int* curState, int* ind, string curString) {
	// если верное состояние
	if (*curState == ID3) {
		// получен символ идентификатора
		if (value[*ind] == "БУКВА" || value[*ind] == "ПОДЧЕРК" || value[*ind] == "ЦИФРА" && curString != "") {
			// сохраним символ и будем читать далее
			curString.push_back(symb[*ind]);
			(*ind)++;
			return state_id3(symb, value, curState, ind, curString);
		}
		// получена закрывающая скобка после считывания идентификатора
		if (curString != "" && value[*ind] == "ЗСКОБКА") {
			// смена состояния, возврат результата
			*curState = CBRACKET1;
			(*ind)++;
			return create_token(curString, "ИДЕНТИФИКАТОР");
		}
	}
	// иначе ОШИБКА
	return create_token(string(1, symb[*ind]), "ОШИБКА");
}

// описание аналогично state_begin
Token state_cbracket1(char symb[], string value[], int* curState, int* ind) {
	// если верное состояние
	if (*curState == CBRACKET1) {
		// получен ПРОБЕЛ
		if (value[*ind] == "ПРОБЕЛ") {
			// смена состояния и вызов функции чтения пробелов
			*curState = SPACE5;
			return state_space5(symb, value, curState, ind);
		}
		// получена ТЧКЗПТ
		if (value[*ind] == "ТЧКЗПТ") {
			// смена состояния, возврат результата
			*curState = SEMICOLON;
			(*ind)++;
			return create_token(";", "ТЧКЗПТ");
		}
	}
	// иначе ОШИБКА
	return create_token(string(1, symb[*ind]), "ОШИБКА");
}

// описание аналогично state_begin
Token state_space5(char symb[], string value[], int* curState, int* ind) {
	// если верное состояние
	if (*curState == SPACE5) {
		// получен ПРОБЕЛ
		if (value[*ind] == "ПРОБЕЛ") {
			// читаем далее
			(*ind)++;
			return state_space5(symb, value, curState, ind);
		}
		// получена ТЧКЗПТ
		if (value[*ind] == "ТЧКЗПТ") {
			// смена состояния и вызов функции для ТЧКЗПТ
			*curState = SEMICOLON;
			return state_semicolon(symb, value, curState, ind);
		}
		// получена БУКВА
		if (value[*ind] == "БУКВА") {
			// смена состояния и вызов функции для ELSE
			*curState = ELSE;
			return state_else(symb, value, curState, ind);
		}
	}
	// иначе ОШИБКА
	return create_token(string(1, symb[*ind]), "ОШИБКА");
}

// описание аналогично state_if
Token state_else(char symb[], string value[], int* curState, int* ind, string curString) {
	// если верное состояние
	if (*curState == ELSE) {
		// получен ПРОБЕЛ после else
		if (curString.size() == 4 && value[*ind] == "ПРОБЕЛ") {
			// смена состояния и возврат результата
			*curState = SPACE6;
			return create_token(curString, "ИДЕНТИФИКАТОР");
		}
		// получена БУКВА
		if (value[*ind] == "БУКВА") {
			// читаем else без учета регистра
			switch ((char)tolower(symb[*ind])) {
				case 'l': if (curString.size() != 1) return create_token(string(1, symb[*ind]), "ОШИБКА");
					break;
				case 's': if (curString.size() != 2) return create_token(string(1, symb[*ind]), "ОШИБКА");
					break;
				default:
				// пришло е И перед ним есть (s ИЛИ пробел)
					if ((char)tolower(symb[*ind]) == 'e' && (curString.size() != 0 && 
						(char)tolower(symb[(*ind)-1]) == 's' || curString.size() == 0))
						break;
				// иначе ошибка
					return create_token(string(1, symb[*ind]), "ОШИБКА");
			}
			// читаем далее, сохранив символ
			curString.push_back(symb[*ind]);
			*ind += 1;
			return state_else(symb, value, curState, ind, curString);
		}
	}
	// иначе ОШИБКА
	return create_token(string(1, symb[*ind]), "ОШИБКА");
}

// описание аналогично state_begin
Token state_space6(char symb[], string value[], int* curState, int* ind) {
	// если верное состояние
	if (*curState == SPACE6) {
		// получен ПРОБЕЛ
		if (value[*ind] == "ПРОБЕЛ") {
			// читаем их далее
			(*ind)++;
			return state_space6(symb, value, curState, ind);
		}
		// получена БУКВА
		if (value[*ind] == "БУКВА") {
			// смена состояния и вызов функции чтения имени подпрограммы
			*curState = NAME2;
			return state_name2(symb, value, curState, ind);
		}
	}
	// иначе ОШИБКА
	return create_token(string(1, symb[*ind]), "ОШИБКА");
}

// описание аналогично state_if
Token state_name2(char symb[], string value[], int* curState, int* ind, string curString) {
	// если верное состояние
	if (*curState == NAME2) {
		// пришел символ из имени подпрограммы
		if (value[*ind] == "БУКВА" || value[*ind] == "ПОДЧЕРК" || value[*ind] == "ЦИФРА" && curString != "") {
			// сохраняем его и читаем дальше
			curString.push_back(symb[*ind]);
			(*ind)++;
			return state_name2(symb, value, curState, ind, curString);
		}
		// пришла открывающая скобка после имени подпрограммы
		if (curString != "" && value[*ind] == "ОСКОБКА") {
			// смена состояния и возврат результата
			*curState = SIGN_INT;
			(*ind)++;
			return create_token(curString, "ПОДПРОГРАММА");
		}
	}
	// иначе ОШИБКА
	return create_token(string(1, symb[*ind]), "ОШИБКА");
}

// описание аналогично state_if
Token state_sign_and_int(char symb[], string value[], int* curState, int* ind, string curString) {
	// если верное состояние
	if (*curState == SIGN_INT) {
		// получен ЗНАК или ЦИФРА
		if (curString == "" && value[*ind] == "ЗНАК" || value[*ind] == "ЦИФРА") {
			// сохраняем, читаем далее
			curString.push_back(symb[*ind]);
			(*ind)++;
			return state_sign_and_int(symb, value, curState, ind, curString);
		}
		// получена ЗСКОБКА
		if (value[*ind] == "ЗСКОБКА") {
			// смена состояния и возврат результата
			*curState = CBRACKET2;
			(*ind)++;
			return create_token(curString, "ЦЕЛОЕ");
		}
	}
	// иначе ОШИБКА
	return create_token(string(1, symb[*ind]), "ОШИБКА");
}

// описание аналогично state_begin
Token state_cbracket2(char symb[], string value[], int* curState, int* ind) {
	// если верное состояние
	if (*curState == CBRACKET2) {
		// получен ПРОБЕЛ
		if (value[*ind] == "ПРОБЕЛ") {
			// читаем дальше
			(*ind)++;
			return state_cbracket2(symb, value, curState, ind);
		}
		// получена ТЧКЗПТ
		if (value[*ind] == "ТЧКЗПТ") {
			// смена состояния и возврат результата
			*curState = SEMICOLON;
			(*ind)++;
			return create_token(";", "ТЧКЗПТ");
		}
	}
	// иначе ОШИБКА
	return create_token(string(1, symb[*ind]), "ОШИБКА");
}

// описание аналогично state_begin
Token state_semicolon(char symb[], string value[], int* curState, int* ind) {
	// если верное состояние и получен ПРОБЕЛ
	if (*curState == SEMICOLON && value[*ind] == "ПРОБЕЛ") {
		// читаем их дальше
		(*ind)++;
		return state_semicolon(symb, value, curState, ind);
	}
	// достигли конца файла - скажем, что всё ОК
	if (value[*ind] == "") return create_token("КОНЕЦ", "КОНЕЦ");
	// иначе ОШИБКА
	return create_token(string(1, symb[*ind]), "ОШИБКА");
}