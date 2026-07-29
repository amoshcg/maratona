#include <bits/stdc++.h>
using namespace std;

void setIO(string s){
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
}

signed main(){
    cin.tie(0);
    cin.sync_with_stdio(0);
    int r, c, u;
    cin >> r >> c >> u;
    vector<vector<char>> image(r, vector<char>(c));
    pair<int,int> stockholm;
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            cin >> image[i][j];
            if(image[i][j] == 'S') stockholm = {i, j};
        }
    }

    vector<int> dx = {-1, 1, 0, 0}, dy = {0, 0, -1, 1};
    vector<vector<bool>> visited(r, vector<bool>(c));

    auto valid = [&](int x, int y){
        if(x >= r || x < 0) return false;
        if(y >= c || y < 0) return false;
        if(image[x][y] == '.') return false;
        return true;
    };

    int land = 0;
    auto dfs = [&](int a, int b){
        stack<pair<int,int>> stk;
        stk.push({a, b});
        visited[a][b] = true;
        while(!stk.empty()){
            int x = stk.top().first;
            int y = stk.top().second;
            stk.pop();

            land++;

            for(int i = 0; i < 4; i++){

                if(!valid(x + dx[i], y + dy[i])) continue;
                if(visited[x + dx[i]][y + dy[i]]) continue;

                stk.push({x + dx[i], y + dy[i]});
                visited[x + dx[i]][y + dy[i]] = true;
            }
        }
    };

    dfs(stockholm.first, stockholm.second);

    cout << land << endl;
    
    while(u--){
        int new_x, new_y;
        cin >> new_x >> new_y;
        new_x--;
        new_y--;
        image[new_x][new_y] = '#';
        for(int i = 0; i < 4; i++){
            
            if(!valid(new_x + dx[i], new_y + dy[i])) continue;

            // Se algum vizinho ja foi for visitado
            if(visited[new_x + dx[i]][new_y + dy[i]]){
                dfs(new_x, new_y);
                break;
            }
        }

        cout << land << endl;
    }
}