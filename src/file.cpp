#include "../include/file.hpp"

using namespace std;



// Função que dado um arquivo com nome file e uma palavra adiciona essa palavra dentro do arquivo
void writeWord(string word, const char * file){
    ofstream fileWrite;

    fileWrite.open(file, ios::app);
    fileWrite << word << " ";

    fileWrite.close(); 
}
// Função que retorna todos os nomes armazenados no arquivo passado como parametro
vector<string> allWords(const char * file){
    ifstream fileRead;

    fileRead.open(file);

    vector<string> vs;
    string s;
    char c;

    while(fileRead.get(c)){
        if(c == ' '){
            vs.push_back(s);
            s.clear();
        }

        else{
            s.push_back(c);
        }
    }

    fileRead.close();

    return vs;
    
}
// Função que dado vector de strings retorna uma dessas strings aleatoriamente
string randomWord(vector<string> allWords){
    srand(time(NULL));

    int index = rand() % allWords.size();

    return allWords[index];
}