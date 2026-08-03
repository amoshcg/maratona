#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <locale>
#include <codecvt>
#include <cstdint>
#include <cwctype> 
#include <chrono>

#ifdef _WIN32
#include <windows.h>
#endif

// Estrutura para representar um nó na árvore de Huffman.
// T é o tipo do dado armazenado (wchar_t para caracter, wstring para palavra).
template <typename T>
struct HuffmanNode {
    T data;
    long long frequency;
    HuffmanNode *left, *right;

    HuffmanNode(T data, long long frequency) : data(data), frequency(frequency), left(nullptr), right(nullptr) {}

    // Destrutor recursivo para limpar a árvore
    ~HuffmanNode() {
        delete left;
        delete right;
    }
};

// Objeto de comparação para a fila de prioridade (min-heap).
template <typename T>
struct CompareNodes {
    bool operator()(HuffmanNode<T>* l, HuffmanNode<T>* r) const {
        return l->frequency > r->frequency;
    }
};

//      LÓGICA DE HUFFMAN

// Gera os códigos de Huffman recursivamente a partir da árvore.
// Pré-condição: root aponta para a raiz de uma árvore de Huffman válida, huffmanCodes é um mapa vazio.
// Pós-condição: O mapa huffmanCodes é preenchido com os símbolos e seus respectivos códigos binários.
template <typename T>
void generateCodes(HuffmanNode<T>* root, const std::wstring& str, std::map<T, std::wstring>& huffmanCodes);

// Constrói a árvore de Huffman a partir de um mapa de frequências.
// Pré-condição: O mapa 'frequencies' contém a contagem de cada símbolo.
// Pós-condição: Retorna um ponteiro para o nó raiz da árvore de Huffman construída.
template <typename T>
HuffmanNode<T>* buildTree(const std::map<T, long long>& frequencies);


//      TOKENIZAÇÃO

// Divide um arquivo em uma sequência de tokens de caracteres.
// Pré-condição: O stream 'in' está aberto e associado a um arquivo de texto válido.
// Pós-condição: Retorna um vetor de wchar_t contendo todos os caracteres do arquivo.
std::vector<wchar_t> tokenizar_por_caracteres(std::wifstream& in);

// Divide um arquivo em uma sequência de tokens de palavras e delimitadores.
// Pré-condição: O stream 'in' está aberto e associado a um arquivo de texto válido.
// Pós-condição: Retorna um vetor de wstring contendo as palavras e delimitadores em ordem.
std::vector<std::wstring> tokenizar_por_palavras(std::wifstream& in);


//      FUNÇÕES DE I/O AUXILIARES

// Escreve uma wstring em um arquivo binário, precedida por seu tamanho.
// Pré-condição: O stream 'out' está aberto em modo binário e pronto para escrita.
// Pós-condição: O tamanho da string e seus dados são escritos no arquivo.
void write_wstring(std::ofstream& out, const std::wstring& str);

// Lê uma wstring de um arquivo binário que foi escrita com write_wstring.
// Pré-condição: O stream 'in' está aberto em modo binário e posicionado corretamente.
// Pós-condição: Retorna a wstring lida do arquivo.
std::wstring read_wstring(std::ifstream& in);


//      COMPACTAÇÃO E DESCOMPACTAÇÃO

// Realiza a compactação de um arquivo usando Huffman por caracteres.
// Pré-condição: inputPath é um caminho válido para um arquivo de texto, outputPath é um caminho gravável.
// Pós-condição: Um arquivo binário compactado é criado em outputPath.
void compactar_caractere(const std::string& inputPath, const std::string& outputPath);

// Realiza a descompactação de um arquivo compactado por caracteres.
// Pré-condição: inputPath deve ser um arquivo válido gerado por 'compactar_caractere'.
// Pós-condição: Um arquivo de texto idêntico ao original é criado em outputPath.
void descompactar_caractere(const std::string& inputPath, const std::string& outputPath);

// Realiza a compactação de um arquivo usando Huffman por palavras.
// Pré-condição: inputPath é um caminho válido para um arquivo de texto, outputPath é um caminho gravável.
// Pós-condição: Um arquivo binário compactado é criado em outputPath.
void compactar_palavra(const std::string& inputPath, const std::string& outputPath);

// Realiza a descompactação de um arquivo compactado por palavras.
// Pré-condição: inputPath deve ser um arquivo válido gerado por 'compactar_palavra'.
// Pós-condição: Um arquivo de texto idêntico ao original é criado em outputPath.
void descompactar_palavra(const std::string& inputPath, const std::string& outputPath);


//      FUNÇÕES DE MENU

// Exibe o menu principal de opções para o usuário.
// Pré-condição: Nenhuma.
// Pós-condição: O menu é impresso na saída padrão.
void printMenu();

#endif // HUFFMAN_HPP