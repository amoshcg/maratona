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

void min_dist(vector<int> &tempo, vector<vector<pair<int,int>>> &vertice, int start){
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0, start});
    tempo[start] = 0;

    while(!pq.empty()){
        int dist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if(dist > tempo[u]) continue;

        for(auto edge:vertice[u]){
            int v = edge.first;
            int w = edge.second;

            if (tempo[u] + w < tempo[v]){
                tempo[v] = tempo[u] + w;
                pq.push({tempo[v], v});
            }
        }
    }
}

signed main(){
	// fastio;
    int n, m, q, main, ic;
    cin >> n >> m >> q >> main >> ic;
    main--;
    ic--;
    vector<vector<pair<int,int>>> vertice(n);
    for(int i = 0; i < m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        vertice[u].push_back({v,w});
        vertice[v].push_back({u,w});
    }

    vector<int> tempo_main(n, LONG_LONG_MAX);
    min_dist(tempo_main, vertice, main);

    vector<int> tempo_ic(n, LONG_LONG_MAX);
    min_dist(tempo_ic, vertice, ic);

    for(int i = 0; i < q; i++){
        int x;
        cin >> x;
        x--;
        cout << tempo_main[x] + tempo_ic[main] - tempo_ic[x] << endl;
    }
	return 0;
}
