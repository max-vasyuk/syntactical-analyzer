#include "header.h"

// toLower - преобразует строку типа string к нижнему регистру
//________________________________________________________________________________________________________
// ВХОД:  string - строка, которую требуется привести к нижнему регистру
//________________________________________________________________________________________________________
// ВЫХОД: string - преобразованная к нижнему регистру строка
//________________________________________________________________________________________________________
string toLower(string s) {
	char* cstr = new char[s.length() + 1];
	strcpy(cstr, s.c_str());
	for (int i = 0; i < s.length(); i++)
		cstr[i] = tolower(cstr[i]);
	return string(cstr);
}

// func_KeyWordIdent- Блок идентификации ключевых слов
//________________________________________________________________________________________________________
// ВХОД:  vector<Token> leks_result - массив кортежей (символ, класс)  - результат лексического анализатора
//________________________________________________________________________________________________________
// ВЫХОД: vector<Token> - результат идентификации ключевых слов - кортежи вида (строка, класс языка)
//________________________________________________________________________________________________________
vector<Token> func_KeyWordIdent(vector<Token> leks_result) {
	//ключевые слова языка Паскаль
	vector<string> keywords{ "absolute", "and", "array", "asm", "begin", "case", "const", "constructor", "div", "goto", "do",
							 "downto", "destructor", "end", "exports", "external", "file", "for", "forward", "function", "in",
							 "implementation", "inline", "interrupt", "interface", "inherited", "label", "library", "mod", "nil",
							 "not", "of", "or", "object", "packed", "procedure", "program", "record", "repeat", "set", "shl",
							 "shr", "string", "to", "type", "unit", "until", "uses", "var", "while", "with", "xor" };
	//результат блока
	vector<Token> result;
	//пробегаем по всем распознанным лексемам и среди идентификаторов ищем ключевые слова
	for (int i = 0; i < leks_result.size(); i++) {
		//переход к следующей лексеме, если текущая не является идентификатором
		if (leks_result[i].leks != "ИДЕНТИФИКАТОР") {
			result.push_back(create_token(leks_result[i].input_string, leks_result[i].leks));
			continue;
		}
		//встретили if
		if (toLower(leks_result[i].input_string) == "if") {
			result.push_back(create_token(leks_result[i].input_string, "КЛСЛОВО_IF"));
			continue;
		}
		//встретили then
		if (toLower(leks_result[i].input_string) == "then") {
			result.push_back(create_token(leks_result[i].input_string, "КЛСЛОВО_THEN"));
			continue;
		}
		//встретили else
		if (toLower(leks_result[i].input_string) == "else") {
			result.push_back(create_token(leks_result[i].input_string, "КЛСЛОВО_ELSE"));
			continue;
		}
		bool flag = 0; //false - если не возникло совпадение идентификатора с ключевыми словами
		for (int j = 0; j < keywords.size(); j++) {
			//если ключевое слово
			if (toLower(leks_result[i].input_string) == keywords[j]) {
				result.push_back(create_token(leks_result[i].input_string, "ОШИБКА"));
				flag = 1;
				break;
			}
		}
		//если не ключевое слово
		if (!flag)
			result.push_back(create_token(leks_result[i].input_string, "НЕКЛСЛОВО"));
	}
	//возвращаем результат
	return result;
}