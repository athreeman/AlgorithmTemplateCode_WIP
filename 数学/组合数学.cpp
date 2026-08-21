#include<bits/stdc++.h>
using namespace std;

// m=[0,n]
// 求和C(n,m)*2^m=3^n
// C(n,0)*2^0+C(n,1)*2^1+...+C(n,m)*2^m+...+C(n,n)*2^n=3^n


//排列组合
ll C(ll n, ll m) {
    if (m == 0 || m == n)return 1;
    else if (m<0 || m>n)return 0;
    ll ans = N[n] % mod * inv_(N[m] * N[n - m], mod) % mod;
    return ans;
}


ll f(ll n, ll l, ll k) {
    // n个元素(数量不限),要求用n个元素凑出长度=l的数组
    // 两个相同元素之间的间隔要>=k
    // 0<=k<n<=l
    // 可能的方案数=n!*(n-k)^(l-k)/(n-k)!
    // n-k的l-k次幂
    return N[n] * pw(n - k, l - k) % mod * inv_(N[n - k], mod);
}