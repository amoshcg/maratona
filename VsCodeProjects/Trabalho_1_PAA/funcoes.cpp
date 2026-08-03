#include "funcoes.hpp"

// Gera os códigos de Huffman recursivamente a partir da árvore.
// Pré-condição: root aponta para a raiz de uma árvore de Huffman válida, huffmanCodes é um mapa vazio.
// Pós-condição: O mapa huffmanCodes é preenchido com os símbolos e seus respectivos códigos binários.
template <typename T>
void generateCodes(HuffmanNode<T>* root, const std::wstring& str, std::map<T, std::wstring>& huffmanCodes) {
    if (!root) return;

    if (!root->left && !root->right) {
        huffmanCodes[root->data] = str.empty() ? L"0" : str;
    }

    if (root->left) generateCodes(root->left, str + L'0', huffmanCodes);
    if (root->right) generateCodes(root->right, str + L'1', huffmanCodes);
}

// Constrói a árvore de Huffman a partir de um mapa de frequências.
// Pré-condição: O mapa 'frequencies' contém a contagem de cada símbolo.
// Pós-condição: Retorna um ponteiro para o nó raiz da árvore de Huffman construída.
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

        T default_val{}; 
        HuffmanNode<T>* top = new HuffmanNode<T>(default_val, left->frequency + right->frequency);
        top->left = left;
        top->right = right;
        pq.push(top);
    }
    return pq.top();
}


// Divide um arquivo em uma sequência de tokens de caracteres.
// Pré-condição: O stream 'in' está aberto e associado a um arquivo de texto válido.
// Pós-condição: Retorna um vetor de wchar_t contendo todos os caracteres do arquivo.
std::vector<wchar_t> tokenizar_por_caracteres(const std::string& path, std::wifstream& in) {
    std::vector<wchar_t> tokens;
    wchar_t ch;
    while (in.get(ch)) {
        tokens.push_back(ch);
    }
    return tokens;
}

// Divide um arquivo em uma sequência de tokens de palavras e delimitadores.
// Pré-condição: O stream 'in' está aberto e associado a um arquivo de texto válido.
// Pós-condição: Retorna um vetor de wstring contendo as palavras e delimitadores em ordem.
std::vector<std::wstring> tokenizar_por_palavras(const std::string& path, std::wifstream& in) {
    std::vector<std::wstring> tokens;
    wchar_t ch;
    std::wstring current_token;
    bool in_word = false; 

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

// Escreve uma wstring em um arquivo binário, precedida por seu tamanho.
// Pré-condição: O stream 'out' está aberto em modo binário e pronto para escrita.
// Pós-condição: O tamanho da string e seus dados são escritos no arquivo.
void write_wstring(std::ofstream& out, const std::wstring& str) {
    uint32_t len = str.length();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(reinterpret_cast<const char*>(str.c_str()), len * sizeof(wchar_t));
}

// Lê uma wstring de um arquivo binário que foi escrita com write_wstring.
// Pré-condição: O stream 'in' está aberto em modo binário e posicionado corretamente.
// Pós-condição: Retorna a wstring lida do arquivo.
std::wstring read_wstring(std::ifstream& in) {
    uint32_t len;
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    std::vector<wchar_t> buffer(len);
    in.read(reinterpret_cast<char*>(buffer.data()), len * sizeof(wchar_t));
    return std::wstring(buffer.begin(), buffer.end());
}


// Realiza a compactação de um arquivo usando Huffman por caracteres.
// Pré-condição: inputPath é um caminho válido para um arquivo de texto, outputPath é um caminho gravável.
// Pós-condição: Um arquivo binário compactado é criado em outputPath.
void compactar_caractere(const std::string& inputPath, const std::string& outputPath) {
    std::wcout << u8"Lendo arquivo e contando frequência de caracteres..." << std::endl;
    std::wifstream inputFile(inputPath);
    if (!inputFile.is_open()) { std::wcerr << u8"Erro: Não foi possível abrir o arquivo de entrada." << std::endl; return; }
    inputFile.imbue(std::locale());

    std::vector<wchar_t> tokens = tokenizar_por_caracteres(inputPath, inputFile);
    inputFile.close();

    if (tokens.empty()) {
        std::wcout << u8"Arquivo vazio. Nada a fazer." << std::endl;
        std::ofstream(outputPath).close(); 
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


// Realiza a descompactação de um arquivo compactado por caracteres.
// Pré-condição: inputPath deve ser um arquivo válido gerado por 'compactar_caractere'.
// Pós-condição: Um arquivo de texto idêntico ao original é criado em outputPath.
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
    } else if (root) {
        std::wcout << u8"Descompactando dados..." << std::endl;
        HuffmanNode<wchar_t>* currentNode = root;
        char byte;
        long long decoded_count = 0;
        bool error_found = false;

        while (inputFile.get(byte) && decoded_count < total_char_count) {
            for (int i = 7; i >= 0; --i) {
                if (decoded_count == total_char_count) break;

                int bit = (byte >> i) & 1;
                currentNode = (bit == 0) ? currentNode->left : currentNode->right;

                if (!currentNode) {
                    std::wcerr << u8"\nERRO: Dados de compactação inválidos ou corrompidos. Abortando descompressão." << std::endl;
                    error_found = true;
                    break; 
                }

                if (!currentNode->left && !currentNode->right) {
                    outputFile.put(currentNode->data);
                    currentNode = root; 
                    decoded_count++;
                }
            }
            if (error_found) break;
        }
    }

    inputFile.close();
    outputFile.close();
    delete root;
    std::wcout << u8"Descompactação por caracter concluída!" << std::endl;
}


// Realiza a compactação de um arquivo usando Huffman por palavras.
// Pré-condição: inputPath é um caminho válido para um arquivo de texto, outputPath é um caminho gravável.
// Pós-condição: Um arquivo binário compactado é criado em outputPath.
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
        write_wstring(outputFile, pair.first); 
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
    std::wcout << u8"Compactação por palavra concluída!" << std::endl;
}


// Realiza a descompactação de um arquivo compactado por palavras.
// Pré-condição: inputPath deve ser um arquivo válido gerado por 'compactar_palavra'.
// Pós-condição: Um arquivo de texto idêntico ao original é criado em outputPath.
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
    } else if (root) {
        std::wcout << u8"Descompactando dados..." << std::endl;
        HuffmanNode<std::wstring>* currentNode = root;
        char byte;
        long long decoded_count = 0;
        bool error_found = false;

        while (inputFile.get(byte) && decoded_count < total_token_count) {
            for (int i = 7; i >= 0; --i) {
                if (decoded_count == total_token_count) break;
                
                int bit = (byte >> i) & 1;
                currentNode = (bit == 0) ? currentNode->left : currentNode->right;

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
            }
            if (error_found) break;
        }
    }
    
    inputFile.close();
    outputFile.close();
    delete root;
    std::wcout << u8"Descompactação por palavra concluída!" << std::endl;
}

// Exibe o menu principal de opções para o usuário.
// Pré-condição: Nenhuma.
// Pós-condição: O menu é impresso na saída padrão.
void printMenu() {
    std::wcout << u8"1. Compactar arquivo (por caractere)\n";
    std::wcout << u8"2. Descompactar arquivo (por caractere)\n";
    std::wcout << u8"3. Compactar arquivo (por palavra)\n";
    std::wcout << u8"4. Descompactar arquivo (por palavra)\n";
    std::wcout << u8"0. Sair\n";
    std::wcout << u8"Escolha uma opção: ";
}