#include<bits/stdc++.h>
using namespace std;
using ll = long long;
//快速幂
ll pw(ll a, ll b, ll mod) {//...
}
//Miller_Rabin算法测质数
//辅助验证函数
bool witness(ll a, ll n) {
    ll u = n - 1;
    int t = 0;
    while ((u & 1) == 0) {
        t++;
        u >>= 1;
    }
    ll x1 = pw(a, u, n), x2;
    for (int i = 1;i <= t;i++) {
        x2 = pw(x1, 2, n);
        if (x2 == 1 && x1 != 1 && x1 != n - 1) {
            return true;
        }
        x1 = x2;
    }
    if (x1 != 1) {
        return true;
    }
    return false;
}
//MR_p测试数组
ll MR_p[] = { 2,3,5,7,11,13,17,19,23,29,31,37 };
bool Miller_Rabin(ll n) {
    //模板例题：https://www.luogu.com.cn/problem/U148828
    //判断x是否为质数
    if (n <= 2) {
        return n == 2;
    }
    if ((n & 1) == 0) {
        return false;
    }
    for (ll p : MR_p) {
        if (p >= n)break;
        if (witness(p, n)) {
            return false;
        }
    }
    return true;
}