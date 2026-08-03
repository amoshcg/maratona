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

vector<vector<int>> nodes;
vector<int> value;
vector<bool> visited;
vector<int> ans;

int dupla = 0;
map<int,int> mp;

void dfs(int u){
	visited[u] = true;

	mp[value[u]]++;
	if(mp[value[u]] == 2) dupla++;

	for(auto v:nodes[u]){
		if(!visited[v]) dfs(v);
	}

	ans[u] = dupla > 0;

	if(mp[value[u]] == 2) dupla--;

	mp[value[u]]--;
}

int main(){
	fastio;
	int n;
	cin >> n;
	value.resize(n);
	nodes.resize(n);
	visited.assign(n, false);
	ans.assign(n, 0);

	cin >> value;

	for(int i = 0; i < n - 1; i++){
		int x, y;
		cin >> x >> y;
		x--;
		y--;
		nodes[x].push_back(y);
		nodes[y].push_back(x);
	}
	dfs(0);
	for(auto &a:ans) cout << (a ? "Yes" : "No") << endl;
	return 0;
}
