#ifndef HEADER_H
#define HEADER_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cctype> 
#include <cstring> 
#include <algorithm>
using namespace std;

// структура для хранения промежуточных результатов анализа (токенов)
struct Token { string input_string, leks; };
vector<Token> func_Translit(string);
vector<Token> func_Leks(vector<Token>);
vector<Token> func_KeyWordIdent(vector<Token>);
string func_Syntax(vector<Token>);

// функция создания токена
inline Token create_token(string str, string value){
	Token tkn;
	tkn.input_string = str;
	tkn.leks = value;
	return tkn;
}

#endif