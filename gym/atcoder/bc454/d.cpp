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


void xd(string &s){
	if(s.substr(s.size() - 4, 4) == "(xx)"){
		s.pop_back();
		s.pop_back();
		s.pop_back();
		s.pop_back();
		s.push_back('x');
		s.push_back('x');
	}
	
}

string to_s(stack<char> &stk){
	string s;
	while(!stk.empty()){
		s += stk.top();
		stk.pop();
	}
	reverse(s.begin(), s.end());
	return s;
}

// Desfaz tudo e depois compara
int main(){
	fastio;
	int t;
	cin >> t;
	while(t--){
		int i = 0, j = 0;
		string a, b;
		cin >> a >> b;

		string ans1 = {};
		for(int i = 0; i < a.size(); i++){
			ans1 += a[i];
			if(ans1.size() >= 4){
				xd(ans1);
			}
		}

		string ans2 = {};
		for(int i = 0; i < b.size(); i++){
			ans2 += b[i];
			if(ans2.size() >= 4){
				xd(ans2);
			}
		}

		if(ans1 == ans2) cout << "Yes" << endl;
		else cout << "No" << endl;
	}


	return 0;
}
