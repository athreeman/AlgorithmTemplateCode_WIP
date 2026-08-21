#include<bits/stdc++.h>
using namespace std;
using ll = long long;
#define ill __int128_t
//快速幂
ll pw(ll a, ll b, ll mod) {
    ll res = 1;
    while (b) {
        if (b & 1) {
            res = ill(res) * ill(a) % mod;
        }
        a = ill(a) * ill(a) % mod;
        b >>= 1;
    }
    return res;
}