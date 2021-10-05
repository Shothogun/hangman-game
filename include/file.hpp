#ifndef FILE_HANGMAN
#define FILE_HANGMAN

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

using namespace std;

// Função que dado um arquivo com nome file e uma palavra adiciona essa palavra dentro do arquivo
void writeWord(string word, const char * file);
// Função que escreve o ranking no arquivo de ranking
void writeRanking(const char * file, vector<pair <string, string> > ranking);
// Função que retorna todos os nomes armazenados no arquivo passado como parametro
vector<string> allWords(const char * file);
// Função que dado vector de strings retorna uma dessas strings aleatoriamente
string randomWord(vector<string> allWords);
// Função que pega o nome do arquivo de ranking e retorna um vector de pair com os rankings
vector< pair<string, string> > readRanking(const char * file);

#endif