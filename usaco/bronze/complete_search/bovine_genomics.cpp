#include <bits/stdc++.h>
using namespace std;

// template <typename T, typename U>
// istream& operator>>(istream& is, pair<T, U>& p) {
// 	return is >> p.first >> p.second;
// }

// template <typename T>
// istream& operator>>(istream& is, vector<T>& v) {
// 	for(auto& elem: v){
// 		is >> elem;
// 	}
// 	return is;
// }

// template <typename T, typename U>
// ostream& operator<<(ostream& os, const std::pair<T, U>& p) {
// 	return os << "{" << p.first << ", " << p.second << "}";
// }

// template <typename T>
// concept IterableContainer = requires(T t) {
// 	begin(t);
// 	end(t);
// } && !same_as<T, string> && !same_as<T, string_view>;

// template<IterableContainer Container>
// ostream& operator<<(ostream& os, const Container& c) {
// 	os << "[";
// 	bool first = true;
// 	for(const auto& elem : c){
// 	if(!first) os << ", ";
//  		os << elem;
// 		first = false;
// 	}
// 	return os << "]";
// }

#define fastio ios_base::sync_with_stdio(false), cin.tie(nullptr);
#define int long long
#define ld long double
#define endl '\n'

void setIO(string s){
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
}

// Se não fizer i = 0, j = i + 1, k = j + 1, não passa no tempo
// Mesmo i = 0, j = i, k = j não passa

signed main(){
	fastio;
	setIO("cownomics");
	int n, m;
	cin >> n >> m;
	vector<string> spotty(n), plain(n);
	for(int i = 0; i < n; i++) cin >> spotty[i];
	for(int i = 0; i < n; i++) cin >> plain[i];

	int ans = 0;
	for(int i = 0; i < m; i++){
		for(int j = i + 1; j < m; j++){
			for(int k = j + 1; k < m; k++){
				if(i == j || i == k || j == k) continue;
				set<string> s, p;
				for(int l = 0; l < n; l++) {
					string aux = {spotty[l][i], spotty[l][j], spotty[l][k]};
					s.insert(aux);
				}
				for(int l = 0; l < n; l++) {
					string aux = {plain[l][i], plain[l][j], plain[l][k]};
					p.insert(aux);
				}
				bool valid = true;
				for(auto s2:s) if(p.count(s2)) valid = false;
				for(auto p2:p) if(s.count(p2)) valid = false;
				if(valid) ans++;
			}
		}
	}
	cout << ans << endl;
	return 0;
}