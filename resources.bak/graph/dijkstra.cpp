#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX 1e18

pair<vector<int>,vector<int>> dijkstra(const vector<vector<pair<int,int>>> &adj, const int &start){
    vector<int> distancia(adj.size(), MAX), prev(adj.size(), -1);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    distancia[start] = 0;
    pq.push({0, start});
    
    while(!pq.empty()){
        int dist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if(dist > distancia[u]) continue;

        for(auto edge:adj[u]){
            int v = edge.first;
            int w = edge.second;

            if(distancia[u] + w < distancia[v]){
                distancia[v] = distancia[u] + w;
                prev[v] = u;
                pq.push({distancia[v], v});
            }
        }
    }
    return {distancia, prev};
}

vector<int> findShortestPath(const pair<vector<int>, vector<int>> &dijkstra, int start, int end){
    vector<int> path;
    if(dijkstra.first[end] == MAX) return path;
    
    for(int current = end; current != -1; current = dijkstra.second[current]){
        path.push_back(current);
    }

    reverse(path.begin(), path.end());
    return path;
}

signed main(){
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
        vertice[u].push_back({v, w});
        vertice[v].push_back({u, w});
    }
 
    auto tempo_main = dijkstra(vertice, main).first;
    auto tempo_ic = dijkstra(vertice, ic).first;


 
    for(int i = 0; i < q; i++){
        int x;
        cin >> x;
        x--;
        cout << tempo_main[x] + tempo_ic[main] - tempo_ic[x] << endl;
    }
    return 0;
}