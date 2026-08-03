#include<bits/stdc++.h>
using namespace std;

int fibonacci(int n) {
    if (n <= 1) return n;                       // Casos base
    return fibonacci(n - 1) + fibonacci(n - 2); // Chamada recursiva
}

int main(){
    int n;
    cin >> n;
    cout << fibonacci(n) << endl;
    return 0;
}

// 0, 1, 1, 2, 3, 5