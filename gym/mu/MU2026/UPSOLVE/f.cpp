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

const int MAX = 1e18;

signed main(){
	fastio;
	int x, n;
	cin >> x >> n;
	vector<pair<int,int>> v(n);
	cin >> v;

	vector<int> dp(x + 1, MAX);
	dp[0] = 0;
	for(auto &car:v){
		for(int i = x; i > 0; i--){
			for(int j = 1; j <= car.first; j++){
				if(i - j >= 0) dp[i] = min(dp[i], dp[i - j] + car.second);
			}
		}
	}
	
	if(dp.back() != MAX) cout << dp.back() << endl;
	else cout << -1 << endl;
	return 0;
}
