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

const int MOD = 1e9 + 7;

signed main(){
	fastio;
	int n, m;
	cin >> n >> m;
	vector<int> values(n);
	for(auto &v:values) cin >> v;
	vector<vector<int>> dp(n, vector<int>(m + 2));

	if(values[0]){
		dp[0][values[0]] = 1;
	} else {
		for(int i = 1; i < m + 1; i++){
			dp[0][i] = 1;
		}
	}
	

	for(int i = 1; i < n; i++){
		
		int val = values[i];
		if(val == 0){
			for(int j = 1; j <= m; j++){
				dp[i][j] += dp[i-1][j - 1] + dp[i-1][j] + dp[i-1][j + 1];
				dp[i][j] %= MOD;
			}
		} else dp[i][val] += dp[i-1][val - 1] + dp[i-1][val] + dp[i-1][val + 1];
		dp[i][val] %= MOD;
	}

	if(values[n-1]){

		cout << dp[n-1][values[n-1]] << endl;

	} else {

		int ans = 0;
		for(int i = 0; i < m; i++){
			ans += dp[n-1][i] % MOD;
		}
		cout << ans << endl;
	}
	cout << dp << endl;
	return 0;
}
