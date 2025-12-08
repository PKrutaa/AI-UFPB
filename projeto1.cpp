#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <stack>

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

void print_tree(const vector<string>& tree){
    if(tree.empty()){
        cout << "Nenhuma árvore encontrada\n";
        return;
    }

    cout << "Árvore: [";

    for(int j = 0; j < tree.size(); j++){
        cout << tree[j] << ((j == tree.size() - 1) ? ("") : (", "));
    }

    cout << "]\n";
}

vector<string> DFS(map<string, vector<string>>& adj_matrix, const string& begin, const string& end){
    int n = adj_matrix.size();

    vector<int> status(n, 0); //represents the status of each vertex
    vector<int> parent(n, -1); //initializates the vector of parents as an invalid parent

    stack<string> s; //stack aux

    vector<string> tree;

    tree.push_back(begin);

    status[dicionario[begin]] = 1; //just the start vertex is 1

    //put the vertex on the stack
    s.push(begin);
    //cout << s.top() << " ";

    bool flag = 0; //flag para indicar se foi achado um novo no ou nao

    //while(there_is_adj_not_visited(s.top(), adj_matrix, status)){
    while(!s.empty()){
        for(auto vertex : adj_matrix[s.top()]){
            if(status[dicionario[vertex]] == 0){
                //updates the status of the vertex
                status[dicionario[vertex]] = 1;
                //put the vertex on the stack
                s.push(vertex);
                tree.push_back(s.top()); //adds the new vertex on the tree
                //cout << s.top() << " ";

                //search in the adj
                flag = 1;
                break;
            }
        }

        if(s.top() == end){ // finds the end vertex
          break;
        }

        if(flag){
            flag = 0;
            continue;
        }

        s.pop();
    }

    /*for(int i = 0; i < n; i++){
        if(status[i] == 0){
            vector<int> tree;

            tree.push_back(i);

            int index_aux = i;

            status[index_aux] = 1; //just the start vertex is 1

            //put the vertex on the stack
            s.push(index_aux);
            //cout << s.top() << " ";

            bool flag = 0; //flag para indicar se foi achado um novo no ou nao

            //while(there_is_adj_not_visited(s.top(), adj_matrix, status)){
            while(!s.empty()){
                for(auto edge : adj_matrix[s.top()]){
                    if(status[edge.first] == 0){
                        //updates the status of the vertex
                        status[edge.first] = 1;
                        //put the vertex on the stack
                        s.push(edge.first);
                        tree.push_back(s.top()); //adds the new vertex on the tree
                        //cout << s.top() << " ";

                        //search in the adj
                        flag = 1;
                        break;
                    }
                }

                if(flag){
                    flag = 0;
                    continue;
                }

                s.pop();
            }

            forest.push_back(tree);
        }
    }*/

    return tree;
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

  // fazer a matriz de adjacência de cada palavra para as outras que diferem apenas uma letra
  find_adj_mat();

  auto tree = DFS(adj_mat, "PATA", "RICO"); // coloca a palavra de inicio da busca e a que quer chegar

  print_tree(tree);

  return 0;
}