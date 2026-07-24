#include <bits/stdc++.h>
using namespace std;

// template <typename T, typename U>
// istream& operator>>(istream& is, pair<T, U>& p) {
// 	return is >> p.first >> p.second;
// }

// template <typename T>
// istream& operator>>(istream& is, vector<T>& v) {
// 	for(auto& elem: v){
// 		is >> elem;
// 	}
// 	return is;
// }

// template <typename T, typename U>
// ostream& operator<<(ostream& os, const std::pair<T, U>& p) {
// 	return os << "{" << p.first << ", " << p.second << "}";
// }

// template <typename T>
// concept IterableContainer = requires(T t) {
// 	begin(t);
// 	end(t);
// } && !same_as<T, string> && !same_as<T, string_view>;

// template<IterableContainer Container>
// ostream& operator<<(ostream& os, const Container& c) {
// 	os << "[";
// 	bool first = true;
// 	for(const auto& elem : c){
// 	if(!first) os << ", ";
//  		os << elem;
// 		first = false;
// 	}
// 	return os << "]";
// }

#define fastio ios_base::sync_with_stdio(false), cin.tie(nullptr);
#define int long long
#define ld long double
#define endl '\n'

struct input{
	string cow, zod, rel;
};

map<string,vector<input>> mp;
map<string, bool> visited;
map<string, int> zodiac;

int ans;
void dfs(string curr_zod = "Ox", string atual = "Bessie", int acc = 0){

	if(atual == "Elsie"){
		ans = acc;
		return;
	}

	visited[atual] = true;
	for(auto &prox:mp[atual]){

		if(!visited[prox.cow]){
			int curr_dis = 0;
			if(prox.rel == "next"){
				curr_dis = (12 - zodiac[curr_zod] + zodiac[prox.zod]) % 12;
				if(curr_dis == 0) curr_dis = 12;
				dfs(prox.zod, prox.cow, acc + curr_dis);
			}
			else {
				curr_dis = (12 - zodiac[prox.zod] + zodiac[curr_zod]) % 12;
				if(curr_dis == 0) curr_dis = 12;
				dfs(prox.zod, prox.cow, acc - curr_dis);
			}
		}
	}
}

signed main(){
	fastio;
	int n;
	cin >> n;
	zodiac["Ox"] = 0;
	zodiac["Tiger"] = 1;
	zodiac["Rabbit"] = 2;
	zodiac["Dragon"] = 3;
	zodiac["Snake"] = 4;
	zodiac["Horse"] = 5;
	zodiac["Goat"] = 6;
	zodiac["Monkey"] = 7;
	zodiac["Rooster"] = 8;
	zodiac["Dog"] = 9;
	zodiac["Pig"] = 10;
	zodiac["Rat"] = 11;

	for(int i = 0; i < n; i++){
		vector<string> aux;
		for(int j = 0; j < 8; j++){
			string x;
			cin >> x;
			aux.push_back(x);
		}

		if(aux[3] == "previous"){
			mp[aux[7]].push_back({aux[0] , aux[4], "previous"});
		} else {
			mp[aux[7]].push_back({aux[0] , aux[4], "next"});
		}
	}
	dfs();
	cout << abs((int)ans) << endl;
	return 0;
}
