#include "funcoes.hpp"

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
             continue;
        }

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
        }
    }

    std::wcout << u8"Programa finalizado.\n";
    return 0;
}