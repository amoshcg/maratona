#include<bits/stdc++.h>
using namespace std;

int fatorial(int n) {
    if (n <= 1) return 1;         // Caso base
    return n * fatorial(n - 1);   // Chamada recursiva
}

int main(){
    int n;
    cin >> n;
    cout << fatorial(n) << endl;
    return 0;
}

// n! = n * (n-1) * (n-2) * ... * 1