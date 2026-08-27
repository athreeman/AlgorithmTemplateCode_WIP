#include<bits/stdc++.h>
using namespace std;

// 01分数规划, 性价比问题
// 给定数组a, b
// 选择部分下标，使得sum(a) / sum(b)最大化
// 公式转化：
// sum(a) / sum(b) = x -> sum(a) - x * sum(b) = 0 -> sum(a[i] - b[i] * x) = 0
// 使用二分答案发求解

// https://www.luogu.com.cn/problem/P10505
const int MAXN = 1e3;
using ld = long double;
using ll = long long;
const ld eps = 1e-12;
struct stc {
    ld a, b;
    ld val;
}a[MAXN + 1];
bool cmp(stc s1, stc s2) {
    return s1.val > s2.val;
}
bool check(ld x, int n, int k) {
    for (int i = 1;i <= n;i++) {
        a[i].val = a[i].a - a[i].b * x;
    }
    sort(a + 1, a + n + 1, cmp);
    ld sum = 0;
    for (int i = 1;i <= k;i++) {
        sum += a[i].val;
    }
    return sum >= eps;
}

bool solve() {
    int n, k;
    cin >> n >> k;
    cout << fixed << setprecision(16);
    if (n == 0 && k == 0) {
        return false;
    }
    ld l = 0, r = 0;
    k = n - k;
    for (int i = 1;i <= n;i++) {
        cin >> a[i].a;
        r += a[i].a;
    }
    for (int i = 1;i <= n;i++) {
        cin >> a[i].b;
    }
    while (l<r && r - l>eps) {
        ld mid = (l + r) / 2.0;
        if (check(mid, n, k)) {
            l = mid + eps;
        }
        else {
            r = mid - eps;
        }
    }
    cout << (ll)round(l * 100.0) << '\n';
    return true;
}
