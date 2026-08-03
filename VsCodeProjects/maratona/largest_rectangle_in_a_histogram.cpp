#include <bits/stdc++.h>
using namespace std;

#define int long long

signed main(){
    int size;
    cin >> size;
    while(size != 0){
        vector<int> v(size);
        for(int i = 0; i < size; i++){
            cin >> v[i];
        }

        v.push_back(0);

        int ans = 0;
        stack<pair<int,int>> stck;
        for(int i = 0; i < v.size(); i++){
            int start = i;
            while(!stck.empty() && stck.top().first > v[i]){
                ans = max(ans, stck.top().first * (i - stck.top().second));
                start = stck.top().second;
                stck.pop();
            }
            stck.push({v[i],start});
        }

        cout << ans << endl;
        cin >> size;
    }
    return 0;
}