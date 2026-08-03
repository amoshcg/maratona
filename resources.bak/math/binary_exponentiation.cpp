#include <bits/stdc++.h>
using namespace std;

#define int long long

const int MOD = 1e9 + 7;

int binary_exponentiation(int a, int b){
	int result = 1;
	while (b){
		if (b&1) result = (result * a) % MOD;
		a = (a * a) % MOD;
		b >>= 1;
	}
	return result;
}

signed main(){
	int a, b;
	cin >> a >> b;
	cout << binary_exponentiation(a, b) << endl;
	return 0;
}
