#ifndef FILE_HANGMAN
#define FILE_HANGMAN

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <time.h>

// Função que dado um arquivo com nome file e uma palavra adiciona essa palavra dentro do arquivo
void writeWord(std::string word, const char * file);
// Função que retorna todos os nomes armazenados no arquivo passado como parametro
std::vector<std::string> allWords(const char * file);
// Função que dado vector de strings retorna uma dessas strings aleatoriamente
std::string randomWord(std::vector<std::string> allWords);

#endif