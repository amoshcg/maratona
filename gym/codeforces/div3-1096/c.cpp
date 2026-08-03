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
#define ld long double

signed main(){
	fastio;
	int t;
	cin >> t;
	while(t--){
		int n;
		cin >> n;
		vector<int> v(n), mod6, mod3, mod2, one, rest;
		cin >> v;
		for(int i = 0; i < n; i++){
			if(v[i] % 6 == 0){
				mod6.push_back(v[i]);
			} else if (v[i] % 3 == 0){
				mod3.push_back(v[i]);
			} else if (v[i] % 2 == 0){
				mod2.push_back(v[i]);
			} else if (v[i] == 1){
				one.push_back(v[i]);
			} else {
				rest.push_back(v[i]);
			}
		}

		for(auto o:mod6) cout << o << " ";
		for(auto o:mod3) cout << o << " ";
		for(auto o:one) cout << o << " ";
		for(auto o:rest) cout << o << " ";
		for(auto o:mod2) cout << o << " ";
		
		
		
		cout << endl;

		// cout << one << rest << mod2 << mod6 << mod3 << endl;
	}
	return 0;
}
