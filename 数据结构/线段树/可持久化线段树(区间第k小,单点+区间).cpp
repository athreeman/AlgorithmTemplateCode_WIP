#include<bits/stdc++.h>
using namespace std;

using ll = long long;

const int MAXN = 2e5;

int a[MAXN + 1];
int version[MAXN + 1];
int d[MAXN + 1];
int m = 0;
int cnt = 0;
struct tree {
    int left;
    int right;
    int size;
}node[(MAXN << 2 | 1) + MAXN * 20];

int clone(int i) {
    ++cnt;
    node[cnt] = node[i];
    return cnt;
}

void up(int i) {
    node[i].size = node[node[i].left].size + node[node[i].right].size;
}

int id(int val) {
    int l = 1, r = m;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (d[mid] == val) {
            return mid;
        }
        else if (d[mid] > val) {
            r = mid - 1;
        }
        else {
            l = mid + 1;
        }
    }
    return l;
}

int build(int l, int r) {
    int rt = ++cnt;
    node[rt].size = 0;
    if (l == r) {
        return rt;
    }
    int mid = (l + r) >> 1;
    node[rt].left = build(l, mid);
    node[rt].right = build(mid + 1, r);
    up(rt);
    return rt;
}

int insert(int jobi, int l, int r, int i) {
    int rt = clone(i);
    if (l == r) {
        node[rt].size++;
    }
    else {
        int mid = (l + r) >> 1;
        if (jobi <= mid) {
            node[rt].left = insert(jobi, l, mid, node[rt].left);
        }
        else {
            node[rt].right = insert(jobi, mid + 1, r, node[rt].right);
        }
        up(rt);
    }
    return rt;
}

int query(int jobk, int l, int r, int h1, int h2) {
    if (l == r) {
        return d[l];
    }
    int mid = (l + r) >> 1;
    int lsiz = node[node[h2].left].size - node[node[h1].left].size;
    if (lsiz >= jobk) {
        return query(jobk, l, mid, node[h1].left, node[h2].left);
    }
    else {
        return query(jobk - lsiz, mid + 1, r, node[h1].right, node[h2].right);
    }
}

void prepare() {
    int c = m;
    m = 0;
    sort(d + 1, d + c + 1);
    d[0] = -1;
    for (int i = 1;i <= c;i++) {
        if (d[i] != d[m]) {
            d[++m] = d[i];
        }
    }
}

// https://www.luogu.com.cn/problem/P3834

void solve() {
    int n, q;
    cin >> n >> q;
    cnt = 0;
    for (int i = 1;i <= n;i++) {
        cin >> a[i];
        d[i] = a[i];
    }
    m = n;
    prepare();
    version[0] = build(1, m);
    for (int i = 1;i <= n;i++) {
        // 基于上一个版本, 排名为id(a[i])的位置, 词频 + 1
        version[i] = insert(id(a[i]), 1, m, version[i - 1]);
    }
    while (q--) {
        int l, r, k;
        cin >> l >> r >> k;
        cout << query(k, 1, m, version[l - 1], version[r]) << '\n';
    }
}