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


string encode(string s){
	int start = -1, n = s.size();
	for(int i = 0; i < n; i++){
		if(s[i] == '1'){
			start = i;
			break;
		}
	}

	if(start == -1) return s;

	string ans;
	for(int i = 0; i <= start; i++){
		ans += '2';
	}

	for(int i = start + 1; i < n; i++){
		ans += s[i];
	}
	return ans;
}

string decode(string s){
	int start = -1, end = -1, n = s.size();

	int dois = 0;
	for(int i = 0; i < n; i++){
		if(s[i] == '2') dois++;
	}

	if(dois == n) {
		string ans;
		for(int i = 0; i < n - 1; i++){
			ans += '0';
		} ans += '1';
		return ans;
	}

	for(int i = 0; i < n; i++){
		if(s[((i-1) % n + n) % n] != '2' && s[i] == '2'){
			start = i;
		}
		if(s[((i-1) % n + n) % n] == '2' && s[i] != '2'){
			end = ((i - 1) % n + n) % n;
		}
	}

	if(start == -1) return s;

	s[end] = '1';

	string ans;
	for(int i = start; i < n; i++){
		if(s[i] == '2') ans += '0';
		else ans += s[i];
	}

	for(int i = 0; i < start; i++){
		if(s[i] == '2') ans += '0';
		else ans += s[i];
	}
	return ans;
}

int main(){
	fastio;
	string op;
	cin >> op;
	int n;
	cin >> n;
	string s;
	cin >> s;
	if(op == "Encode"){
		cout << encode(s) << endl;
	} else {
		cout << decode(s) << endl;
	}
	return 0;
}
