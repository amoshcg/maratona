#include <bits/stdc++.h>
using namespace std;

void func(int &val){
    val = 0;
}
int main(){
    int num = 100;
    func(num);
    cout << num;
    return 0;
}