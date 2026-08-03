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
		vector<int> v(n);
		for(int i = 0; i < n; i++){
			cin >> v[i];
		}
		// priority_queue<int> pq;
		// pq.push(v[0]);
		// int ans = 0;
		// for(int i = 1; i < n; i++){
		// 	while(!pq.empty() && pq.top() > v[i]){
		// 		ans += pq.top() - v[i];
		// 		pq.pop();
		// 		pq.push(v[i]);
		// 	}
		// 	pq.push(v[i]);
			
		// }
		// cout << "ans " << ans << endl;

		vector<int> w = v;

		sort(w.begin(), w.end());

		int ans = 0;
		for(int i = 0; i < n; i++){
			ans += w[i] - v[i];
		}

		cout << "ans " << ans << endl;

		for(auto x:v) cout << x << " ";
		cout << endl;
		
		for(auto x:w) cout << x << " ";
		cout << endl;
	}
	return 0;
}

// Basicamente do que sobrou preciso remover um que me de a melhor opcao
