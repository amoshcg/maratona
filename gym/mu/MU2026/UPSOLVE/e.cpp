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

struct segtree{
    vector<int> nobody, one;
    int tamanho=1;

    // Inicializa a segtree
    void init(int n){
        while(tamanho < n) tamanho*=2;
        nobody.assign(2*tamanho, 1LL);
		one.assign(2*tamanho, 0LL);
    }

    void build(vector<int>&v,int x,int lx,int rx){
        if(rx-lx==1){
            if(lx < v.size()) {
				nobody[x] = 100 - v[lx];
				one[x] = v[lx] * modinv(nobody[x]);
			}
            return;
        }
        int m=(lx+rx)/2;
        build(v,2*x+1,lx,m);
        build(v,2*x+2,m,rx);
        nobody[x] = (nobody[2*x+1] * nobody[2*x+2]) % MOD;
		one[x] = (one[2*x+1] + one[2*x+2]) % MOD;
    }

    segtree(vector<int>&v){
        init(v.size());
        build(v,0,0,tamanho);
    }

    void set(int pos, int valor, int x, int lx, int rx){
        if(rx-lx==1){
            nobody[x] = 100 - valor;
			one[x] = (valor * modinv(nobody[x])) % MOD;
            return;
        }
        int meio = (lx+rx)/2;
        if(pos < meio){
            set(pos,valor,2*x+1,lx,meio);
        } else {
            set(pos,valor,2*x+2,meio,rx);
        }
        nobody[x] = (nobody[2*x+1] * nobody[2*x+2]) % MOD;
		one[x] = (one[2*x+1] + one[2*x+2]) % MOD;
    }

    void set(int pos, int valor){
        set(pos, valor, 0, 0, tamanho);
    }

    int mult(int l, int r, int x, int lx, int rx){
        if(lx >= r || l >= rx) return 1;
        if(lx >= l && rx <= r) return nobody[x];
        int meio=(lx+rx)/2;
        int s1=mult(l,r,2*x+1,lx,meio);
        int s2=mult(l,r,2*x+2,meio,rx);
        return (s1 * s2) % MOD;
    }

	int sum(int l, int r, int x, int lx, int rx){
        if(lx >= r || l >= rx) return 0;
        if(lx >= l && rx <= r) return one[x];
        int meio=(lx+rx)/2;
        int s1=sum(l,r,2*x+1,lx,meio);
        int s2=sum(l,r,2*x+2,meio,rx);
        return (s1 + s2) % MOD;
    }

    int solve(int l, int r){
		// cout << "func "<< sum(l, r, 0, 0, tamanho) << endl;
		// cout << mult(l, r, 0, 0, tamanho) << endl;
        // cout << fastExpo(100, r - l) << endl;
        // cout << modinv(fastExpo(100, r - l)) << endl;
		int ninguem = (modinv(fastExpo(100, r - l)) * mult(l, r, 0, 0, tamanho)) % MOD;
		int um = (1 + sum(l, r, 0, 0, tamanho)) % MOD;
        return (ninguem * um) % MOD;
    }
};

signed main(){
	fastio;
	int n, q;
	cin >> n >> q;
	vector<int> v(n);
	cin >> v;

	segtree s(v);

	// for(int i = 0; i < 2 * s.tamanho; i++){
	// 	cout << s.nobody[i] << " ";
	// } cout << endl;

	// for(int i = 0; i < 2 * s.tamanho; i++){
	// 	cout << s.one[i] << " ";
	// } cout << endl;

	for(int i = 0; i < q; i++){
		int type;
		cin >> type;
		if(type == 2) {
			int a;
			cin >> a;
			// cout << "resp" << endl;
			cout << s.solve(a, n) << endl;
            // cout << "resp" << endl;
		} else {
			int a, b;
			cin >> a >> b;
			s.set(a - 1, b);
		}
	}

    // for(int i = 0; i < 2 * s.tamanho; i++){
	// 	cout << s.nobody[i] << " ";
	// } cout << endl;

	// for(int i = 0; i < 2 * s.tamanho; i++){
	// 	cout << s.one[i] << " ";
	// } cout << endl;

    // cout << modinv(10000) << endl;
	// cout << ((50 * 50 * modinv(10000))%MOD * (1 + 50 * modinv(50) + 50 * modinv(50))%MOD)%MOD << endl;

	// cout << (modinv(10000) * (1 + (modinv(1) * 99) + (modinv(1) * 99) % MOD) % MOD) << endl;

	// cout << ((int)199 * modinv(10000)) % MOD << endl;
	return 0;
}