#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        heights.push_back(0);
        int ans = 0;
        stack<pair<int,int>> stck;
        for(int i = 0; i < heights.size(); i++){
            int idx = i;
            while(!stck.empty() && heights[i] < stck.top().first){
                idx = stck.top().second;
                ans = min(ans, stck.top().first * (i - stck.top().second));
                stck.pop();
            }
            stck.push({heights[i],idx});
        }
        cout << ans << endl;
    }
};
