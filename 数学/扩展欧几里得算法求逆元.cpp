#include<bits/stdc++.h>
using namespace std;
using ll = long long;
ll exgcd(ll a, ll b, ll& x, ll& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    return exgcd(b, a % b, y, x);
}

// 求解a在模mod意义下的逆元
// 要求a,mod必须互质
// 时间复杂度O((logmin(a, mod)) ^ 3)
ll inv(ll a, ll mod) {
    ll x, y;
    exgcd(a, mod, x, y);
    x = (x % mod + mod) % mod;
    return x;
}
