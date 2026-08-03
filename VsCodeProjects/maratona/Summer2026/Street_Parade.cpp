#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'
#define fastio ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

signed main(){
    fastio;
    int n;
    cin >> n;
    while(n != 0){
        vector<int> v(n);
        for(int i = 0; i < n; i++){
            cin >> v[i];
        }
        int atual = 1;
        stack<int> stck1, stck2;
        for(int i = 0; i < n; i++){
            if(v[i] ==  atual) {
                stck1.push(v[i]);
                atual++;
            }
            else stck2.push(v[i]);

            while(!stck1.empty() && !stck2.empty() && stck2.top() == stck1.top() + 1){
                stck1.push(stck2.top());
                stck2.pop();
            }
        }
        if(stck2.empty()) cout << "yes" << endl;
        else cout << "no" << endl;
        cin >> n;
    }
    return 0;
}