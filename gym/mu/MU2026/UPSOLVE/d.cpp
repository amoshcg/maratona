#include <bits/stdc++.h>
using namespace std;

template <typename T, typename U>
istream& operator>>(istream& is, pair<T, U>& p) {
	return is >> p.first >> p.second;
}

template <typename T>
istream& operator>>(istream& is, vector<T>& v) {
	for(auto& elem: v){
		is >> elem;
	}
	return is;
}

template <typename T, typename U>
ostream& operator<<(ostream& os, const std::pair<T, U>& p) {
	return os << "{" << p.first << ", " << p.second << "}";
}

template <typename T>
concept IterableContainer = requires(T t) {
	begin(t);
	end(t);
} && !same_as<T, string> && !same_as<T, string_view>;

template<IterableContainer Container>
ostream& operator<<(ostream& os, const Container& c) {
	os << "[";
	bool first = true;
	for(const auto& elem : c){
	if(!first) os << ", ";
 		os << elem;
		first = false;
	}
	return os << "]";
}

#define fastio ios_base::sync_with_stdio(false), cin.tie(nullptr);
#define int long long

const int MOD = 1e9 + 7;
const int MAX = 1e6 + 1;

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

int somatorio(int k, vector<int> &sk){
	int acc = 0;
	for(int i = 1; i < k; i++){
		acc = (acc + comb(k + 1, i) * sk[i]) % MOD;
	}
	return acc;
}

signed main(){
	fastio;
	build();
	int t;
	cin >> t;
	while(t--){
		int n, k;
		cin >> n >> k;
		vector<int> sk(k+1);
		for(int i = 1; i <= k; i++){
			sk[i] = (((fastExpo(1+n, i+1) % MOD - (n + 1 + somatorio(i, sk) % MOD)) % MOD + MOD) % MOD * modinv(i+1)) % MOD;
		}
		cout << sk.back() << endl;
	}
	
	return 0;
}
