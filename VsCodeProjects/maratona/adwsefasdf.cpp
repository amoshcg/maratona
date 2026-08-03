#include <bits/stdc++.h>
using namespace std;

// Generic printer for vector<T>
template <typename T>
ostream &operator<<(ostream &os, const vector<T> &v) {
    for (size_t i = 0; i < v.size(); ++i) {
        os << v[i];
        if (i + 1 < v.size()) os << ' ';
    }
    return os;
}
 
// Specialized printer for vector<vector<T>> (matrix)
template <typename T>
ostream &operator<<(ostream &os, const vector<vector<T>> &matrix) {
    for (size_t i = 0; i < matrix.size(); ++i) {
        os << matrix[i];
        if (i + 1 < matrix.size()) os << '\n';
    }
    return os;
}
 
#define novo(x, y) vector<x>v(y); for(auto &w:v) cin >> w;
 
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define bg3 ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(NULL);
#define int long signed int long
#define endl "\n"
 
int nxt() {
    int x;
    cin >> x;
    return x;
}



 
signed main(){
    // freopen("input.txt", "r", stdin);
    
    // freopen("angry.in", "r", stdin);
    // freopen("angry.out", "w", stdout);
    
    // auto start = chrono::high_resolution_clock::now();
 
    bg3;
    int n = nxt();
    
    vector<vector<int>> adj(n+1);

    for(int i = 0; i < n-1; i++){
        int x, y; cin >> x >> y;
        // int x = nxt(), y = nxt();
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    // cout << "adjacencia" << endl;
    // cout << adj << endl;

    vector<int> dis(n+1, 0);

    // vector<set<int>> dis(n+1); // Para guardar as distancias
    // dis[0].insert(1);

    queue<int> q;
    vector<bool> visited(n+1, false);
    q.push(1);
    visited[1] = true;
    dis[1] = 0;

    while(!q.empty()){
        int v = q.front();
        q.pop();
        
        // cout << v << " " << endl;
        for(auto e: adj[v]){
            if(!visited[e]){
                visited[e] = true;
                // cout << visited << endl;
                // cout << v << " " << e << " " << endl;
                q.push(e);

                dis[e] = dis[v] + 1;

                // dis[cnt].insert(e);
            }
        }
        // cout << cnt << endl;
    }

    vector<set<int>> ans(n+1);
    for(int i = 1; i <= n; i++){
        ans[dis[i]].insert(i);
    }

    // cout << dis << endl;

    // for(auto &an:ans){
    //     for(auto &a:an ) cout << a << " ";
    //     cout << endl;
    // }

    bool terminou = true;
    int d = 0;
    for(int i = 0; i < n; i++){
        int aux = nxt();
        // cout << aux << endl;
        if(ans[d].empty()) d++;
        if(ans[d].count(aux)){
            ans[d].erase(aux);
        } else {
            terminou = false;
            break;
        }
        // cout << aux << " " << d << endl;
    }


    

    if (terminou) cout << "Yes" << endl;
    else cout << "No" << endl;

    // auto end = chrono::high_resolution_clock::now();
    // std::chrono::duration<double, std::milli> duration = end - start;
    // std::cout << "Execution time: " << duration.count() << " ms\n";
    
    return 0;
}
 
// Dar um sort e ir explodindo
// Como o range e 1e9 nao e possivel guardar em um array
// O mais distante no caso seria o ultimo a explodir
// Portanto se o acharmos conseguimos determinar o limite da proxima explosao