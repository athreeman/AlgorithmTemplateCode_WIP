#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll mod = 1e9 + 7;
ll pw(ll a,ll b){}


//费马小定理,求逆元
ll inv_(ll a, ll p) {
    return pw(a, p - 2);
}

//暴力求逆元
//只需满足gcd(a,mod)=1即可
ll inv02_(ll a, ll mod) {
    a %= mod;
    for (ll t = 1; t < mod; t++) {
        if ((a * t) % mod == 1) return t;
    }
    return 1;
}