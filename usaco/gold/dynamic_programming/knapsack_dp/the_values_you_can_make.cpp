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

signed main(){
	fastio;
	int n, k;
	cin >> n >> k;
	vector<int> coins(n);
	for(auto &c:coins) cin >> c;

	vector<vector<bool>> dp(k+1, vector<bool>(k+1, false));
	dp[0][0] = true;

	for(auto &c:coins){
		for(int i = k; i >= 0; i--) {
			for(int j = k; j >= 0; j--) {
            	if(i >= c && dp[i - c][j]) dp[i][j] = true;
            	if(j >= c && dp[i][j - c]) dp[i][j] = true;
        	}
		}
	}

	vector<int> ans;
	for(int i = 0; i <= k; i++){
		if(dp[i][k - i]) ans.push_back(i);
	}

	cout << ans.size() << endl;
	for(auto &a:ans) cout << a << " ";
	cout << endl;

	return 0;
}
