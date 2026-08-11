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
	int n, q;
	cin >> n >> q;
	vector<int> v(n);

	int x = 0;

	// cout << n << q << endl;

	vector<bool> taken(n);
	vector<int> bigger;
	for(int i = 0; i < q; i++){
		int op;
		cin >> op;

		if(op == 1){
			int pos;
			cin >> pos;
			x ^= v[pos - 1];
			v[pos - 1]++;
			x ^= v[pos - 1];

			
			if(v[pos - 1] && !taken[pos - 1]){
				taken[pos - 1] = true;
				bigger.push_back(pos - 1);
			}
			
			// cout << "pos " << pos << endl;
		} else {
			vector<int> aux;
			for(int j = 0; j < bigger.size(); j++){
				x ^= v[bigger[j]];
				v[bigger[j]]--;
				x ^= v[bigger[j]];
				if(v[bigger[j]] > 0) aux.push_back(bigger[j]);
				else taken[bigger[j]] = false;
			}
			bigger = aux;
		}

		cout << x << endl;
	}
	return 0;
}
