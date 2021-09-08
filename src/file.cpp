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
// Função que pega o nome do arquivo de ranking e retorna um vector de pair com os rankings
vector< pair<string, string> > readRanking(const char * file){
    ifstream fileRead;

    fileRead.open(file);

    vector< pair<string,string> > vpair;
    string sname, snumber;
    char c;

    while(fileRead.get(c)){
        if(c == '\n'){
            for(int i = sname.size() - 1; sname[i] != ' '; i--){
                snumber.push_back(sname[i]);
                sname.erase(i);
            }

            sname.erase(sname.size() - 1);// retirar o ultimo espaço em branco
            reverse(snumber.begin(), snumber.end());

            vpair.push_back(make_pair(sname, snumber));
            sname.clear();
            snumber.clear();
        }
        else{
            sname.push_back(c);
        }
    }
    fileRead.close();

    return vpair;
}
// Função que escreve o ranking no arquivo de ranking
void writeRanking(const char * file, vector<pair <string, string> > ranking){
    ofstream fileWrite;

    fileWrite.open(file);

    for(int i = 0; i < ranking.size(); i++){
        fileWrite << ranking[i].first << " " << ranking[i].second << "\n";
    }

    fileWrite.close();
}