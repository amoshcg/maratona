#include <iostream>
#include <chrono>
#include <vector>
using namespace std;

int main() {
    const int N = 10000;
    auto start = chrono::high_resolution_clock::now();
    vector<vector<double>> matriz(N, vector<double>(N, 1.0));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            matriz[i][j] *= 2;

    double soma = 0;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            soma += matriz[i][j];

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout << "Tempo de CPU (Memory-bound): " << elapsed.count() << " segundos" << endl;
    return 0;
}