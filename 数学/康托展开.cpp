#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// 康托展开：
// 给定数字1~n, 给定1~n的排列P, 求该排列P的名次(字典序升序)
// rank(P) = [范围求和1 <= i <= n]：rightSmall(P[i]) * (n - i)!

// https://www.luogu.com.cn/problem/P5367

const int MAXN = 1e6;
const int mod = 998244353;
int tree[MAXN + 1];
int fac[MAXN + 1];
int p[MAXN + 1];

int lowbit(int x) {
    return x & -x;
}

void add(int i, int n, int v) {
    while (i <= n) {
        tree[i] += v;
        i += lowbit(i);
    }
}

int sum(int r) {
    int ans = 0;
    while (r > 0) {
        ans = ll((ll)ans + (ll)tree[r]) % mod;
        r -= lowbit(r);
    }
    return ans;
}

int rank(int n) {
    int ans = 0;
    for (int i = 1;i <= n;i++) {
        ans = ll((ll)ans + (ll)sum(p[i] - 1) * (ll)fac[n - i] % mod) % mod;
        add(p[i], n, -1);
    }
    return ans;
}

void prepare(int n) {
    fac[0] = 1;
    for (int i = 1;i <= n;i++) {
        fac[i] = ll((ll)fac[i - 1] * (ll)i) % mod;
    }
}

void solve() {
    int n;
    cin >> n;
    prepare(n);
    for (int i = 1;i <= n;i++) {
        add(i, n, 1);
        cin >> p[i];
    }
    cout << ::rank(n) + 1;
}
