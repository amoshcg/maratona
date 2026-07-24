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

void setIO(string s){
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
}

map<int,vector<int>> graph;
void dfs(vector<bool> &visited, int curr){
	visited[curr] = true;
	for(auto next:graph[curr]){
		if(!visited[next]) dfs(visited, next);
	}
}

signed main(){
	fastio;
	setIO("hoofball");
	int n;
	cin >> n;
	vector<int> pos(n);
	for(int i = 0; i < n; i++){
		cin >> pos[i];
	}

	if(n == 1) {
		cout << 1 << endl;
		return 0;
	}

	sort(pos.begin(), pos.end());

	for(int i = n - 2; i > 0; i--){
		if(abs(pos[i - 1] - pos[i]) <= abs(pos[i + 1] - pos[i])){
			graph[i].push_back(i - 1);
		} else {
			graph[i].push_back(i + 1);
		}
	}

	graph[0].push_back(1);
	graph[n-1].push_back(n-2);

	int ans = 0, curr = 0;
	vector<bool> visited(n);
	for(int i = n - 1; i >= 0; i--){
		if(!visited[i]) {
			dfs(visited, i);
			curr++;
		}
	}
	ans = max(curr, ans);

	curr = 1;
	visited.assign(n, false);
	dfs(visited, 0);
	for(int i = n - 1; i >= 0; i--){
		if(!visited[i]) {
			dfs(visited, i);
			curr++;
		}
	}
	ans = min(curr, ans);

	curr = 0;
	visited.assign(n, false);
	for(int i = 0; i < n; i++){
		if(!visited[i]) {
			dfs(visited, i);
			curr++;
		}
	}
	ans = min(curr, ans);
	cout << ans << endl;


	for(auto [g, viz]:graph){
		cout << g << ": "<< endl;
		for(auto w:viz) cout << w << " ";
		cout << endl;
	}
	return 0;
}
