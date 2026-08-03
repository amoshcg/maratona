#include <iostream>
#include <chrono>
#include <vector>
using namespace std;

bool is_prime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; ++i)
        if (n % i == 0) return false;
    return true;
}

int main() {
    auto start = chrono::high_resolution_clock::now();
    vector<int> primes;
    for (int i = 2; primes.size() < 100000; ++i) {
        if (is_prime(i)) primes.push_back(i);
    }
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout << "Tempo de CPU (CPU-bound): " << elapsed.count() << " segundos" << endl;
    return 0;
}