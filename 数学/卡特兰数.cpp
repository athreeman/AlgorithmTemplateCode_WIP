#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// 卡特兰数：
// f(n) = C(2n, n) - C(2n, n - 1)
// f(n) = C(2n, n) / (n + 1)
// f(n) = f(n - 1) * ((4n - 2) / (n + 1))
// f(n) = [求和0 <= i <= n - 1]：f(i) * f(n - 1 - i)
// 其中, 公式1, 3, 4要求n >= 1
// 公式2, n >= 0

// 卡特兰数使用的核心在于：
// 1、对关系的转化, 不同状态定义但相同规模的映射转移
// 2、严格的状态转移

// 核心代码如下：
ll f1(int n) {
    f[n] = (C(2 * n, n) - C(2 * n, n - 1) + mod) % mod;
    return f[n];
}

ll f2(int n) {
    f[n] = C(2 * n, n) * invVal[n + 1] % mod;
    return f[n];
}

ll f3(int n) {
    f[0] = f[1] = 1;
    for (int i = 2;i <= n;i++) {
        f[i] = f[i - 1] * (4 * i - 2) % mod * invVal[i + 1] % mod;
    }
    return f[n];
}

ll f4(int n) {
    f[0] = f[1] = 1;
    for (int i = 2;i <= n;i++) {
        f[i] = 0;
        for (int j = 0;j <= i - 1;j++) {
            f[i] = (f[i] + f[j] * f[i - 1 - j] % mod) % mod;
        }
    }
    return f[n];
}


const int mod = 1e9 + 7;
const int MAXN = 2e5;
ll invVal[MAXN + 10];// 连续常数的逆元
ll fac[MAXN + 10];// fac[i]即(i!)对mod取模的结果
ll inv[MAXN + 10];// inv[i]即(i!)模mod意义下的逆元
ll f[MAXN + 10];


ll pw(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1)res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

ll inv_(ll a) {
    return pw(a, mod - 2);
}

void init(int n) {
    fac[0] = 1;
    for (ll i = 1;i <= n;i++) {
        fac[i] = fac[i - 1] * i % mod;
    }

    inv[0] = 1;
    inv[n] = inv_(fac[n]);
    for (ll i = n - 1;i >= 1;i--) {
        inv[i] = (i + 1) * inv[i + 1] % mod;
    }

    invVal[1] = 1;
    for (ll i = 2;i <= n;i++) {
        invVal[i] = mod - invVal[mod % i] * (mod / i) % mod;
    }

}

ll C(ll n, ll m) {
    return (((fac[n] * inv[m]) % mod) * inv[n - m]) % mod;
}
