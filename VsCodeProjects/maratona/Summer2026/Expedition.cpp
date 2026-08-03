#include<bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'
#define fastio ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)



signed main(){
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        priority_queue<pair<int,int>> gas_station;
        for(int i = 0; i < n; i++){
            pair<int,int> p;
            cin >> p.first >> p.second;
            gas_station.push(p);
        }

        // Usamos os maiores intervalos primeiro, caso ja tenhamos passado por um posto
        // mas nao abastecemos a gente pode usar ele depois para aumentar nosso alcance
        int gas, dis, stops = 0;
        cin >> gas >> dis;

        // Se eu conseguir ir direto do primeiro ponto de combustivel
        if(gas >= dis){
            cout << 1 << endl;
            break;
        }

        priority_queue<pair<int,int>> behind;
        // while(dis > 0 || gas_station.empty()){
        //     while()
        // }
        do {
            // Se consigo chegar no posto de combustivel guardo todos os postos pelo qual eu passo
            while(!gas_station.empty() && dis - gas <= gas_station.top().first){
                behind.push(gas_station.top());
                gas_station.pop();
            }

            // Carrego o combustivel
            if(!behind.empty()){
                gas += behind.top().second;
                behind.pop();
                stops++;
            }
            
            // Se consigo chegar no destino paro
            if(gas >= dis){
                cout << stops << endl;
                break;
            }

        } while(!behind.empty() || !gas_station.empty());

        if(gas < dis) cout << -1 << endl;
    }
}