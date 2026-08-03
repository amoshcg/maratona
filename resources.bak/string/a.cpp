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
#define endl '\n'

int mex(vector<int> a){
	int n = a.size();
	for(int i = 0; i < n; i++){
		while(a[i] >= 0 && a[i] < n && a[a[i]] != a[i]){
			swap(a[i],a[a[i]]);
		}
	}
	for(int i = 0; i < n; i++){
		if(a[i] != i){
			return i;
		}
	}
	return n;
}


int manacher_odd_trivial(vector<int> w) {

	vector<int> v(w.size() + 2);
	v[0] = -1, v[w.size() + 1] = -2;

	for(int i = 0; i < w.size(); i++){
		v[i + 1] = w[i];
	}

	int ans = 0;

    int n = v.size();
    vector<int> p(n + 2);
	
    for(int i = 1; i <= n; i++) {
		vector<int> aux;
        while(v[i - p[i]] == v[i + p[i]]) {
			aux.push_back(v[i + p[i]]);
            p[i]++;
        }
		ans = max(ans, mex(aux));
    }

    return ans;
}

int manacher_even_trivial(vector<int> w) {

	vector<int> v;

	int i = 0;
	v.push_back(-2);
	while(i < w.size()){
		v.push_back(-1);
		v.push_back(w[i]);
		i++;
	}
	v.push_back(-1);
	v.push_back(-3);
	int ans = 0;
    int n = v.size();
    vector<int> p(n + 2);
	
    for(int i = 1; i < n - 1; i++) {
		vector<int> aux;
        while(v[i - p[i]] == v[i + p[i]]) {
			aux.push_back(v[i + p[i]]);
            p[i]++;
        }
		ans = max(ans, mex(aux));
    }

    return ans;
}



signed main(){
	fastio;
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
		n *= 2;
		vector<int> v(n);
		cin >> v;

		cout << manacher_even_trivial(v) << endl;
    }
	return 0;
}