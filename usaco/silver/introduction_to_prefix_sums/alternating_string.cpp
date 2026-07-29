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
	int t;
	cin >> t;
	while(t--){
		int n;
		cin >> n;
		string s;
		cin >> s;
		vector<vector<int>> pref_odd(n+1, vector<int>(26)), pref_even(n+1, vector<int>(26));
		vector<vector<int>> suff_odd(n+1, vector<int>(26)), suff_even(n+1, vector<int>(26));
		for(int i = 1; i < n+1; i++){
			pref_odd[i] = pref_odd[i-1];
			pref_even[i] = pref_even[i-1];

			int atual = s[i-1] - 'a';

			if(i % 2 == 0) pref_even[i][atual]++;	
			else pref_odd[i][atual]++;
		}

		for(int i = n - 1; i >= 0; i--){
			suff_odd[i] = suff_odd[i+1];
			suff_even[i] = suff_even[i+1];

			int atual = s[i] - 'a';
			if(i % 2 == 0) suff_even[i][atual]++;	
			else suff_odd[i][atual]++;
		}

		if(n % 2 == 0){
			int max_a = 0, max_b = 0;
			for(int i = 0; i < 26; i++){
				max_a = max(max_a, pref_even[n][i]);
				max_b = max(max_b, pref_odd[n][i]);
			}
			cout << n - max_a - max_b << endl;
		} else {
			int ans = 1e9;
			for(int i = 0; i < n; i++){
				int atual = s[i] - 'a';
				pref_odd[i+1][atual]--;
				pref_even[i+1][atual]--;
				suff_odd[i][atual]--;
				suff_even[i][atual]--;

				int max_a = 0, max_b = 0;

				for(int j = 0; j < 26; j++){
					if(i % 2 == 0){
						max_a = max(max_a, pref_odd[i+1][j] + suff_even[i][j]);
						cout << pref_odd[i+1][j] << " " << suff_even[i][j] << endl;
					} else {
						max_a = max(max_a, pref_even[i+1][j] + suff_odd[i][j]);
						cout << pref_even[i+1][j] << " " << suff_odd[i][j] << endl;
					}
				}
				cout << endl;

				for(int j = 0; j < 26; j++){
					if(i % 2 == 0){
						max_b = max(max_b, pref_even[i+1][j] + suff_odd[i][j]);
						cout << pref_even[i+1][j] << " " << suff_odd[i][j] << endl;
					} else {
						max_b = max(max_b, pref_odd[i+1][j] + suff_even[i][j]);
						cout << pref_odd[i+1][j] << " " << suff_even[i][j] << endl;
					}
				}
				cout << endl;

				pref_odd[i+1][atual]++;
				pref_even[i+1][atual]++;
				suff_odd[i][atual]++;
				suff_even[i][atual]++;

				ans = min(ans, n - max_a - max_b);
			}
			cout << ans << endl;
		}
	}
	return 0;
}
