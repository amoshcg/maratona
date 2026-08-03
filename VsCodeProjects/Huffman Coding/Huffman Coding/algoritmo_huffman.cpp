#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <locale>
#include <codecvt>
#include <cstdint>
#include <cwctype> // Para iswalnum
#include <chrono> // Biblioteca para cronometragem

#include <windows.h>

// =================================================================
// 1. ESTRUTURAS E LÓGICA DE HUFFMAN GENÉRICAS (USANDO TEMPLATES)
// =================================================================

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

template <typename T>
struct CompareNodes {
    bool operator()(HuffmanNode<T>* l, HuffmanNode<T>* r) const {
        return l->frequency > r->frequency;
    }
};

// Função generateCodes CORRIGIDA
template <typename T>
void generateCodes(HuffmanNode<T>* root, const std::wstring& str, std::map<T, std::wstring>& huffmanCodes) {
    if (!root) return;

    // Se o nó é uma folha (não tem filhos)
    if (!root->left && !root->right) {
        // CORREÇÃO: Se a string do caminho estiver vazia, significa que a árvore
        // tem um único nó. O código deve ser "0", e não vazio.
        huffmanCodes[root->data] = str.empty() ? L"0" : str;
    }

    if (root->left) generateCodes(root->left, str + L'0', huffmanCodes);
    if (root->right) generateCodes(root->right, str + L'1', huffmanCodes);
}

template <typename T>
HuffmanNode<T>* buildTree(const std::map<T, long long>& frequencies) {
    std::priority_queue<HuffmanNode<T>*, std::vector<HuffmanNode<T>*>, CompareNodes<T>> pq;

    for (const auto& pair : frequencies) {
        pq.push(new HuffmanNode<T>(pair.first, pair.second));
    }
    
    if (pq.empty()) return nullptr;

    while (pq.size() > 1) {
        HuffmanNode<T>* left = pq.top(); pq.pop();
        HuffmanNode<T>* right = pq.top(); pq.pop();

        T default_val{}; // Valor padrão para T (L'\0' para wchar_t, L"" para wstring)
        HuffmanNode<T>* top = new HuffmanNode<T>(default_val, left->frequency + right->frequency);
        top->left = left;
        top->right = right;
        pq.push(top);
    }
    return pq.top();
}

// =================================================================
// 2. TOKENIZAÇÃO (DIVIDIR O ARQUIVO EM SÍMBOLOS)
// =================================================================

// Tokenizador para modo Caracter
std::vector<wchar_t> tokenizar_por_caracteres(const std::string& path, std::wifstream& in) {
    std::vector<wchar_t> tokens;
    wchar_t ch;
    while (in.get(ch)) {
        tokens.push_back(ch);
    }
    return tokens;
}

// Tokenizador para modo Palavra
std::vector<std::wstring> tokenizar_por_palavras(const std::string& path, std::wifstream& in) {
    std::vector<std::wstring> tokens;
    wchar_t ch;
    std::wstring current_token;
    bool in_word = false; // Estado: dentro de uma palavra (alfanumérica) ou delimitador

    while (in.get(ch)) {
        bool is_char_word_char = std::use_facet<std::ctype<wchar_t>>(in.getloc()).is(std::ctype_base::alnum, ch);
        if (current_token.empty()) {
            current_token += ch;
            in_word = is_char_word_char;
        } else {
            if (is_char_word_char == in_word) {
                current_token += ch;
            } else {
                tokens.push_back(current_token);
                current_token = ch;
                in_word = is_char_word_char;
            }
        }
    }
    if (!current_token.empty()) {
        tokens.push_back(current_token);
    }
    return tokens;
}

// =================================================================
// 3. FUNÇÕES DE COMPACTAÇÃO E DESCOMPACTAÇÃO
// =================================================================

// --- Funções Auxiliares para I/O Binário de Strings ---
void write_wstring(std::ofstream& out, const std::wstring& str) {
    uint32_t len = str.length();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(reinterpret_cast<const char*>(str.c_str()), len * sizeof(wchar_t));
}

std::wstring read_wstring(std::ifstream& in) {
    uint32_t len;
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    std::vector<wchar_t> buffer(len);
    in.read(reinterpret_cast<char*>(buffer.data()), len * sizeof(wchar_t));
    return std::wstring(buffer.begin(), buffer.end());
}


// --- Compactação por Caracter ---
void compactar_caractere(const std::string& inputPath, const std::string& outputPath) {
    std::wcout << u8"Lendo arquivo e contando frequência de caracteres..." << std::endl;
    std::wifstream inputFile(inputPath);
    if (!inputFile.is_open()) { std::wcerr << u8"Erro: Não foi possível abrir o arquivo de entrada." << std::endl; return; }
    inputFile.imbue(std::locale());

    std::vector<wchar_t> tokens = tokenizar_por_caracteres(inputPath, inputFile);
    inputFile.close();

    if (tokens.empty()) {
        std::wcout << u8"Arquivo vazio. Nada a fazer." << std::endl;
        std::ofstream(outputPath).close(); // Cria um arquivo de saída vazio
        return;
    }

    std::map<wchar_t, long long> frequencies;
    for (const auto& token : tokens) frequencies[token]++;
    
    std::wcout << u8"Construindo árvore de Huffman..." << std::endl;
    HuffmanNode<wchar_t>* root = buildTree(frequencies);

    std::map<wchar_t, std::wstring> huffmanCodes;
    generateCodes(root, L"", huffmanCodes);

    std::ofstream outputFile(outputPath, std::ios::binary);
    if (!outputFile.is_open()) { std::wcerr << u8"Erro: Não foi possível criar o arquivo de saída." << std::endl; delete root; return; }

    std::wcout << u8"Escrevendo cabeçalho e dados compactados..." << std::endl;
    uint32_t map_size = frequencies.size();
    outputFile.write(reinterpret_cast<const char*>(&map_size), sizeof(map_size));
    for (const auto& pair : frequencies) {
        outputFile.write(reinterpret_cast<const char*>(&pair.first), sizeof(wchar_t));
        outputFile.write(reinterpret_cast<const char*>(&pair.second), sizeof(long long));
    }
    
    unsigned char buffer = 0;
    int bit_count = 0;
    for (const auto& token : tokens) {
        for (char bit : huffmanCodes[token]) {
            buffer <<= 1;
            if (bit == '1') buffer |= 1;
            bit_count++;
            if (bit_count == 8) {
                outputFile.put(buffer);
                buffer = 0;
                bit_count = 0;
            }
        }
    }
    if (bit_count > 0) {
        buffer <<= (8 - bit_count);
        outputFile.put(buffer);
    }

    outputFile.close();
    delete root;
    std::wcout << u8"Compactação por caracter concluída!" << std::endl;
}

// Função descompactar_caracter CORRIGIDA E SEGURA
void descompactar_caractere(const std::string& inputPath, const std::string& outputPath) {
    std::wcout << u8"Lendo cabeçalho do arquivo compactado..." << std::endl;
    std::ifstream inputFile(inputPath, std::ios::binary);
    if (!inputFile.is_open() || inputFile.peek() == EOF) {
        if(inputFile.peek() == EOF) {
             std::wofstream(outputPath).close();
             std::wcout << u8"Arquivo de entrada vazio. Arquivo de saída vazio criado." << std::endl;
             return;
        }
        std::wcerr << u8"Erro: Não foi possível abrir o arquivo de entrada." << std::endl; 
        return;
    }
    
    std::map<wchar_t, long long> frequencies;
    uint32_t map_size;
    inputFile.read(reinterpret_cast<char*>(&map_size), sizeof(map_size));
    
    long long total_char_count = 0;
    for (uint32_t i = 0; i < map_size; ++i) {
        wchar_t ch;
        long long freq;
        inputFile.read(reinterpret_cast<char*>(&ch), sizeof(wchar_t));
        inputFile.read(reinterpret_cast<char*>(&freq), sizeof(long long));
        frequencies[ch] = freq;
        total_char_count += freq;
    }
    
    std::wcout << u8"Reconstruindo árvore de Huffman..." << std::endl;
    HuffmanNode<wchar_t>* root = buildTree(frequencies);
    
    std::wofstream outputFile(outputPath);
    if (!outputFile.is_open()) { std::wcerr << u8"Erro: Não foi possível criar o arquivo de saída." << std::endl; delete root; return; }
    outputFile.imbue(std::locale());

    if (root && !root->left && !root->right) {
        for (long long i = 0; i < total_char_count; ++i) {
            outputFile.put(root->data);
        }
    } else if (root) { // Só prossiga se a árvore não for nula
        std::wcout << u8"Descompactando dados..." << std::endl;
        HuffmanNode<wchar_t>* currentNode = root;
        char byte;
        long long decoded_count = 0;
        bool error_found = false;

        while (inputFile.get(byte) && decoded_count < total_char_count) {
            for (int i = 7; i >= 0; --i) {
                if (decoded_count == total_char_count) break;

                // **INÍCIO DA LÓGICA DE NAVEGAÇÃO SEGURA**
                int bit = (byte >> i) & 1;
                currentNode = (bit == 0) ? currentNode->left : currentNode->right;

                // VERIFICAÇÃO DE SEGURANÇA: Checa se o caminho é válido.
                // Se currentNode for nulo, os dados estão corrompidos ou há um erro.
                if (!currentNode) {
                    std::wcerr << u8"\nERRO: Dados de compactação inválidos ou corrompidos. Abortando descompressão." << std::endl;
                    error_found = true;
                    break; 
                }

                // Se chegamos a uma folha, decodificamos o caracter
                if (!currentNode->left && !currentNode->right) {
                    outputFile.put(currentNode->data);
                    currentNode = root; // Volta para a raiz
                    decoded_count++;
                }
                // **FIM DA LÓGICA DE NAVEGAÇÃO SEGURA**
            }
            if (error_found) break; // Sai do laço while principal se um erro foi encontrado
        }
    }

    inputFile.close();
    outputFile.close();
    delete root;
    std::wcout << u8"Descompactação por caracter concluída!" << std::endl;
}

// --- Compactação por Palavra ---
void compactar_palavra(const std::string& inputPath, const std::string& outputPath) {
    std::wcout << u8"Lendo arquivo e tokenizando por palavras..." << std::endl;
    std::wifstream inputFile(inputPath);
    if (!inputFile.is_open()) { std::wcerr << u8"Erro: Não foi possível abrir o arquivo de entrada." << std::endl; return; }
    inputFile.imbue(std::locale());
    
    std::vector<std::wstring> tokens = tokenizar_por_palavras(inputPath, inputFile);
    inputFile.close();
    
    if (tokens.empty()) {
        std::wcout << u8"Arquivo vazio. Nada a fazer." << std::endl;
        std::ofstream(outputPath).close();
        return;
    }

    std::map<std::wstring, long long> frequencies;
    for (const auto& token : tokens) frequencies[token]++;

    std::wcout << u8"Construindo árvore de Huffman para palavras..." << std::endl;
    HuffmanNode<std::wstring>* root = buildTree(frequencies);

    std::map<std::wstring, std::wstring> huffmanCodes;
    generateCodes(root, L"", huffmanCodes);

    std::ofstream outputFile(outputPath, std::ios::binary);
    if (!outputFile.is_open()) { std::wcerr << u8"Erro: Não foi possível criar o arquivo de saída." << std::endl; delete root; return; }

    std::wcout << u8"Escrevendo cabeçalho e dados compactados..." << std::endl;
    uint32_t map_size = frequencies.size();
    outputFile.write(reinterpret_cast<const char*>(&map_size), sizeof(map_size));
    for (const auto& pair : frequencies) {
        write_wstring(outputFile, pair.first); // Palavra/Token
        outputFile.write(reinterpret_cast<const char*>(&pair.second), sizeof(long long)); // Frequência
    }

    unsigned char buffer = 0;
    int bit_count = 0;
    for (const auto& token : tokens) {
        for (char bit : huffmanCodes[token]) {
            buffer <<= 1;
            if (bit == '1') buffer |= 1;
            bit_count++;
            if (bit_count == 8) {
                outputFile.put(buffer);
                buffer = 0;
                bit_count = 0;
            }
        }
    }
    if (bit_count > 0) {
        buffer <<= (8 - bit_count);
        outputFile.put(buffer);
    }
    
    outputFile.close();
    delete root;
    std::wcout << u8"Compactação por palavra concluída!" << std::endl;
}

// Função descompactar_palavra CORRIGIDA E SEGURA
void descompactar_palavra(const std::string& inputPath, const std::string& outputPath) {
    std::wcout << u8"Lendo cabeçalho do arquivo compactado..." << std::endl;
    std::ifstream inputFile(inputPath, std::ios::binary);
     if (!inputFile.is_open() || inputFile.peek() == EOF) {
        if(inputFile.peek() == EOF) {
             std::wofstream(outputPath).close();
             std::wcout << u8"Arquivo de entrada vazio. Arquivo de saída vazio criado." << std::endl;
             return;
        }
        std::wcerr << u8"Erro: Não foi possível abrir o arquivo de entrada." << std::endl; 
        return;
    }
    
    std::map<std::wstring, long long> frequencies;
    uint32_t map_size;
    inputFile.read(reinterpret_cast<char*>(&map_size), sizeof(map_size));
    
    long long total_token_count = 0;
    for (uint32_t i = 0; i < map_size; ++i) {
        std::wstring token = read_wstring(inputFile);
        long long freq;
        inputFile.read(reinterpret_cast<char*>(&freq), sizeof(long long));
        frequencies[token] = freq;
        total_token_count += freq;
    }
    
    std::wcout << u8"Reconstruindo árvore de Huffman para palavras..." << std::endl;
    HuffmanNode<std::wstring>* root = buildTree(frequencies);
    
    std::wofstream outputFile(outputPath);
    if (!outputFile.is_open()) { std::wcerr << u8"Erro: Não foi possível criar o arquivo de saída." << std::endl; delete root; return; }
    outputFile.imbue(std::locale());
    
    if (root && !root->left && !root->right) {
        for (long long i = 0; i < total_token_count; ++i) {
            outputFile << root->data;
        }
    } else if (root) { // Só prossiga se a árvore não for nula
        std::wcout << u8"Descompactando dados..." << std::endl;
        HuffmanNode<std::wstring>* currentNode = root;
        char byte;
        long long decoded_count = 0;
        bool error_found = false;

        while (inputFile.get(byte) && decoded_count < total_token_count) {
            for (int i = 7; i >= 0; --i) {
                if (decoded_count == total_token_count) break;
                
                // **INÍCIO DA LÓGICA DE NAVEGAÇÃO SEGURA**
                int bit = (byte >> i) & 1;
                currentNode = (bit == 0) ? currentNode->left : currentNode->right;

                // VERIFICAÇÃO DE SEGURANÇA
                if (!currentNode) {
                    std::wcerr << u8"\nERRO: Dados de compactação inválidos ou corrompidos. Abortando descompressão." << std::endl;
                    error_found = true;
                    break;
                }

                if (!currentNode->left && !currentNode->right) {
                    outputFile << currentNode->data;
                    currentNode = root;
                    decoded_count++;
                }
                // **FIM DA LÓGICA DE NAVEGAÇÃO SEGURA**
            }
            if (error_found) break;
        }
    }
    
    inputFile.close();
    outputFile.close();
    delete root;
    std::wcout << u8"Descompactação por palavra concluída!" << std::endl;
}

void printMenu() {
    std::wcout << u8"1. Compactar arquivo (por caractere)\n";
    std::wcout << u8"2. Descompactar arquivo (por caractere)\n";
    std::wcout << u8"3. Compactar arquivo (por palavra)\n";
    std::wcout << u8"4. Descompactar arquivo (por palavra)\n";
    std::wcout << u8"0. Sair\n";
    std::wcout << u8"Escolha uma opção: ";
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    setvbuf(stdout, nullptr, _IONBF, 0);

    int choice;
    std::string inputFile, outputFile;

    while (true) {
        printMenu();
        std::cin >> choice;
        std::cin.ignore(); // Limpa o buffer de entrada

        if (choice == 0) {
            break;
        }
        
        if (choice >= 1 && choice <= 4) {
            std::wcout << u8"Digite o nome do arquivo de ENTRADA: ";
            std::getline(std::cin, inputFile);
            std::wcout << u8"Digite o nome do arquivo de SAÍDA: ";
            std::getline(std::cin, outputFile);
        } else {
             std::wcout << u8"Opção Inválida\n";
             continue; // Volta para o início do laço se a opção for inválida
        }

        // <<< INÍCIO DAS MUDANÇAS PARA CRONOMETRAGEM >>>
        switch (choice) {
            case 1:
                {
                    auto start = std::chrono::high_resolution_clock::now();
                    compactar_caractere(inputFile, outputFile);
                    auto end = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double> duration = end - start;
                    std::wcout << u8"\nTempo decorrido: " << duration.count() << u8" segundos.\n" << std::endl;
                }
                break;
            case 2:
                {
                    auto start = std::chrono::high_resolution_clock::now();
                    descompactar_caractere(inputFile, outputFile);
                    auto end = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double> duration = end - start;
                    std::wcout << u8"\nTempo decorrido: " << duration.count() << u8" segundos.\n" << std::endl;
                }
                break;
            case 3:
                {
                    auto start = std::chrono::high_resolution_clock::now();
                    compactar_palavra(inputFile, outputFile);
                    auto end = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double> duration = end - start;
                    std::wcout << u8"\nTempo decorrido: " << duration.count() << u8" segundos.\n" << std::endl;
                }
                break;
            case 4:
                {
                    auto start = std::chrono::high_resolution_clock::now();
                    descompactar_palavra(inputFile, outputFile);
                    auto end = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double> duration = end - start;
                    std::wcout << u8"\nTempo decorrido: " << duration.count() << u8" segundos.\n" << std::endl;
                }
                break;
            // O default foi removido pois a validação já acontece antes do switch
        }
        // <<< FIM DAS MUDANÇAS PARA CRONOMETRAGEM >>>
    }

    std::wcout << u8"Programa finalizado.\n";
    return 0;
}