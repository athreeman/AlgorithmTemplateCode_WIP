#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ill = __int128_t;

// 中国剩余定理
// 扩展：m1, m2, m3, ..., mn之间不需要严格互质
// x% m1 = r1, x% m2 = r2, ..., x% mn = rn
// 补充初始模数m0 = 1, lcm = 1, tail = 0, 得到ans1 = x * lcm + tail
// 对于mi, ri, 得到ans2 = y * mi + ri
// 显然ans1 = ans2, 相消得到lcm* x + mi * y = ri - tail, 即ax + by = c
// exgcd求解, 若不存在解说明无解


// 通解x = x0 + (b / d) * n, 带入ans = lcm * x + tail, ans = lcm * (b / d) * n + (lcm * x0 + tail)
// 即进行如下运算：
// 得到lcm1 = lcm * (b / d), tail1 = (lcm * x0 + tail) % lcm1
// 得到ans = lcm1 * x + tail1
// 持续迭代直到结束, 得到最后的tail就是答案(最小整数解)

const int MAXN = 2e5;
ll r[MAXN + 1];
ll m[MAXN + 1];

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

// 模板：https://www.luogu.com.cn/problem/P4777
// C++建议使用__int128_t类型, 比位运算实现更为安全和高效
ll excrt(int n) {
    ll tail = 0, lcm = 1, tmp, a, b, c, x0;
    for (int i = 1;i <= n;i++) {
        // 此处a, b, c可能因题意而定制
        a = lcm;
        b = m[i];
        c = ((r[i] - tail) % b + b) % b;

        // 以下代码是通用部分
        ll x, y;
        ll d = exgcd(a, b, x, y);
        if (c % d != 0) {
            return -1;//无解
        }

        // x0保证非负特解
        x0 = ((ill)x * (ill)(c / d) % (b / d) + ill(b / d)) % (b / d);
        tmp = lcm * (b / d);// 此时的tmp就是新的lcm1
        tail = ((ill)tail + ill(x0) * ill(lcm) % tmp) % tmp;
        lcm = tmp;
    }
    // tail是返回最小非负解
    return tail;
}
