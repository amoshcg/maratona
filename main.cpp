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
} && !is_convertible_v<T, string_view>;

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
#define ld long double
#define endl '\n'

set<pair<int,int>> ans;

void valid(vector<int> a, vector<int> b, int valor, int n){
	set<int> aux;
	// vemos primeiro se a esta contido
	bool init = false;
	int count = 1;
	for(int i = 1; i < a.size(); i++){
		
		if(valor == a[i] || valor == b[i]) {
			count++;
			continue;
		}
		
		if(!init){
			aux.insert(a[i]);
			aux.insert(b[i]);
			init = true;
		} else {
			vector<int> remove;
			for(auto aa:aux) if(aa != a[i] && aa != b[i]) remove.push_back(aa);
			for(auto r:remove) aux.erase(r);
		}

		if(aux.empty()) break;
	}

	for(auto aa:aux){

		if(aa == valor) continue;

		int maior = max(valor, aa);
		int menor = min(valor, aa);
		ans.insert({menor, maior});
		// cout <<"valor " << valor << " " << aa << endl;
	}

	if(count == a.size() && aux.empty()){
		for(int i = 1; i <= n; i++){
			if(valor != i){
				int maior = max(valor, i);
				int menor = min(valor, i);
				ans.insert({menor, maior});
			}
		}
	}
}

signed main(){
	fastio;
	int n, m;
	cin >> n >> m;
	vector<int> a(m), b(m);
	for(int i = 0; i < m; i++){
		cin >> a[i] >> b[i];
	}

	valid(a, b, a[0], n);
	valid(a, b, b[0], n);

	// cout << endl;

	// for(auto aa:ans) cout << aa.first << " " << aa.second << endl;

	cout << ans.size() << endl;
	return 0;
}