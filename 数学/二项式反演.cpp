#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// 二项式反演：
// 以下f和g函数都是对i范围上的求和
// 0 <= i <= n
// g(n) = (-1)^i * C(n, i) * f(i) 等价于 f(n) = (-1)^i * C(n, i) * g(i)
// g(n) = C(n, i) * f(i) 等价于 f(n) = (-1)^(n - i) * C(n, i) * g(i)

// n <= i <= N
// g(n) = (-1)^i * C(i, n) * f(i) 等价于 f(n) = (-1)^i * C(i, n) * g(i)
// g(n) = C(i, n) * f(i) 等价于 f(n) = (-1)^(i - n) * C(i, n) * g(i)

// g(i)：钦定必须选择某i个元素, 且形成的交集元素至少包含这i个
// 2 ^ (n - i)：选择了必选的i个元素的所有集合(i个必选, 决定集合不同的项是其他n - i个, n - i个任选)
// 2 ^ (2 ^ (n - i)) - 1：所有选择了必选元素的所有集合, 选或不选的方案数(-1即不能为空)
// g(i) = C(n, i) * (2 ^ (2 ^ (n - i)) - 1)

// f(i)：挑选集合后, 集合形成的交集刚好是i个元素
// 特征式：g(k) = f(i) * C(i, k) 求和(k <= i <= n)
// 表示：从f(i)刚好的i个元素中, 选择出k个作为g(k)钦定的至少k个元素
// 命中了第四个反演式
// f(k) = (-1)^(i - k) * C(i, k) * g(i) 求和(k <= i <= n)

// https://www.luogu.com.cn/problem/P10596
// 核心：该题运用了钦定至少k个 -> 恰好k个的转化
// 此类转化往往是二项式反演的核心

const int mod = 1e9 + 7;
const int MAXN = 1e6;
ll fac[MAXN + 1];// fac[i]即(i!)对mod取模的结果
ll inv[MAXN + 1];// inv[i]即(i!)模mod意义下的逆元
ll g[MAXN + 1];

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
}

ll C(ll n, ll m) {
    return (((fac[n] * inv[m]) % mod) * inv[n - m]) % mod;
}

void prepare(int n) {
    init(n);
    // g(i) = C(n, i) * (2 ^ (2 ^ (n - i)) - 1)
    ll tmp = 2;
    for (int i = n;i >= 0;i--) {
        g[i] = tmp;
        tmp = tmp * tmp % mod;
    }
    for (int i = 0;i <= n;i++) {
        g[i] = (g[i] + mod - 1) % mod * C(n, i) % mod;
    }
}

ll f(int k, int n) {
    ll ans = 0;
    // f(k) = (-1)^(i - k) * C(i, k) * g(i) 求和(k <= i <= n)
    for (int i = k;i <= n;i++) {
        if ((i - k) & 1) {
            ans = (ans + C(i, k) * (mod - 1) % mod * g[i] % mod) % mod;
        }
        else {
            ans = (ans + C(i, k) * g[i] % mod) % mod;
        }
    }
    return ans;
}

void solve() {
    int n, k;
    cin >> n >> k;
    prepare(n);
    cout << f(k, n);
}
