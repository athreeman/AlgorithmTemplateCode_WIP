#include<bits/stdc++.h>
using namespace std;
//Raney引理:若整数序列(下标1~m)每一项不超过1(a[i]<=1),总和为正整数n,
//则它的m个循环移位中恰有n个移位的所有非空前缀和为正
void Raney() {
    cout << "Raney:" << '\n';
    const int m = 22;
    int arr[m + 1] = { 0,1,1,1,-2,1,-1,1,1,-3,1,1,
        -2,1,1,1,1,1,1,-1,-2,1,1 };
    int n = 0;
    for (int i = 1;i <= m;i++) {
        n += arr[i];
    }
    cout << n << ' ' << m << '\n';
    int cnt = 0;
    for (int i = 1;i <= m;i++) {
        int sum = 0;
        int flg = 1;
        for (int j = i;j <= i + m - 1;j++) {
            sum += arr[(j - 1) % m + 1];
            if (sum <= 0)flg = 0;
        }
        if (flg)cnt++;
    }
    cout << "n: " << n << '\n';
    cout << "cnt: " << cnt << '\n';
}