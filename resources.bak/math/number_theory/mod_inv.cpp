#include <bits/stdc++.h>
using namespace std;

#define int long long

const int MAX = 1e6+1, MOD = 1e9 + 7;

int fat[MAX], invfat[MAX];

int fastExpo(int base, int exp) {
    int res = 1;
    while(exp) {
        if (exp & 1) res = res * base % MOD;
        base = base * base % MOD;
        exp >>= 1;
    }
    return res % MOD;
}

int modinv(int n) {
    return fastExpo(n, MOD - 2);
}

void build(){
    fat[0] = 1;
    for (int i = 1; i < MAX; i++) fat[i] = (fat[i-1] * i) % MOD;
    invfat[MAX-1] = modinv(fat[MAX-1]);
    for (int i = MAX - 2; i >= 0; i--) invfat[i] = (invfat[i+1] * (i+1)) % MOD;
}

int comb(int a, int b){
    if (b > a || a < 0 || b < 0) return 0;
    return (((fat[a] * invfat[b]) % MOD) * invfat[a-b]) % MOD;
}

signed main(){
	build();
	int n;
	cin >> n;

	for(int i = 0; i < n; i++){
		int a, b;
		cin >> a >> b;
		cout << comb(a, b) << endl;
	}
}
