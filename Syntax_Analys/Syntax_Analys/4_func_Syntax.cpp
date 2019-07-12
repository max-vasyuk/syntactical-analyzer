#include "syntax.h"

// func_Leks - Лексический блок
//________________________________________________________________________________________________________
// ВХОД:  vector<Token>keyident_result - массив кортежей (символ, класс) после идентификации ключевых слов
//________________________________________________________________________________________________________
// ВЫХОД: результат синтаксического анализа - строка, содержащая ACCEPT или REJECT - принята или нет цепочка соответственно
//________________________________________________________________________________________________________
string func_Syntax(vector<Token> keyident_result) {
	int curState = BEGIN, ind = 0;
	string text[80];
	string leks[80];

	for (int i = 0; i < keyident_result.size(); i++) {
		text[i] = keyident_result[i].input_string;
		leks[i] = keyident_result[i].leks;
	}

	Token result = state_begin(text, leks, &curState, &ind);
	if (result.leks == "ОШИБКА") return "REJECT";
	return "ACCEPT";
}

// state_begin - функция для состояния "Начало"
//________________________________________________________________________________________________________
// ВХОД: string text[] - распознанные лексемы строки
//		 string value[] - результаты лексического анализатора
//		 int* curState - текущее состояние
//		 int* ind - текущий индекс в строке
//________________________________________________________________________________________________________
// ВЫХОД: Token - токен, содержащий str, value
//________________________________________________________________________________________________________
Token state_begin(string text[], string value[], int* curState, int* ind) {
	// если верное состояние
	if (*curState == BEGIN) {
		// если получен IF
		if (value[*ind] == "КЛСЛОВО_IF") {
			// смена состояния и вызов функции для считывания следующей после if
			*curState = IF;
			(*ind)++;
			return state_if(text, value, curState, ind);
		}
	}
	// иначе ОШИБКА
	return create_token(text[*ind], "ОШИБКА");
}

// описание аналогично state_begin
Token state_if(string text[], string value[], int* curState, int* ind) {
	// если верное состояние
	if (*curState == IF) {
		// если получен идентификатор
		if (value[*ind] == "НЕКЛСЛОВО") {
			// смена состояния и вызов функции для считывания следующей после идентификатора
			*curState = ID1;
			(*ind)++;
			return state_id1(text, value, curState, ind);
		}
	}
	// иначе ОШИБКА
	return create_token(text[*ind], "ОШИБКА");
}

// описание аналогично state_begin
Token state_id1(string text[], string value[], int* curState, int* ind) {
	// если верное состояние
	if (*curState == ID1) {
		// если получен THEN
		if (value[*ind] == "КЛСЛОВО_THEN") {
			// смена состояния и вызов функции для считывания следующей после then
			*curState = THEN;
			(*ind)++;
			return state_then(text, value, curState, ind);
		}
	}
	// иначе ОШИБКА
	return create_token(text[*ind], "ОШИБКА");
}

// описание аналогично state_begin
Token state_then(string text[], string value[], int* curState, int* ind) {
	// если верное состояние
	if (*curState == THEN) {
		// если получен идентификатор
		if (value[*ind] == "НЕКЛСЛОВО") {
			// смена состояния и вызов функции для считывания следующей после идентификатора
			*curState = ID2;
			(*ind)++;
			return state_id2(text, value, curState, ind);
		}
	}
	// иначе ОШИБКА
	return create_token(text[*ind], "ОШИБКА");
}

// описание аналогично state_begin
Token state_id2(string text[], string value[], int* curState, int* ind) {
	// если верное состояние
	if (*curState == ID2) {
		// если получен присвоение
		if (value[*ind] == "ПРИСВОЕНИЕ") {
			// смена состояния и вызов функции для считывания следующей после присвоения
			*curState = COLON_EQUAL;
			(*ind)++;
			return state_colon_and_equal(text, value, curState, ind);
		}
	}
	// иначе ОШИБКА
	return create_token(text[*ind], "ОШИБКА");
}

// описание аналогично state_begin
Token state_colon_and_equal(string text[], string value[], int* curState, int* ind) {
	// если верное состояние
	if (*curState == COLON_EQUAL) {
		// если получен идентификатор
		if (value[*ind] == "НЕКЛСЛОВО") {
			// смена состояния и вызов функции для считывания следующей после идентификатора
			*curState = NAME1;
			(*ind)++;
			return state_name1(text, value, curState, ind);
		}
	}
	// иначе ОШИБКА
	return create_token(text[*ind], "ОШИБКА");
}

// описание аналогично state_begin
Token state_name1(string text[], string value[], int* curState, int* ind) {
	// если верное состояние
	if (*curState == NAME1) {
		// если получен оскобка
		if (value[*ind] == "ОСКОБКА") {
			// смена состояния и вызов функции для считывания следующей после оскобки
			*curState = OBRACKET1;
			(*ind)++;
			return state_obracket1(text, value, curState, ind);
		}
	}
	// иначе ОШИБКА
	return create_token(text[*ind], "ОШИБКА");
}

// описание аналогично state_begin
Token state_obracket1(string text[], string value[], int* curState, int* ind) {
	// если верное состояние
	if (*curState == OBRACKET1) {
		// если получен идентификатор
		if (value[*ind] == "НЕКЛСЛОВО") {
			// смена состояния и вызов функции для считывания следующей после идентификатора 
			*curState = ID3;
			(*ind)++;
			return state_id3(text, value, curState, ind);
		}
	}
	// иначе ОШИБКА
	return create_token(text[*ind], "ОШИБКА");
}

// описание аналогично state_begin
Token state_id3(string text[], string value[], int* curState, int* ind) {
	// если верное состояние
	if (*curState == ID3) {
		// если получен зскобка
		if (value[*ind] == "ЗСКОБКА") {
			// смена состояния и вызов функции для считывания следующей после зскобки
			*curState = CBRACKET1;
			(*ind)++;
			return state_cbracket1(text, value, curState, ind);
		}
	}
	// иначе ОШИБКА
	return create_token(text[*ind], "ОШИБКА");
}

// описание аналогично state_begin
Token state_cbracket1(string text[], string value[], int* curState, int* ind) {
	// если верное состояние
	if (*curState == CBRACKET1) {
		// если получен ELSE
		if (value[*ind] == "КЛСЛОВО_ELSE") {
			// смена состояния и вызов функции для считывания следующей после else
			*curState = ELSE;
			(*ind)++;
			return state_else(text, value, curState, ind);
		}
		// если получен тчкзпт
		if (value[*ind] == "ТЧКЗПТ") {
			// смена состояния и вызов функции для завершения работы КА
			*curState = SEMICOLON;
			(*ind)++;
			return state_semicolon(text, value, curState, ind);
		}
	}
	// иначе ОШИБКА
	return create_token(text[*ind], "ОШИБКА");
}

// описание аналогично state_begin
Token state_else(string text[], string value[], int* curState, int* ind) {
	// если верное состояние
	if (*curState == ELSE) {
		// если получен идентификатор
		if (value[*ind] == "НЕКЛСЛОВО") {
			// смена состояния и вызов функции для считывания следующей после идентификатора
			*curState = NAME2;
			(*ind)++;
			return state_name2(text, value, curState, ind);
		}
	}
	// иначе ОШИБКА
	return create_token(text[*ind], "ОШИБКА");
}

// описание аналогично state_begin
Token state_name2(string text[], string value[], int* curState, int* ind) {
	// если верное состояние
	if (*curState == NAME2) {
		// если получен оскобка
		if (value[*ind] == "ОСКОБКА") {
			// смена состояния и вызов функции для считывания следующей после оскобки
			*curState = OBRACKET2;
			(*ind)++;
			return state_obracket2(text, value, curState, ind);
		}
	}
	// иначе ОШИБКА
	return create_token(text[*ind], "ОШИБКА");
}

// описание аналогично state_begin
Token state_obracket2(string text[], string value[], int* curState, int* ind) {
	// если верное состояние
	if (*curState == OBRACKET2) {
		// если получен знак и целое
		if (value[*ind] == "ЦЕЛОЕ") {
			// смена состояния и вызов функции для считывания следующей после знака и целого
			*curState = SIGN_INT;
			(*ind)++;
			return state_sign_and_int(text, value, curState, ind);
		}
	}
	// иначе ОШИБКА
	return create_token(text[*ind], "ОШИБКА");
}

// описание аналогично state_begin
Token state_sign_and_int(string text[], string value[], int* curState, int* ind) {
	// если верное состояние
	if (*curState == SIGN_INT) {
		// если получен зскобка
		if (value[*ind] == "ЗСКОБКА") {
			// смена состояния и вызов функции для считывания следующей после зскобки
			*curState = CBRACKET2;
			(*ind)++;
			return state_cbracket2(text, value, curState, ind);
		}
	}
	// иначе ОШИБКА
	return create_token(text[*ind], "ОШИБКА");
}

// описание аналогично state_begin
Token state_cbracket2(string text[], string value[], int* curState, int* ind) {
	// если верное состояние
	if (*curState == CBRACKET2) {
		// если получен тчкзпт
		if (value[*ind] == "ТЧКЗПТ") {
			// смена состояния и вызов функции для завершения работы КА
			*curState = SEMICOLON;
			(*ind)++;
			return state_semicolon(text, value, curState, ind);
		}
	}
	// иначе ОШИБКА
	return create_token(text[*ind], "ОШИБКА");
}

// описание аналогично state_begin
Token state_semicolon(string text[], string value[], int* curState, int* ind) {
	//достигли конечного состояния - скажем, что всё ОК
	return create_token("КОНЕЦ", "КОНЕЦ");
}