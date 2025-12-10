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
#include <vector>
#include <deque>
#include <unordered_map>
#include <algorithm>
#include <cctype>
using namespace std;

// Estrutura para armazenar o estado atual da busca
struct Estado {
    string palavra;
    int profundidade;
};

// Cabeçalho de função
unordered_set<string> carregarDicionario(const string& filename);
vector<string> gerarVizinhos(const string& palavra, const unordered_set<string>& dicionario);
vector<string> reconstruirCaminho(const string& palavra_inicial, const string& palavra_final, const unordered_map<string, string>& pai);
vector<string> buscaHibrida(const string& palavra_inicial, const string& palavra_final, const unordered_set<string>& dicionario, int k);

int main() {
    auto dicionario = carregarDicionario("dicionario.txt");
    cout << "Carregadas " << dicionario.size() << " palavras.\n";

    vector<string> caminho = buscaHibrida("GATO", "VELA", dicionario, 0);
    cout << "Caminho: ";
    for (const string& palavra : caminho) {
        cout << palavra << " ";
    }
    cout << endl;
}

// Implementação das outras funções
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

vector<string> reconstruirCaminho(const string& palavra_inicial, const string& palavra_final, const unordered_map<string, string>& pai) {

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

    /**
     * @brief Realiza a busca híbrida entre duas palavras.
     * @param palavra_inicial A palavra inicial.
     * @param palavra_final A palavra final.
     * @param dicionario O dicionário de palavras.
     * @param k O limite de profundidade da busca em profundidade.
     * @return Um vetor de strings contendo o caminho entre as duas palavras.
     */

    // Casos base

    if (dicionario.find(palavra_inicial) == dicionario.end() || dicionario.find(palavra_final) == dicionario.end()) { // Verifica se palavra inicial e final estão no dicionario
        cerr << "Palavra inicial ou final não encontrada no dicionário" << endl;
        return {};
    }

    if (palavra_inicial == palavra_final) { // Verifica se palavra inicial e final são iguais
        return {palavra_inicial};
    }

    // Estruturas de dados

    deque<Estado> fronteira;
    unordered_set<string> visitados;
    unordered_map<string, string> pai;

    // Inicialização da busca

    Estado estado_inicial = {palavra_inicial, 0};
    fronteira.push_back(estado_inicial);
    visitados.insert(palavra_inicial);

    // Loop principal da busca

    while (!fronteira.empty()) {
        Estado atual = fronteira.front(); // Pega o estado atual da fronteira
        fronteira.pop_front(); // Remove o estado para a busca

        if (atual.palavra == palavra_final) {
            return reconstruirCaminho(palavra_inicial, palavra_final, pai); // Reconstrói o caminho se encontrar a palavra final
        }

        vector<string> vizinhos = gerarVizinhos(atual.palavra, dicionario); // Gera os vizinhos da palavra atual

        for (const string& vizinho : vizinhos){ // Percorre todos os vizinhos da palavra atual
            if (visitados.find(vizinho) == visitados.end()) { // Verifica se o vizinho não foi visitado
                visitados.insert(vizinho); // Marca o vizinho como visitado
                pai[vizinho] = atual.palavra; // Marca o pai do vizinho como a palavra atual

                Estado novo_estado = {vizinho, atual.profundidade + 1}; // Cria um novo estado com a palavra vizinha e a profundidade + 1

                if (atual.profundidade < k) {
                    fronteira.push_back(novo_estado); // Adiciona na fronteira como último elemento para a busca em largura
                }
                else {
                    fronteira.push_front(novo_estado); // Adiciona na fronteira como primeiro elemento para a busca em profundidade
                }
            }
        }
    }

    return {}; // Retorna um vetor vazio se não encontrar o caminho
}