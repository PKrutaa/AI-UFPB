/**
* @file word_morphing_bfs_bfs.cpp
* @author Kruta
* Esse arquivo implementa o algoritmo de busca em largura juntamente com o algoritmo
* de busca em profundidade para encontrar a distância entre duas palavras.
*/

#include <fstream> // leitura de arquivos
#include <iostream>
#include <unordered_set> // para armazenar o dicionário
#include <string>

using namespace std;

unordered_set<string> carregarDicionario(const string& filename) {

    /**
     * @brief Carrega o dicionário de palavras do arquivo.
     * @param filename O nome do arquivo contendo o dicionário.
     * @return Um conjunto de strings contendo todas as palavras do dicionário.
     */

    unordered_set<string> dicionario; // Cria dicionário vazio
    
    ifstream arquivo(filename); // Abre arquivo

    if (!arquivo.is_open()) { // Verifico se foi aberto corretamente
        cerr << "Erro ao abrir o arquivo " << filename << endl;
        exit(1);
    }

    string palavra; // Variável para armazenar cada palavra do dicionário

    while (arquivo >> palavra) { // Lê cada palavra do dicionário

        for (char& c : palavra) { // Converte para maiúsculas
            c = toupper(c);
        }

        dicionario.insert(palavra); // Insere na hash table
    }

    return dicionario; // Retorna o dicionário carregado
}

int main() {
    auto dicionario = carregarDicionario("dicionario.txt");

    cout << "Carregadas " << dicionario.size() << " palavras.\n";

    // testar:
    if (dicionario.find("GATO") != dicionario.end()) {
        cout << "Achei GATO no dicionario!\n";
    }
}