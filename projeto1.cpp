#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>

using namespace std;

vector<string> lista; // lista com todas as palavras do dicionário
map<string, int> dicionario; // map com os indices da lista
map<string, vector<string>> adj_mat; // matriz de adjacencia com a lista de todas as palavras adj a palavra chave

//                               Word Morphing
// Os estados são as diferentes palavras nesse caso de 4 letras
// A ação possível é trocar uma letra da palavra atual e transformar ela em outra palavra existente
// Objetivo de atingir uma palavra alvo

// Para rodar o código iremos passar o nome do arquivo do dicionário como parâmetro

// para compilar o programa usar o comando g++ projeto1.cpp -o p1
// para utilizar o programa usar o comando ./p1 nome_do_dicionario.txt

bool readData(const string& arquivo){
  //cria um fluxo de entrada (para ler o arquivo)
  ifstream fp;

  //tenta abrir o arquivo
  fp.open(arquivo);

  //verifica se o arquivo foi aberto
  if(!fp.is_open()){
      cout << "Nao foi possivel abrir o arquivo [" << arquivo << "].\n";
      return false;
  }

  string palavra;

  lista.clear();

  //leio todos as palavras do arquivo
  while(1){
    fp >> palavra;

    if(fp.eof()) break;

    lista.push_back(palavra);

    dicionario[palavra] = lista.size()-1;
  }

  //fecho o arquivo
  fp.close();

  return true;
}

void find_adj_mat(){
  string palavra;
  vector<string> aux;

  bool achei;

  for(int i = 0; i < lista.size(); i++){
    aux.clear(); // limpa o vector antes de começar uma nova iteração

    achei = false;

    for(int j = 0; j < lista[i].size(); j++){ // itera por todas as letras
      palavra = lista[i];

      for(char k = 'A'; k <= 'Z'; k++){ // verifica todas as possibilidades
        palavra[j] = k;

        if(palavra == lista[i]){
          continue;
        }else{ // procura se aquela palavra é válida
          auto ret = dicionario.find(palavra);

          if(ret != dicionario.end()){
            aux.push_back(palavra);

            achei = true;
            
            // cout << "Adicionei a palavra " << palavra << endl;
          }
        }
      }
    }

    if(achei){
      adj_mat[lista[i]] = aux;
    }else{
      // cout << "A palavra " << lista[i] << " está desconexa\n";
    }
  }
}

int main(int argc, char** argv){
  if(argc < 2){
    cout << "Faltando parâmetros\n";
    cout << "Uso correto: ./p1 nome_do_dicionario.txt\n";
    return -1;
  }

  // ler o dicionário e armazenar todas as palavras em um vector
  if(!readData(argv[1])){
    cout << "Ocorreu um erro ao ler as informações dos processos!\n";
  }
  
  /*for(int i = 0; i < lista.size(); i++){
    cout << "#" << i << " " << lista[i] << endl;
  }*/

  // fazer a matriz de adjacência de cada palavra para as outras que diferem apenas uma letra
  find_adj_mat();

  vector<string> teste = adj_mat[lista[0]];
  
  cout << "Palavras adjacentes a " << lista[0] << ":\n";
  for(int i = 0; i < teste.size(); i++){
    cout << teste[i] << ", ";
  }cout << endl;

  return 0;
}