#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ill = __int128_t;
// 中国剩余定理
// 一般形式：要求m1, m2, ...mn互质
// x% m1 = r1, x% m2 = r2, ..., x% mn = rn
// lcm = m1 * m2 * m3*...*mn(互质)
// ai = lcm / mi
// ci = (ri * ai * inv(ai, mi)) % lcm
// 每一个ci满足ci% mi = ri, ci% mj = 0(j != i)
// x = c1 + c2 + c3 + ... + cn
// 最小整数解minx = x % lcm
// 通解X = k * lcm + minx(k >= 0)

const int MAXN = 2e5;
ll r[MAXN + 1];
ll m[MAXN + 1];
ll c[MAXN + 1];
ll a[MAXN + 1];

ll add(ll a, ll b, ll mod) {
    return b == 0 ? a : add(a ^ b, ((a & b) << 1) % mod, mod);
}
ll multiply(ll a, ll b, ll ans, ll mod) {
    return b == 0 ? ans : multiply((a << 1) % mod, (ull)b >> 1, (b & 1) ? add(ans, a, mod) : ans, mod);
}
ll mul(ll a, ll b, ll mod) { return multiply(a, b, 0, mod); }


ll exgcd(ll a, ll b, ll& x, ll& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    else {
        ll g = exgcd(b, a % b, x, y);
        ll tmp = y;
        y = x - y * (a / b);
        x = tmp;
        return g;
    }
}

ll inv(ll a, ll mod) {
    ll x, y;
    exgcd(a, mod, x, y);
    x = (x % mod + mod) % mod;
    return x;
}

// 模板：https://www.luogu.com.cn/problem/P1495
// 注意：
// 使用__int128_t的数据类型, 避免中间数据爆ll类型
// 或自行使用位运算实现乘法, 每一步进行取模运算
// 两者都可AC, C++建议使用__int128_t类型, 更高效和安全

void solve() {
    int n;
    cin >> n;
    ll lcm = 1;
    for (int i = 1;i <= n;i++) {
        cin >> m[i] >> r[i];
        lcm *= m[i];
    }
    ll x = 0;

    for (int i = 1;i <= n;i++) {
        a[i] = lcm / m[i];
        // c[i] = mul(r[i], mul(a[i], inv(a[i], m[i]), lcm), lcm);
        c[i] = (ill)r[i] * (ill)a[i] % lcm * (ill)inv(a[i], m[i]) % lcm;
        x = (x + c[i]) % lcm;
    }
    x %= lcm;
    cout << x << '\n';
}
