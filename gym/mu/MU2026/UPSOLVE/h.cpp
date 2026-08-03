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



struct segtree{
	vector<int> prefixo, sufixo, soma, ans;
	int tamanho;
	void init(int n){
		int i = 1;
		while(i < n) i *= 2;
		prefixo.assign(2 * i, 0);
		sufixo.assign(2* i, 0);
		soma.assign(2 * i, 0);
		ans.assign(2 * i, 0);	
		tamanho = i;
	}

	void set(int pos, int val, int x, int lx, int rx){
		if(rx - lx == 1){
			soma[x] = val != 1;
			prefixo[x] = val != 1;
			sufixo[x] = val != 1;
			ans[x] = val != 1;
			return;
		}
		int meio = (rx + lx) / 2;
		if (pos < meio) set(pos, val, 2*x+1, lx, meio);
		else set(pos, val, 2*x+2, meio, rx);
		soma[x] = soma[2*x+1] + soma[2*x+2];
		if((rx - lx) / 2 == soma[2*x+1]) prefixo[x] = soma[2*x+1] + prefixo[2*x+2];
		else prefixo[x] = prefixo[2*x+1];
		if((rx - lx) / 2 == soma[2*x+2]) sufixo[x] = soma[2*x+2] + sufixo[2*x+1];
		else sufixo[x] = sufixo[2*x+2];
		ans[x] = ans[2*x+1] + ans[2*x+2] + (sufixo[2*x+1] * prefixo[2*x+2]);
	}

	void set(int pos, int val){
		set(pos, val, 0, 0, tamanho);
	}
};

signed main(){
	fastio;
	int n, q;
	string s;
	cin >> n >> s >> q;
	
	segtree seg;
	seg.init(n);

	for(int i = 0; i < n; i++){
		seg.set(i, s[i] - '0');
	}

	int total = (n * (n + 1)) / 2;

	for(int i = 0; i < q; i++){
		int pos, val;
		cin >> pos >> val;
		seg.set(pos - 1, val);
		cout << total - seg.ans[0] << endl; 
	}

	return 0;
}
