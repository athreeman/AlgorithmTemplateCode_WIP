#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll mod = 1e9 + 7;


//逆元的线性递归
//例题：https://www.luogu.com.cn/problem/P3811
ll inv[3000001];
void initial_inv(ll n, ll p) {
    inv[1] = 1;
    for (ll i = 2;i <= n;i++) {
        inv[i] = p - inv[p % i] * (p / i) % p;
    }
}