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

vector<string> gerarVizinhos(const string& palavra, const unordered_set<string>& dicionario) {

    /**
     * @brief Gera os vizinhos de uma palavra.
     * @param palavra A palavra para gerar os vizinhos.
     * @param dicionario O dicionário de palavras.
     * @return Um vetor de strings contendo todos os vizinhos da palavra.
     */

    vector<string> vizinhos; // Vetor para armazenar os vizinhos

    for (int i = 0; i < palavra.size(); i++) {
        char original = palavra[i]; // Guarda o caractere original
        for (char c = 'A'; c <= 'Z'; c++) {
            if (c == original) continue;
            string vizinho = palavra; // Cria uma cópia da palavra
            vizinho[i] = c;
            if (dicionario.find(vizinho) != dicionario.end()) { // Verifica se o vizinho está no dicionário
                vizinhos.push_back(vizinho);
            }
        }
    }

    return vizinhos; // Retorna o vetor de vizinhos
}

// Estrutura para armazenar o estado atual da busca
struct Estado {
    string palavra;
    int profundidade;
};

vector<string> reconstruirCaminho(const string* palavra_inicial, const string* palavra_final, const unordered_map<string, string>& pai) {

    /**
     * @brief Reconstrói o caminho entre duas palavras.
     * @param palavra_inicial A palavra inicial.
     * @param palavra_final A palavra final.
     * @param pai O mapa de pais.
     * @return Um vetor de strings contendo o caminho entre as duas palavras.
     */

    vector<string> caminho;
    string atual = palavra_final; // Inicializa a palavra atual com a palavra final

    while (true) {
        caminho.push_back(atual); // Adiciona a palavra atual ao caminho
        auto it = pai.find(atual); // Encontra o pai da palavra atual
        if (it == pai.end()) break;
        atual = it->second; // Atualiza a palavra atual com o pai da palavra atual
    }

    reverse(caminho.begin(), caminho.end()); // Inverte o caminho
    return caminho;
}


vector<string> buscaHibrida( const string& palavra_inicial, const string& palavra_final, const unordered_set<string>& dicionario, int k) {
    return;
}

int main() {
    auto dicionario = carregarDicionario("dicionario.txt");

    cout << "Carregadas " << dicionario.size() << " palavras.\n";

    vector<string> vizinhos = gerarVizinhos("GATO", dicionario);

    cout << "Vizinhos de GATO: ";
    for (const string& vizinho : vizinhos) {
        cout << vizinho << " ";
    }
    cout << endl;

    // testar:
    if (dicionario.find("GATO") != dicionario.end()) {
        cout << "Achei GATO no dicionario!\n";
    }
}