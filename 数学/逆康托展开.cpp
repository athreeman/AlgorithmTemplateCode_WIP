#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// 逆康托展开：
// 给定数字1~n, 给定1~n的排列P
// P排列的名次x, 求第x + m的排列
// 核心：阶乘进制, 第i位使用i!作为基准(最低位0)
// 第i位的数位就是rightSmall[P[i]](康托展开内容)

// https://www.luogu.com.cn/problem/U72177

const int MAXN = 1e5;
int sum[MAXN << 2 | 1];
ll a[MAXN + 1];
void add(int jobi, int jobv, int l, int r, int i);
int range(int jobl, int jobr, int l, int r, int i);
void build(int l, int r, int i);
int queryAndDelete(int jobk, int l, int r, int i);
// 核心代码：
void compute(int n, ll m) {
    build(1, n, 1);

    // 把排列的每一位,转化为对应的阶乘进制位
    // 方法：小于当前位值的未使用元素个数
    for (int i = 1;i <= n;i++) {
        int tmp = a[i];
        a[i] = range(1, tmp - 1, 1, n, 1);
        add(tmp, -1, 1, n, 1);
    }

    // 阶乘进位：
    // 和下一位相比,多乘的值val,进行除法取模进位
    a[n] += m;
    for (int i = n;i >= 1;i--) {
        a[i - 1] += a[i] / ll(n - i + 1);
        a[i] %= ll(n - i + 1);
    }
    build(1, n, 1);
    for (int i = 1;i <= n;i++) {
        a[i] = queryAndDelete(a[i] + 1, 1, n, 1);
    }
}

void build(int l, int r, int i) {
    if (l == r) {
        sum[i] = 1;
    }
    else {
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
        sum[i] = sum[i << 1] + sum[i << 1 | 1];
    }
}

int range(int jobl, int jobr, int l, int r, int i) {
    if (jobl > jobr)return 0;
    if (jobl <= l && r <= jobr) {
        return sum[i];
    }
    else {
        int mid = (l + r) >> 1;
        int ans = 0;
        if (jobl <= mid) {
            ans += range(jobl, jobr, l, mid, i << 1);
        }
        if (jobr > mid) {
            ans += range(jobl, jobr, mid + 1, r, i << 1 | 1);
        }
        return ans;
    }
}

void add(int jobi, int jobv, int l, int r, int i) {
    if (l == r) {
        sum[i] += jobv;
    }
    else {
        int mid = (l + r) >> 1;
        if (jobi <= mid) {
            add(jobi, jobv, l, mid, i << 1);
        }
        else {
            add(jobi, jobv, mid + 1, r, i << 1 | 1);
        }
        sum[i] = sum[i << 1] + sum[i << 1 | 1];
    }
}

int queryAndDelete(int jobk, int l, int r, int i) {
    if (l == r) {
        sum[i]--;
        return l;
    }
    else {
        int lsum = sum[i << 1];
        int rsum = sum[i << 1 | 1];
        int mid = (l + r) >> 1;
        int ans;
        if (lsum >= jobk) {
            ans = queryAndDelete(jobk, l, mid, i << 1);
        }
        else {
            ans = queryAndDelete(jobk - lsum, mid + 1, r, i << 1 | 1);
        }
        sum[i] = sum[i << 1] + sum[i << 1 | 1];
        return ans;
    }
}

void solve() {
    ll n, m;
    cin >> n >> m;
    for (int i = 1;i <= n;i++) {
        cin >> a[i];
    }
    compute(n, m);
    for (int i = 1;i <= n;i++) {
        cout << a[i] << ' ';
    }
}
