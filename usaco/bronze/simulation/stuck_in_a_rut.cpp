#include <bits/stdc++.h>
using namespace std;

struct cow{
    char direction;
    int x, y;
};

int main(){
    cin.tie(0);
    cin.sync_with_stdio(0);
    int n;
    cin >> n;
    vector<cow> cows(n);

    for(int i = 0; i < n; i++){
        cin >> cows[i].direction >> cows[i].x >> cows[i].y;
    }

    vector<int> northbound, eastbound;
    for(int i = 0; i < n; i++){
        if(cows[i].direction == 'E') eastbound.push_back(i);
        else northbound.push_back(i);
    }

    vector<pair<int, pair<int,int>>> intersections;

    for(int i = 0; i < northbound.size(); i++){
        for(int j = 0; j < eastbound.size(); j++){
            int nx = cows[northbound[i]].x, ny = cows[northbound[i]].y;
            int ex = cows[eastbound[j]].x, ey = cows[eastbound[j]].y;

            if(ey < ny || nx < ex) continue;

            if(ey - ny > nx - ex) intersections.push_back({ey - ny, {northbound[i], eastbound[j]}});
            else if (ey - ny < nx - ex) intersections.push_back({nx - ex, {eastbound[j], northbound[i]}});
        }
    }

    sort(intersections.begin(), intersections.end());

    vector<int> blocked(n, -1);
    vector<int> distance(n);
    for(int i = 0; i < intersections.size(); i++){
        int t = intersections[i].first;
        int a = intersections[i].second.first;
        int b = intersections[i].second.second;

        // Caso uma vaca já tenha sido bloqueada
        // Não substituir por uma intersecção posterior
        if(blocked[a] != -1) continue;

        if(cows[a].direction == 'E'){
            if(blocked[b] == -1 || cows[a].y < blocked[b]) {
                blocked[a] = cows[b].x;
                distance[a] = t;
            }
        } else {
            if(blocked[b] == -1 || cows[a].x < blocked[b]) {
                blocked[a] = cows[b].y;
                distance[a] = t;
            }
        }
    }

    for(auto d:distance) {
        if(d == 0) cout << "Infinity" << endl;
        else cout << d << endl;
    }
}
