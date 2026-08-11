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

int MOD = 1e9 + 7;

signed main(){
	fastio;
	int n;
	cin >> n;
	vector<vector<char>> grid(n, vector<char>(n));
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			cin >> grid[i][j];
		}
	}

	vector<vector<int>> dp(n, vector<int>(n));
	if(grid[0][0] != '*') dp[0][0] = 1;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(grid[i][j] != '*'){
				if(i - 1 >= 0) dp[i][j] += dp[i - 1][j];
				dp[i][j] %= MOD;
				if(j - 1 >= 0) dp[i][j] += dp[i][j - 1];
				dp[i][j] %= MOD;
			}
		}
	}

	cout << dp[n - 1][n - 1] << endl;
	return 0;
}
