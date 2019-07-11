#ifndef HEADER_H
#define HEADER_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// структура для хранения промежуточных результатов анализа (токенов)
struct Token { string input_string, leks; };

std::vector<Token> func_Translit(string);
std::vector<Token> func_Leks(std::vector<Token>);
void func_KeyWordIdent();
void func_Syntax();

#endif