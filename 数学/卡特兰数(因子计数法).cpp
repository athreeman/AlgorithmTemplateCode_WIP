#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// 卡特兰数：
// f(n) = C(2n, n) / (n + 1)
// 公式2, n >= 0

// 当数据量达到1e6规模, 模数mod未必是质数
// 需要用到公式2 + 因子计数法求解
// 维护最小质因子表, 质数不需要维护(默认标记0, 否则会出错！)

// 时间复杂度:O(n)
// https://www.luogu.com.cn/problem/P3200
// 核心代码如下：


ll f2(int n, int mod) {
    // 2 ~ n : -1
    fill(cnt + 2, cnt + n + 1, -1);
    // n + 2 ~ 2n : 1
    fill(cnt + n + 2, cnt + 2 * n + 1, 1);
    for (int i = 2 * n;i >= 2;i--) {
        if (minFactor[i] != 0) {
            cnt[minFactor[i]] += cnt[i];
            cnt[i / minFactor[i]] += cnt[i];
            cnt[i] = 0;
        }
    }
    ll ans = 1;
    for (int i = 2;i <= 2 * n;i++) {
        if (cnt[i] != 0) {
            ans = ans * pw(i, cnt[i], mod) % mod;
        }
    }
    return ans;
}

const int MAXN = 1e6;
// ！！！开二倍空间！！！
ll minFactor[2 * MAXN + 1];// minFactor[i]表示i的最小质因子(线性欧拉筛维护最小质因子表)
bitset<2 * MAXN + 1>isPrime;//标记质数
ll Primes[2 * MAXN + 1];
int cnt[2 * MAXN + 1];
void getPrimes_Linear(ll n) {
    isPrime.set();
    isPrime[0] = isPrime[1] = 0;
    Primes[0] = 0;
    for (ll i = 2;i <= n;i++) {
        // 注意：卡特兰数和因子计数法, 质数不需要获取
        if (isPrime[i]) Primes[++Primes[0]] = i;
        for (ll j = 1, v;j <= Primes[0];j++) {
            v = Primes[j];
            if (v * i > n)break;
            isPrime[i * v] = 0;
            minFactor[i * v] = v;
            if (i % v == 0)break;
        }
    }
}

ll pw(ll a, ll b, int mod) {
    ll res = 1;
    while (b) {
        if (b & 1)res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
