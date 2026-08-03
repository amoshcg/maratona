#include <bits/stdc++.h>
using namespace std;

int main(){
    int n, m;
    cin >> n >> m;
    vector<int> nums1(n), nums2(m), ans(m+1, -1);
    for(int i = 0; i < n; i++){
        cin >> nums1[i];
    }
    for(int i = 0; i < m; i++){
        cin >> nums2[i];
    }
    stack<int> stck;
    for(int i = 0; i < nums2.size(); i++){
        cout << i << endl;
        while(!stck.empty() && stck.top() < nums2[i]){
            ans[stck.top()] = nums2[i];
            stck.pop();
        }

        stck.push(nums2[i]);
    }

    cout << "terminou" << endl;

    for(int i = 0; i < nums1.size(); i++){
        cout << ans[nums1[i]] << " ";
    }
    cout << endl;
}